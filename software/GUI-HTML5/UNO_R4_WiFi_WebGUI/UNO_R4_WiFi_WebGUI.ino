/*
  UNO R4 WiFi - HTML_GUI Webserver + USB serial command bridge

  - Creates its own Wi-Fi access point (phone/tablet/PC connects to it).
  - Serves the supplied HTML_GUI pages from flash memory.
  - Converts the existing website's Web Serial writes into HTTP POST /send.
  - Forwards each command line to Windows over USB Serial at 115200 baud.

  IMPORTANT: Serial is reserved for application commands. Do not add debug
  Serial.print/println calls here, otherwise those messages reach the PC app.
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

WiFiServer server(80);

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

// Trims only the outer whitespace. A command is sent as one USB serial line.
static bool sendCommandLine(char *line, size_t length) {
  while (length > 0 && (line[length - 1] == ' ' || line[length - 1] == '\t' || line[length - 1] == '\r')) {
    --length;
  }
  size_t first = 0;
  while (first < length && (line[first] == ' ' || line[first] == '\t')) {
    ++first;
  }
  if (first >= length) return true; // ignore blank lines

  // Disallow control characters in the payload except ordinary printable text.
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
      // Stream::read can return -1 while data is momentarily unavailable.
      unsigned long waitStart = millis();
      while (incoming < 0 && client.connected() && millis() - waitStart < 2500) {
        delay(1);
        incoming = client.read();
      }
      if (incoming < 0) return false;
    }

    char c = static_cast<char>(incoming);
    if (c == '\n') {
      if (lineOverflow) {
        valid = false;
      } else if (!sendCommandLine(line, lineLength)) {
        valid = false;
      }
      lineLength = 0;
      lineOverflow = false;
    } else if (c != '\r') {
      if (lineLength < MAX_COMMAND_LINE) {
        line[lineLength++] = c;
      } else {
        lineOverflow = true;
      }
    }
  }

  if (lineOverflow) {
    valid = false;
  } else if (lineLength > 0 && !sendCommandLine(line, lineLength)) {
    valid = false;
  }
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

  if (method == "POST" && target == "/send") {
    if (contentLength > MAX_HTTP_BODY) {
      sendText(client, 413, "Payload Too Large", "Command payload too large\n");
    } else {
      bool ok = forwardRequestBody(client, contentLength);
      if (ok) sendText(client, 200, "OK", "OK\n");
      else sendText(client, 400, "Bad Request", "Invalid or incomplete command payload\n");
    }
  } else if (method == "GET") {
    servePage(client, target.c_str());
  } else {
    sendText(client, 405, "Method Not Allowed", "Method not allowed\n");
  }

  delay(1);
  client.stop();
}

void setup() {
  // USB serial is the data channel to the Windows C++ program.
  Serial.begin(SERIAL_BAUD);

  // Create a password-protected Wi-Fi network hosted by the UNO R4 WiFi.
  int apStatus = WiFi.beginAP(AP_SSID, AP_PASSWORD);
  if (apStatus != WL_AP_LISTENING) {
    // Do not print errors on Serial: the PC program expects commands only.
    while (true) delay(1000);
  }

  delay(1000);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) handleClient(client);
}
