# UNO R4 WiFi WebGUI – Bidirectional Serial Bridge

The Arduino UNO R4 WiFi hosts the updated HTML GUI and transports data between the browser and the Heavy Core C++ application over USB serial.

## Connection

- Wi-Fi access point: `GUI-UNO-R4`
- HTTP server: `http://192.168.4.1/` (connect to the UNO access point first)
- USB serial baud rate: `115200`
- Browser to PC: `POST /send`
- PC to browser: `GET /receive` (polled by the page bridge every 75 ms)
- Messages are newline-delimited. The UNO appends CR/LF to each complete command it forwards to the PC.

Do not print debugging messages on the USB `Serial` connection while Heavy Core is connected. Debug output would be interpreted as application data by the GUI.

## Commands sent from GUI to PC

The command strings below use the syntax described by the supplied `COMMAND_GRAMMAR` and the command guide embedded in `Main_page.html`.

| GUI / feature | Full command sent over USB | Parameters / notes |
|---|---|---|
| Emergency stop | `XSTOPX` | Optional argument in grammar: `#`, `1` or `DUMMY`; GUI sends no argument. Use only as the actual emergency-stop path. |
| Program termination | `XENDX` | Optional argument in grammar: `#`, `1` or `DUMMY`; GUI sends no argument. |
| Enable motors | `ENAM ALL` or `ENAM 1,2,3` | `ALL` or selected axes 1–6, comma- or space-separated. |
| Disable motors | `DISM ALL` or `DISM 2,4,6` | Same axis selection syntax. |
| Enable axis controllers | `ENAC ALL` or `ENAC 1,3,5` | Same axis selection syntax. |
| Disable axis controllers | `DISC ALL` or `DISC 1,2` | Same axis selection syntax. |
| Cartesian movement | `MOVE 100 200 300 0 90 0` | Exactly six numeric values: X, Y, Z, Rx, Ry, Rz. Decimal and negative values are accepted by the shown regex. |
| Single-joint movement | `SINGLE JOINT MOVE 1 90` | Joint index 1–7 and one signed numeric value. |
| Repeated movement | `REPEAT 100 200 300 0 0 0 5 10 0 2` | Ten integer parameters: initial X/Y/Z/Rx/Ry/Rz, repeat count (positive), ΔX, ΔY, ΔZ. |
| Motion speed | `SET SPEED[50]` | Intended value range 1–100. |
| Acceleration | `SET ACCEL[75]` | Intended value range 1–100. |
| Deceleration | `SET DECEL[25]` | Intended value range 1–100. |
| Homing | `HOME[3]` | Intended axis selection 0–6; the project guide says 0 may represent all axes. |
| Chamber fan | `CHAMBER FAN ON`, `CHAMBER FAN OFF`, `CHAMBER FAN SPEED+`, `CHAMBER FAN SPEED-`, `CHAMBER FAN AUTO` | No fan number is appended; the supplied regex has no fan-index parameter. |
| Chamber lights | `CHAMBER LIGHTS ON` / `CHAMBER LIGHTS OFF` | Exact form required by grammar. |
| Chamber PSU | `CHAMBER PSU ON` / `CHAMBER PSU OFF` | Exact form required by grammar. |
| Read chamber sensor | `CHAMBER READ - HUM` | Use `HUM`, `PRESS`, `TEMP` or `CONTROLER TEMP`. |
| Text editor | User-entered command text, newline-delimited | The editor sends text as entered. Each command must match the C++ parser grammar. Local file download is separate. |

### Commands not sent by the current GUI

- `HAA` is marked `old unused` in the supplied grammar; the Controls page uses the newer `HOME[0]`…`HOME[6]` form instead.
- `READ SENSOR DATA ALL` / `READ SENSOR DATA <axis>` is **not present** in the supplied `COMMAND_GRAMMAR`. The RSD page therefore only displays incoming telemetry; it no longer emits this unsupported request.
- `SAVE "name"` is not present in the supplied grammar. The Text Editor keeps local `.gcode` download but does not send a remote `SAVE` command.

## Data sent from PC back to GUI

The UNO bridge transports received bytes without interpreting them. The page JavaScript processes newline-delimited response lines.

| PC response line | GUI target | Required format / notes |
|---|---|---|
| Axis 1 telemetry | RSD, axis 1 | `AXIS:1,<position>,<motor_temp>,<load>,<mpu>` |
| Axis 2 telemetry | RSD, axis 2 | `AXIS:2,<position1>,<position2>,<motor_temp1>,<motor_temp2>,<load>` |
| Axis 3 telemetry | RSD, axis 3 | `AXIS:3,<position>,<motor_temp>,<load>` |
| Axis 4 telemetry | RSD, axis 4 | `AXIS:4,<position>,<motor_temp>,<load>,<mpu>` |
| Axis 5 telemetry | RSD, axis 5 | `AXIS:5,<position>,<motor_temp>,<load>` |
| Axis 6 telemetry | RSD, axis 6 | `AXIS:6,<position>,<motor_temp>,<load>,<mpu>` |
| Chamber temperature | Chamber | `CHAMBER TEMP:<value>` (°C) |
| Chamber humidity | Chamber | `CHAMBER HUM:<value>` (%) |
| Chamber pressure | Chamber | `CHAMBER PRESS:<value>` (hPa) |
| Chamber controller temperature | Chamber | `CHAMBER CONTROLER TEMP:<value>` (°C) |
| General command result | Controls / Text Editor | Any line, e.g. `OK:<message>`, `ERR:<message>` or `UNKNOWN:<message>`. |

Every response must end with `\n`. Do not add labels, spaces, or additional columns to the `AXIS:` CSV records beyond the field order shown above unless you also update `rsd.html`'s parser.

## Important regex note

The `SET` and `HOME` regexes in the snippet appear to escape square brackets around fixed text such as `1-100` and `0-6`. As written literally, patterns like `SPEED\[1-100\]` match the text `SPEED[1-100]`, not every numeric value from 1 to 100. The UI emits the examples documented in the project guide (such as `SET SPEED[50]` and `HOME[3]`), but the C++ regex should be checked so its actual accepted range matches the intended numeric range.

Similarly, `HOME` appears both as a `SET` subcommand and as its own grammar key. Confirm in the command parser whether the accepted complete line is `HOME[3]` or a prefixed form before relying on that control.

## Project files

- `UNO_R4_WiFi_WebGUI.ino` — Wi-Fi server, `/send`, `/receive`, USB serial buffering.
- `WebPages.h` — HTML and CSS assets embedded in flash.
- `SerialBridge.h` — Browser Web Serial compatibility bridge, including receive polling.
- `Main_page.html` — Project and command reference.
- `controls.html`, `chamber.html`, `rsd.html`, `text-editor.html` — Interactive pages.

The UNO R4 firmware has not been compiled against a specific installed Arduino board package in this environment and has not been hardware-tested. Check the serial format and command parser on the target system before enabling motion.
