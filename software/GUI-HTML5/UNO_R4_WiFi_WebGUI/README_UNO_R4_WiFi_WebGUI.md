# UNO R4 WiFi — HTML GUI over Wi-Fi and USB Serial

This project lets you use the existing HTML GUI with an Arduino UNO R4 WiFi. The Arduino creates its own Wi-Fi access point and hosts the website. When you use a control on the website, the browser sends an HTTP request to the Arduino, which forwards each command line to your Windows C++ application over USB serial.

## Wi-Fi access point

- **SSID:** `GUI-UNO-R4`
- **Default password:** `GUIcontrol24`
- **Website:** <http://192.168.4.1/>

The SSID and password are configured near the top of `UNO_R4_WiFi_WebGUI.ino` as `AP_SSID` and `AP_PASSWORD`. Change the default password before using the device in an environment where untrusted people may be nearby. Anyone who can join this access point can send commands to the connected C++ application.

The address `192.168.4.1` is the Arduino's default access-point address in this sketch; it is a private local address and is not a public Internet address. The website is served by the Arduino, so an Internet connection is not required.

## Setup

1. Install the latest Arduino IDE.
2. Open `UNO_R4_WiFi_WebGUI.ino`. Keep `WebPages.h` and `SerialBridge.h` in the same folder as the sketch.
3. In Boards Manager, install **Arduino UNO R4 Boards**. Select **Arduino UNO R4 WiFi** under **Tools → Board**, and select the correct port for uploading.
4. Connect the board to your computer with USB-C and upload the sketch.
5. On your phone, tablet, or computer, connect to the `GUI-UNO-R4` Wi-Fi network using the configured password. If your device warns that the network has no Internet access, stay connected.
6. Open <http://192.168.4.1/> in a browser.
7. Start your Windows C++ application and connect it to the Arduino's USB serial COM port. The COM port number may change after uploading or restarting; check Windows Device Manager.

## Windows C++ serial connection

- **USB serial baud rate:** `115200` (configured by `SERIAL_BAUD` in the sketch).
- Configure the C++ application to use the same baud rate.
- A single website command is forwarded as a line ending in `
` over USB serial.
- Multiline text is forwarded one line at a time.
- The sketch does not print debug messages to `Serial`, because those messages would be received by the C++ application as if they were commands.
- The Arduino does not open the Windows COM port; your C++ application does that.

Close the Arduino Serial Monitor and any other serial terminal while the C++ application is using the COM port. On Windows, the same serial port generally cannot be opened by two applications at the same time.

## Current limitations and security notes

- This version supports the **website → Arduino → Windows C++** direction.
- Data sent back from the Windows application to the Arduino is not currently forwarded to the website. Existing website sections that expect live serial data from the PC will not receive new PC data in this version.
- The Wi-Fi access point is password-protected, but every device that can join it can send website commands. Use a strong, unique password and connect only trusted devices.
- This is a local access-point web server, not a website published on the public Internet.

## Files

- `UNO_R4_WiFi_WebGUI.ino` — Arduino web server and USB serial command forwarding.
- `WebPages.h` — HTML and CSS pages stored in the Arduino's flash memory.
- `SerialBridge.h` — browser-side bridge that sends website commands to the Arduino over HTTP.
- `Website/` — editable original website pages with the bridge script reference, if included in your working copy.
