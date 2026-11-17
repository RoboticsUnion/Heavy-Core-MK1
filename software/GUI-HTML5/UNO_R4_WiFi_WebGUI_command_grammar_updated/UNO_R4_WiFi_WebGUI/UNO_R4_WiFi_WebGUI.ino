/*
  UNO R4 WiFi - HTML_GUI Webserver + bidirectional USB serial bridge

  - Creates its own Wi-Fi access point.
  - Serves the HTML_GUI pages from flash memory.
  - POST /send: forwards browser commands to the PC over USB Serial.
  - GET /receive: returns bytes received from the PC over USB Serial.

  Serial is the application data channel. Do not add debug Serial.print calls:
  they would be forwarded to the website as if they were robot responses.
*/
#include <WiFiS3.h>
#include <string.h>
#include "WebPages.h"
#include "SerialBridge.h"

const char AP_SSID[] = "GUI-UNO-R4";
const char AP_PASSWORD[] = "GUIcontrol24"; // WPA2 password: at least 8 characters

constexpr unsigned long SERIAL_BAUD = 115200;
constexpr size_t MAX_HTTP_BODY = 8192;
constexpr size_t MAX_COMMAND_LINE = 511;
constexpr size_t SERIAL_RX_CAPACITY = 2048;
constexpr size_t SERIAL_RX_RESPONSE_SIZE = 1024;

WiFiServer server(80);

// Fixed-size ring buffer keeps USB serial input available between HTTP polls.
static uint8_t serialRxBuffer[SERIAL_RX_CAPACITY];
static size_t serialRxHead = 0;
static size_t serialRxTail = 0;
static size_t serialRxCount = 0;
static uint32_t serialRxDropped = 0;

static void collectSerialInput() {
  while (Serial.available() > 0) {
    int incoming = Serial.read();
    if (incoming < 0) break;

    if (serialRxCount < SERIAL_RX_CAPACITY) {
      serialRxBuffer[serialRxHead] = static_cast<uint8_t>(incoming);
      serialRxHead = (serialRxHead + 1) % SERIAL_RX_CAPACITY;
      ++serialRxCount;
    } else {
      // Preserve queued data and count newer bytes that could not be stored.
      ++serialRxDropped;
    }
  }
}

static size_t takeSerialInput(uint8_t *destination, size_t maxLength) {
  size_t copied = 0;
  while (copied < maxLength && serialRxCount > 0) {
    destination[copied++] = serialRxBuffer[serialRxTail];
    serialRxTail = (serialRxTail + 1) % SERIAL_RX_CAPACITY;
    --serialRxCount;
  }
  return copied;
}

static void sendResponse(WiFiClient &client, int statusCode,
                         const char *statusText, const char *contentType,
                         const uint8_t *data, size_t length) {
  client.print("HTTP/1.1 ");
  client.print(statusCode);
  client.print(' ');
  client.print(statusText);
  client.print("\r\nContent-Type: ");
  client.print(contentType);
  client.print("\r\nContent-Length: ");
  client.print(length);
  client.print("\r\nConnection: close\r\nCache-Control: no-store\r\nX-Content-Type-Options: nosniff\r\n\r\n");
  if (data != nullptr && length > 0) {
    client.write(data, length);
  }
}

static void sendText(WiFiClient &client, int statusCode,
                     const char *statusText, const char *body) {
  sendResponse(client, statusCode, statusText, "text/plain; charset=utf-8",
               reinterpret_cast<const uint8_t *>(body), strlen(body));
}

static void serveContent(WiFiClient &client, const char *type,
                         const char *content, size_t length) {
  sendResponse(client, 200, "OK", type,
               reinterpret_cast<const uint8_t *>(content), length);
}

static void serveSerialReceive(WiFiClient &client) {
  collectSerialInput();

  uint8_t responseBuffer[SERIAL_RX_RESPONSE_SIZE];
  size_t responseLength = takeSerialInput(responseBuffer, sizeof(responseBuffer));
  uint32_t dropped = serialRxDropped;
  serialRxDropped = 0;

  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Content-Type: application/octet-stream\r\n");
  client.print("Content-Length: ");
  client.print(responseLength);
  client.print("\r\nX-RX-Dropped: ");
  client.print(dropped);
  client.print("\r\nConnection: close\r\nCache-Control: no-store\r\n");
  client.print("X-Content-Type-Options: nosniff\r\n\r\n");

  if (responseLength > 0) {
    client.write(responseBuffer, responseLength);
  }
}

static void servePage(WiFiClient &client, const char *path) {
  if (strcmp(path, "/") == 0 || strcmp(path, "/Main_page.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_MAIN, sizeof(PAGE_MAIN) - 1);
  } else if (strcmp(path, "/controls.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_CONTROLS, sizeof(PAGE_CONTROLS) - 1);
  } else if (strcmp(path, "/settings.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_SETTINGS, sizeof(PAGE_SETTINGS) - 1);
  } else if (strcmp(path, "/rsd.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_RSD, sizeof(PAGE_RSD) - 1);
  } else if (strcmp(path, "/chamber.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_CHAMBER, sizeof(PAGE_CHAMBER) - 1);
  } else if (strcmp(path, "/text-editor.html") == 0) {
    serveContent(client, "text/html; charset=utf-8", PAGE_TEXT_EDITOR, sizeof(PAGE_TEXT_EDITOR) - 1);
  } else if (strcmp(path, "/style.css") == 0) {
    serveContent(client, "text/css; charset=utf-8", PAGE_CSS, sizeof(PAGE_CSS) - 1);
  } else if (strcmp(path, "/serial_bridge.js") == 0) {
    serveContent(client, "application/javascript; charset=utf-8", PAGE_BRIDGE_JS, sizeof(PAGE_BRIDGE_JS) - 1);
  } else if (strcmp(path, "/favicon.ico") == 0) {
    sendResponse(client, 204, "No Content", "text/plain", nullptr, 0);
  } else {
    sendText(client, 404, "Not Found", "Not found\n");
  }
}

// Trims outer whitespace. A command is forwarded to the PC as one USB line.
static bool sendCommandLine(char *line, size_t length) {
  while (length > 0 && (line[length - 1] == ' ' || line[length - 1] == '\t' || line[length - 1] == '\r')) {
    --length;
  }
  size_t first = 0;
  while (first < length && (line[first] == ' ' || line[first] == '\t')) {
    ++first;
  }
  if (first >= length) return true;

  for (size_t i = first; i < length; ++i) {
    unsigned char c = static_cast<unsigned char>(line[i]);
    if (c < 0x20 && c != '\t') return false;
  }

  Serial.write(reinterpret_cast<const uint8_t *>(line + first), length - first);
  Serial.write('\r');
  Serial.write('\n');
  return true;
}

static bool forwardRequestBody(WiFiClient &client, size_t contentLength) {
  char line[MAX_COMMAND_LINE + 1];
  size_t lineLength = 0;
  bool lineOverflow = false;
  bool valid = true;

  for (size_t i = 0; i < contentLength; ++i) {
    int incoming = client.read();
    if (incoming < 0) {
      unsigned long waitStart = millis();
      while (incoming < 0 && client.connected() && millis() - waitStart < 2500) {
        delay(1);
        incoming = client.read();
      }
      if (incoming < 0) return false;
    }

    char c = static_cast<char>(incoming);
    if (c == '\n') {
      if (lineOverflow) valid = false;
      else if (!sendCommandLine(line, lineLength)) valid = false;
      lineLength = 0;
      lineOverflow = false;
    } else if (c != '\r') {
      if (lineLength < MAX_COMMAND_LINE) line[lineLength++] = c;
      else lineOverflow = true;
    }
  }

  if (lineOverflow) valid = false;
  else if (lineLength > 0 && !sendCommandLine(line, lineLength)) valid = false;
  return valid;
}

static void handleClient(WiFiClient &client) {
  client.setTimeout(3000);
  String requestLine = client.readStringUntil('\n');
  requestLine.trim();
  if (requestLine.length() == 0) {
    client.stop();
    return;
  }

  int firstSpace = requestLine.indexOf(' ');
  int secondSpace = requestLine.indexOf(' ', firstSpace + 1);
  if (firstSpace < 0 || secondSpace < 0) {
    sendText(client, 400, "Bad Request", "Bad request\n");
    client.stop();
    return;
  }

  String method = requestLine.substring(0, firstSpace);
  String target = requestLine.substring(firstSpace + 1, secondSpace);
  int question = target.indexOf('?');
  if (question >= 0) target.remove(question);

  size_t contentLength = 0;
  while (client.connected()) {
    String headerLine = client.readStringUntil('\n');
    headerLine.trim();
    if (headerLine.length() == 0) break;

    String lower = headerLine;
    lower.toLowerCase();
    if (lower.startsWith("content-length:")) {
      String number = headerLine.substring(headerLine.indexOf(':') + 1);
      number.trim();
      contentLength = static_cast<size_t>(number.toInt());
    }
  }

  collectSerialInput();

  if (method == "POST" && target == "/send") {
    if (contentLength > MAX_HTTP_BODY) {
      sendText(client, 413, "Payload Too Large", "Command payload too large\n");
    } else {
      bool ok = forwardRequestBody(client, contentLength);
      if (ok) sendText(client, 200, "OK", "OK\n");
      else sendText(client, 400, "Bad Request", "Invalid or incomplete command payload\n");
    }
  } else if (method == "GET" && target == "/receive") {
    serveSerialReceive(client);
  } else if (method == "GET") {
    servePage(client, target.c_str());
  } else {
    sendText(client, 405, "Method Not Allowed", "Method not allowed\n");
  }

  delay(1);
  client.stop();
}

void setup() {
  Serial.begin(SERIAL_BAUD);

  int apStatus = WiFi.beginAP(AP_SSID, AP_PASSWORD);
  if (apStatus != WL_AP_LISTENING) {
    // Do not use Serial for diagnostics; it is reserved for application data.
    while (true) delay(1000);
  }

  delay(1000);
  server.begin();
}

void loop() {
  collectSerialInput();

  WiFiClient client = server.available();
  if (client) handleClient(client);

  // Drain USB input even when no browser is polling at this exact moment.
  collectSerialInput();
}
