# Heavy Core mk1 — C++ Codebase Guide
###### `This dok was written by chatgpt with in the prompt the infos.`

This document is a developer guide for the **Heavy Core mk1** project. It explains the current C++ modules, their public functions, how to use them, and how to investigate common problems.

Heavy Core mk1 is being developed as a control system for a robotic arm. The project is intended to connect a GUI and a terminal to the robot, receive and interpret commands, and communicate with the connected hardware.

> **Project status:** This is an actively developed project. Some modules are functional, while others are prototypes or work in progress. The implementation notes in this guide distinguish implemented behavior from planned functionality. Do not assume that a feature is complete just because its interface is present.

---

## Contents

- [1. Project structure](#1-project-structure)
- [2. Requirements and build](#2-requirements-and-build)
- [3. Dependencies](#3-dependencies)
- [4. Naming and code conventions](#4-naming-and-code-conventions)
- [5. System overview](#5-system-overview)
- [6. Terminal input — TerminalIN](#6-terminal-input--terminalin)
- [7. Terminal output — TerminalOUT](#7-terminal-output--terminalout)
- [8. Serial connection — Serial](#8-serial-connection--serial)
- [9. GUI data preparation — DataPrep](#9-gui-data-preparation--dataprep)
- [10. DialogiXMove decoder — DeCode](#10-dialogixmove-decoder--decode)
- [11. User management — UserManager](#11-user-management--usermanager)
- [12. Preset management — PresetLoader](#12-preset-management--presetloader)
- [13. Logging system — Logging](#13-logging-system--logging)
- [14. Terminal interpreter — TerminalInterpreter](#14-terminal-interpreter--terminalinterpreter)
- [15. Debugging guide](#15-debugging-guide)
- [16. Known limitations and development notes](#16-known-limitations-and-development-notes)
- [17. Planned development](#17-planned-development)
- [18. Safety note](#18-safety-note)

---

## 1. Project structure

The repository separates the C++ runtime, terminal tools, serial communication, robot-command decoding, and Python code.

```text
Heavy Core mk1/
├── C++/
│   ├── .vscode/
│   │   └── tasks.json
│   ├── ansi_color_chart/
│   │   └── ansi_color_chart.hpp
│   ├── Arm-logic/
│   │   ├── DialogiXMove_dekodierer/
│   │   │   ├── DialogiXMove_dekodierer.cpp
│   │   │   └── DialogiXMove_dekodierer.hpp
│   │   └── Serial-Data-logic/
│   │       ├── GUI-data-prep/
│   │       │   ├── GUI-data-prep.cpp
│   │       │   └── GUI-data-prep.hpp
│   │       └── Serial-conection/
│   │           ├── serial-conection.cpp
│   │           └── serial-conection.hpp
│   ├── Main_runtime/
│   │   └── main.cpp
│   └── Terminal/
│       ├── Login-Register-Presetloading/
│       │   ├── logging-system/
│       │   ├── nlohmann/
│       │   ├── preset-manager/
│       │   ├── usr-manager/
│       │   └── preset-user.json
│       ├── Terminal-IN/
│       ├── Terminal-Interpreter/
│       └── Terminal-OUT/
│           └── error_list.txt
└── Python/
    └── inverse_kinematics/
        └── inverse_kinematik.py
```

### Main module responsibilities

| Module | Responsibility |
|---|---|
| `Terminal-IN` | Reads text, integer, and password input from the terminal. |
| `Terminal-OUT` | Prints terminal messages, applies ANSI colors, and looks up configured error messages. |
| `Terminal-Interpreter` | Dispatches terminal commands to registered command handlers. |
| `Serial-conection` | Opens, configures, checks, and closes the GUI, CON1, and CON2 serial connections. |
| `GUI-data-prep` | Reads serial input line by line or as a complete code block and validates command syntax. |
| `DialogiXMove_dekodierer` | Converts supported DialogiXMove command lines into typed C++ command objects. |
| `usr-manager` | Registers, authenticates, and deletes users in the JSON database. |
| `preset-manager` | Provides the interface for loading and changing user presets. Its implementation is currently incomplete. |
| `logging-system` | Appends timestamped messages to the log file. |
| `ansi_color_chart` | Defines ANSI color strings for terminal output. |

---

## 2. Requirements and build

### Development environment

The supplied C++ build configuration is designed for **Windows** and uses the Microsoft C++ compiler (`cl.exe`). The project uses C++17.

You need:

- Windows.
- Visual Studio Build Tools or Visual Studio with the MSVC C++ compiler installed.
- Windows SDK headers and libraries required by the Windows API calls.
- Visual Studio Code, if you want to use the supplied VS Code task.

### Build configuration

The build task is located at:

```text
C++/.vscode/tasks.json
```

The supplied task uses `/std:c++17` and compiles the project source files into:

```text
C++/Main_runtime/main.exe
```

The task sets the working directory to the C++ workspace folder. This matters because several JSON, error-file, and log-file paths are relative paths. When debugging a file-not-found problem, check the process working directory before changing the path in the source code.

To build in VS Code, open the `C++` folder as the workspace and run the configured build task.

### Windows-specific implementation

The serial module uses the Windows API and Windows `HANDLE` values. It is therefore not currently a cross-platform serial implementation. A Linux or macOS port would need a separate serial backend.

---

## 3. Dependencies

### nlohmann/json

The project includes the single-header JSON library **[JSON for Modern C++](https://github.com/nlohmann/json)** by Niels Lohmann and contributors.

- Header in this repository: `Terminal/Login-Register-Presetloading/nlohmann/json.hpp`
- Upstream project: <https://github.com/nlohmann/json>
- License: MIT License. See the upstream repository and included license information for the applicable terms.

The library is used by `UserManager` to read and write `preset-user.json`.

### Windows API

Windows API functions are used for serial communication, console input handling, and device access. The relevant Windows headers are included by the affected source files.

---

## 4. Naming and code conventions

The repository contains some legacy spellings in file names and public function names. They are kept as-is because changing them can break existing `#include` directives or calls.

For new code, use these conventions where practical:

- **Classes and structs:** `PascalCase`, for example `UserManager`, `TerminalOUT`, and `DataPrep`.
- **Functions and variables:** `snake_case`, for example `read_serial_GUI_code_block` and `user_name`.
- **DialogiXMove commands:** uppercase command names, for example `MOVE`, `ENAM`, and `CHAMBER`.
- **Constants:** descriptive names in uppercase or the existing project style.
- **Folders:** group code by module or responsibility.
- **Headers:** declare public interfaces in `.hpp` files; implement non-template functions in `.cpp` files.

### Preserve existing public names

Some existing names contain spelling mistakes, including `serial_conect_GUI`, `serial-conection`, and JSON keys containing `lenght`. Do not rename these casually. Either keep them for compatibility or update every declaration, definition, include, call site, and stored-data migration together.

---

## 5. System overview

The intended command-processing route is:

```text
GUI / Terminal
      │
      ▼
Serial connection
      │
      ▼
GUI-data-prep
(receive lines, assemble blocks, validate syntax)
      │
      ▼
DialogiXMove decoder
(convert command text into typed C++ values)
      │
      ▼
Validation and command handling
      │
      ├──────────────► Robot commands / inverse kinematics
      │
      └──────────────► Chamber commands
      │
      ▼
Execution and hardware communication
      │
      ▼
Status and sensor feedback to the GUI
```

This diagram describes the intended architecture. The validation stage, Python inverse-kinematics integration, command queue, hardware acknowledgement flow, and complete feedback route are still development tasks unless implemented in a newer branch.

The decoder itself does not move the robot. It only parses supported command text and returns C++ data structures. The returned values must be checked and processed by later stages before they are used by hardware-control code.

---

## 6. Terminal input — `TerminalIN`

**Files:**

```text
Terminal/Terminal-IN/Terminal-IN.hpp
Terminal/Terminal-IN/Terminal-IN.cpp
```

`TerminalIN` provides three input functions.

### Public functions

| Function | Return type | Description |
|---|---|---|
| `terminal_read_line()` | `std::string` | Reads one complete line from standard input. |
| `terminal_read_line_int()` | `int` | Reads and validates an integer. It repeats the prompt after invalid input. |
| `terminal_read_password()` | `std::string` | Reads a line while disabling console input echo when a Windows console is available. |

### Example

```cpp
#include <string>
#include "Terminal/Terminal-IN/Terminal-IN.hpp"

int main()
{
    TerminalIN input;

    std::string user_name = input.terminal_read_line();
    int menu_option = input.terminal_read_line_int();
    std::string password = input.terminal_read_password();

    // Use the values in the application.
    return 0;
}
```

### Behavior and debugging

- `terminal_read_line()` returns the line exactly as read; it does not validate the contents.
- `terminal_read_line_int()` uses `std::stoi` and checks that no non-whitespace characters remain after the number. Invalid input and out-of-range values produce configured terminal errors, then the function asks again.
- If standard input reaches end-of-file, `terminal_read_line_int()` returns `0`. Do not automatically interpret that as a valid menu choice.
- `terminal_read_password()` attempts to disable `ENABLE_ECHO_INPUT` on the Windows console and restores the previous console mode afterward. When input is redirected or no console mode is available, hidden input cannot be guaranteed.

---

## 7. Terminal output — `TerminalOUT`

**Files:**

```text
Terminal/Terminal-OUT/Terminal-OUT.hpp
Terminal/Terminal-OUT/Terminal-OUT.cpp
Terminal/Terminal-OUT/error_list.txt
```

`TerminalOUT` centralizes normal output, colored output, and error-message lookup.

### Public functions

| Function | Return type | Description |
|---|---|---|
| `terminal_custom_output(std::string content, std::string color)` | `void` | Prints the supplied content using the supplied ANSI color string, then resets the color. |
| `terminal_standard_output()` | `void` | Prints the standard prompt, `--> `. |
| `terminal_error_output(std::string error_reason)` | `std::string` | Finds an error definition by key and returns the complete configured message. |
| `load_error_message(const std::string config_file_name)` | `std::vector<std::string>` | Loads error definitions from a text file and returns the loaded lines. |

### Error-file format

Each non-empty line in `error_list.txt` should use this format:

```text
error_key - Human-readable explanation
```

For example:

```text
error_only_int - Only integer input is accepted.
```

The key is the part before ` -`. Pass that key to `terminal_error_output()`:

```cpp
std::string message = terminal_out.terminal_error_output("error_only_int");
terminal_out.terminal_custom_output(message, ansi_color_chart::red);
```

If the key is not found, `terminal_error_output()` returns an `Error not found` message.

### Example

```cpp
#include <string>
#include "ansi_color_chart/ansi_color_chart.hpp"
#include "Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "Terminal/Terminal-IN/Terminal-IN.hpp"

int main()
{
    TerminalOUT output;
    TerminalIN input;

    output.load_error_message("Terminal/Terminal-OUT/error_list.txt");

    output.terminal_standard_output();
    std::string text = input.terminal_read_line();
    output.terminal_custom_output(text, ansi_color_chart::green);

    std::string error = output.terminal_error_output("error_only_int");
    output.terminal_custom_output(error, ansi_color_chart::red);

    return 0;
}
```

### Debugging

1. Confirm that `error_list.txt` exists.
2. Confirm that the path is valid relative to the process working directory.
3. Confirm that the error key exactly matches the key in the file. Keys are not automatically corrected for spelling or capitalization.
4. Check that the line uses ` -` between the key and the description.

The implementation also tries the project-relative paths `Terminal/Terminal-OUT/error_list.txt` and `../Terminal/Terminal-OUT/error_list.txt` when the supplied path cannot be loaded.

---

## 8. Serial connection — `Serial`

**Files:**

```text
Arm-logic/Serial-Data-logic/Serial-conection/serial-conection.hpp
Arm-logic/Serial-Data-logic/Serial-conection/serial-conection.cpp
```

The `Serial` class manages three independent serial handles:

- `m_hSerialGUI` — connection to the GUI.
- `m_hSerialCON1` — first controller connection.
- `m_hSerialCON2` — second controller connection.

The header also declares a global instance named `serial`.

### GUI connection

```cpp
std::string serial_conect_GUI(std::string PORT_GUI, int baudrate_GUI);
void disconnect_serial_GUI();
```

Opens the selected COM port and configures the requested baud rate. On success, it returns:

```text
Connection was successful!
```

On failure, it returns an error key, such as `error_opening_port_GUI` or `error_reading_setting_GUI`.

### CON1 connection

```cpp
std::string serial_conect_CON1(std::string PORT_CON1, int baudrate_CON1);
void disconnect_serial_CON1();
```

Uses the same connection process for the CON1 handle.

### CON2 connection

```cpp
std::string serial_conect_CON2(std::string PORT_CON2, int baudrate_CON2);
void disconnect_serial_CON2();
```

Uses the same connection process for the CON2 handle.

### Serial configuration

The current connection functions configure:

- The baud rate supplied by the caller.
- 8 data bits.
- One stop bit.
- No parity.
- Read and write timeouts.

The Windows device path is constructed as `\\.\COMx`, which allows the application to open COM ports using the Windows file API.

### Search for serial ports

```cpp
std::vector<std::string> search_for_serial_ports();
```

Returns the serial-port names discovered by the current Windows enumeration implementation. An empty vector means that no port names were returned by that search call; it does not prove that no serial device is physically connected.

**Implementation note:** In the source archive reviewed for this guide, `search_for_serial_ports()` uses `QueryDosDeviceW()` and filters names beginning with `COM`. That API returns DOS-device names, not the Plug and Play friendly name of the attached board. Therefore, the current `Arduino` / `ESP` / `STM` label checks cannot reliably identify a board from the returned COM name alone. If the working branch has since been changed to enumerate `GUID_DEVINTERFACE_COMPORT` through SetupAPI, update this note to match that implementation.

### Check open connections

```cpp
std::vector<std::string> check_serial_available(
    std::string PORT_GUI, int baudrate_GUI,
    std::string PORT_CON1, int baudrate_CON1,
    std::string PORT_CON2, int baudrate_CON2
);
```

Returns three status strings in this order:

```text
GUI-OK / GUI-NOT-CONECTED
CON1-OK / CON1-NOT-CONECTED
CON2-OK / CON2-NOT-CONECTED
```

**Current implementation detail:** The supplied `.cpp` checks the existing serial handles using `ClearCommError()`. The port-name and baud-rate arguments are present in the function signature but are not used by the current implementation to open or reconfigure connections. Connect the ports first, then use this function to check their handles.

### Example: search, connect, and disconnect

```cpp
#include <iostream>
#include <string>
#include <vector>

#include "Arm-logic/Serial-Data-logic/Serial-conection/serial-conection.hpp"

int main()
{
    std::vector<std::string> ports = serial.search_for_serial_ports();

    if (ports.empty())
    {
        std::cout << "No serial ports found.\n";
        return 0;
    }

    for (const std::string& port : ports)
    {
        std::cout << port << '\n';
    }

    // Use the actual COM name, without any display label such as " | Arduino".
    const std::string status = serial.serial_conect_GUI("COM5", 115200);
    std::cout << status << '\n';

    if (status == "Connection was successful!")
    {
        // Perform serial communication here.
        serial.disconnect_serial_GUI();
    }

    return 0;
}
```

### Serial debugging checklist

- Check Windows Device Manager for the COM number.
- Close Arduino IDE Serial Monitor and other applications that may already have the port open.
- Confirm that the selected COM name is passed without a display suffix such as ` | Arduino`.
- Confirm that the device and application use the same baud rate.
- Check the returned status string and the corresponding key in `error_list.txt`.
- Confirm that a successful connection is disconnected with the matching disconnect function.
- Do not use `check_serial_available()` as a substitute for opening a connection.

---

## 9. GUI data preparation — `DataPrep`

**Files:**

```text
Arm-logic/Serial-Data-logic/GUI-data-prep/GUI-data-prep.hpp
Arm-logic/Serial-Data-logic/GUI-data-prep/GUI-data-prep.cpp
```

`DataPrep` receives and prepares input from the GUI serial connection. A global instance named `data_prep` is declared in the header.

### Public functions and data

| Name | Type | Description |
|---|---|---|
| `read_serial_GUI_per_line()` | `std::string` | Reads one line from the GUI serial handle and validates it. Returns an empty string if no valid line is returned or a read/validation failure occurs. |
| `read_serial_GUI_code_block()` | `std::vector<std::string>` | Waits for a `BEGINN` marker, collects lines until `END`, optionally validates them, and returns the collected lines. |
| `check_incoming_data_validate(const std::string& raw_incoming_data_per_line)` | `bool` | Checks a line against the command grammar defined in `GUI-data-prep.hpp`. |
| `code_save_slot_1` | `std::vector<std::string>` | In-memory code-block slot 1. |
| `code_save_slot_2` | `std::vector<std::string>` | In-memory code-block slot 2. |
| `code_save_slot_3` | `std::vector<std::string>` | In-memory code-block slot 3. |
| `error_return_code_blk` | `std::vector<std::string>` | Stores lines rejected by the validator, together with an error description. |
| `error_count` | `int` | Counts validation errors. |
| `error_buffer` | `std::string` | Holds the most recent validation error text. |

### Code-block protocol

The code-block reader expects this framing:

```text
BEGINN
MOVE 100 200 300 0 0 0
MOVE 110 200 300 0 0 0
END
```

`BEGINN` and `END` are transport markers. The returned vector contains the lines between the markers; the markers themselves are not added to the vector.

### Example: receive a block

A serial connection must already be open before calling this function.

```cpp
#include <string>
#include <vector>

#include "Arm-logic/Serial-Data-logic/GUI-data-prep/GUI-data-prep.hpp"

int main()
{
    std::vector<std::string> code_block = data_prep.read_serial_GUI_code_block();

    for (const std::string& line : code_block)
    {
        // Pass each received line to the next processing stage.
    }

    return 0;
}
```

### Validation behavior

The command grammar is stored in `COMMAND_GRAMMAR` in `GUI-data-prep.hpp`. It currently contains patterns for commands and tokens such as:

- `HAA`, `XSTOPX`, and `XENDX`.
- `ENAM`, `DISM`, `ENAC`, and `DISC` with `ALL` or controller/axis numbers.
- `MOVE` with six numeric values.
- `CHAMBER` operations such as fan, lights, PSU, and sensor-read requests.
- `SINGLE JOINT` and `DO AGAIN` input forms.

The code-block reader asks whether automatic validation should run (`Y/n`). In the current implementation, declining validation still saves the block into an in-memory save slot. If validation is selected and errors are found, the function returns the received block after reporting the errors; the caller must therefore not assume that a non-empty vector is automatically valid.

The three save slots are vectors in memory. The supplied implementation does not persist these slots to the JSON user database.

### Debugging

- No block returned: confirm the sender transmits a newline after `BEGINN`, every command line, and `END`.
- The reader waits indefinitely: confirm that the exact marker is `BEGINN` and that the end marker is `END`.
- A line is rejected: inspect `error_buffer`, `error_count`, and `error_return_code_blk`.
- A block is non-empty but contains invalid commands: check whether automatic validation was skipped or whether the caller ignored the validation errors.
- A line is accepted here but fails in the decoder: compare `COMMAND_GRAMMAR` with the parser rules in the decoder. They are not fully synchronized in the current source.

---

## 10. DialogiXMove decoder — `DeCode`

**Files:**

```text
Arm-logic/DialogiXMove_dekodierer/DialogiXMove_dekodierer.hpp
Arm-logic/DialogiXMove_dekodierer/DialogiXMove_dekodierer.cpp
```

The decoder converts supported DialogiXMove command lines into typed C++ structures. It does **not** calculate inverse kinematics, validate physical movement limits, or execute hardware commands.

### Public decoding functions

```cpp
std::vector<DeCode::CommandResult> DeCode_code_line(std::string code_line);
std::vector<DeCode::CommandResult> DeCode_code_blk(std::vector<std::string> code_blk);
```

- `DeCode_code_line()` decodes one command line. It returns an empty vector if the line does not produce a supported command.
- `DeCode_code_blk()` calls the line decoder for each element in the input vector and collects the successfully decoded results.

`CommandResult` is a `std::variant`. It can contain one of the supported command structures or `std::monostate` for an empty/invalid result.

### Supported command structures

| Command | Data structure | Fields stored by the decoder |
|---|---|---|
| `MOVE` | `DeCode::MOVE` | `X`, `Y`, `Z`, `Rx`, `Ry`, `Rz` — six integers. |
| `ENAM` | `DeCode::ENAM` | `mot_con_nbr` — the second whitespace-separated token. |
| `DISM` | `DeCode::DISM` | `mot_con_nbr` — the second whitespace-separated token. |
| `ENAC` | `DeCode::ENAC` | `axis_con_nbr` — the second whitespace-separated token. |
| `DISC` | `DeCode::DISC` | `axis_con_nbr` — the second whitespace-separated token. |
| `CHAMBER` | `DeCode::CHAMBER` | `part` — currently only the second whitespace-separated token. |
| `JOINT` | `DeCode::JOINT` | `joint_nbr`, `joint_angle` — two integers. |
| `REPEAT` | `DeCode::REPEAT` | `X`, `Y`, `Z`, `Rx`, `Ry`, `Rz`, `repeat_nbr`, `changex`, `changey`, `changez` — ten integers. |

The parser uses uppercase command names and splits the line at whitespace. The command names are case-sensitive in the current implementation.

### Command-line formats accepted by the decoder

```text
MOVE 100 200 300 0 0 0
ENAM 1
DISM 1
ENAC 2
DISC 2
CHAMBER FAN
JOINT 2 90
REPEAT 100 200 300 0 0 0 3 10 0 0
```

These examples show the decoder's current token layout. They do not guarantee that every command is fully validated or ready for hardware execution.

### Example: decode a block and read MOVE values

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <variant>

#include "Arm-logic/DialogiXMove_dekodierer/DialogiXMove_dekodierer.hpp"

int main()
{
    DeCode decoder;

    const std::vector<std::string> code_block = {
        "MOVE 100 200 300 0 0 0",
        "MOVE 400 500 600 0 0 0"
    };

    const std::vector<DeCode::CommandResult> parsed =
        decoder.DeCode_code_blk(code_block);

    for (const auto& command : parsed)
    {
        if (std::holds_alternative<DeCode::MOVE>(command))
        {
            const DeCode::MOVE& move = std::get<DeCode::MOVE>(command);

            std::cout << "X: " << move.X << '\n';
            std::cout << "Y: " << move.Y << '\n';
            std::cout << "Z: " << move.Z << '\n';
            std::cout << "Rx: " << move.Rx << '\n';
            std::cout << "Ry: " << move.Ry << '\n';
            std::cout << "Rz: " << move.Rz << "\n\n";
        }
    }

    return 0;
}
```

Expected output:

```text
X: 100
Y: 200
Z: 300
Rx: 0
Ry: 0
Rz: 0

X: 400
Y: 500
Z: 600
Rx: 0
Ry: 0
Rz: 0
```

### Example: read different command types

Use `std::holds_alternative<T>()` to check the stored type, then `std::get<T>()` to access its fields.

```cpp
for (const auto& command : parsed)
{
    if (std::holds_alternative<DeCode::MOVE>(command))
    {
        const auto& value = std::get<DeCode::MOVE>(command);
        // value.X, value.Y, value.Z, value.Rx, value.Ry, value.Rz
    }
    else if (std::holds_alternative<DeCode::ENAM>(command))
    {
        const auto& value = std::get<DeCode::ENAM>(command);
        // value.mot_con_nbr
    }
    else if (std::holds_alternative<DeCode::DISM>(command))
    {
        const auto& value = std::get<DeCode::DISM>(command);
        // value.mot_con_nbr
    }
    else if (std::holds_alternative<DeCode::ENAC>(command))
    {
        const auto& value = std::get<DeCode::ENAC>(command);
        // value.axis_con_nbr
    }
    else if (std::holds_alternative<DeCode::DISC>(command))
    {
        const auto& value = std::get<DeCode::DISC>(command);
        // value.axis_con_nbr
    }
    else if (std::holds_alternative<DeCode::CHAMBER>(command))
    {
        const auto& value = std::get<DeCode::CHAMBER>(command);
        // value.part
    }
    else if (std::holds_alternative<DeCode::JOINT>(command))
    {
        const auto& value = std::get<DeCode::JOINT>(command);
        // value.joint_nbr, value.joint_angle
    }
    else if (std::holds_alternative<DeCode::REPEAT>(command))
    {
        const auto& value = std::get<DeCode::REPEAT>(command);
        // value.X, value.Y, value.Z, value.Rx, value.Ry, value.Rz,
        // value.repeat_nbr, value.changex, value.changey, value.changez
    }
}
```

### What happens internally

1. `DeCode_code_blk()` iterates over the supplied vector of lines.
2. Each line is passed to `DeCode_code_line()`.
3. `DeCode_code_line()` calls the internal parser.
4. The parser splits the line into whitespace-separated tokens and checks the command name.
5. A supported command is returned as the corresponding structure inside `CommandResult`.
6. The command is added to the corresponding vector in `active_functions` and is also returned in the result vector.

### Decoder debugging and important constraints

- **Use spaces between tokens.** The decoder's `split()` function separates at whitespace, not commas.
- **Use integers for numeric fields.** The current structures store `int` values and the parser uses `std::stoi`.
- **Malformed numbers can throw.** The parser does not catch `std::invalid_argument` or `std::out_of_range` around every `std::stoi` call. Catch decoding exceptions at the caller until structured parser errors are implemented.
- **The current parser checks minimum token counts.** Extra tokens may be ignored because the conditions use `tokens.size() >= ...` rather than requiring an exact count.
- **`CHAMBER` currently stores only one argument token.** For a line such as `CHAMBER FAN ON`, the current decoder stores `FAN` in `part`; it does not store `ON` as part of the value.
- **`active_functions` accumulates commands.** Each successful decode appends to its corresponding member vector. The shown implementation does not clear these vectors automatically before a new block. Clear them explicitly when a fresh per-block summary is required.
- **The decoder is case-sensitive.** Use uppercase command names unless case-insensitive handling is added.

Example of clearing the accumulated vectors before decoding another block:

```cpp
decoder.active_functions.moves.clear();
decoder.active_functions.enam.clear();
decoder.active_functions.dism.clear();
decoder.active_functions.enac.clear();
decoder.active_functions.disc.clear();
decoder.active_functions.chamber.clear();
decoder.active_functions.joint.clear();
decoder.active_functions.repeat.clear();
```

---

## 11. User management — `UserManager`

**Files:**

```text
Terminal/Login-Register-Presetloading/usr-manager/usr-manager.hpp
Terminal/Login-Register-Presetloading/usr-manager/usr-manager.cpp
Terminal/Login-Register-Presetloading/preset-user.json
```

`UserManager` handles user registration, login validation, account deletion, startup text, and timestamp generation. It uses `nlohmann::json` for its database.

### Public interface

| Function / member | Return type | Description |
|---|---|---|
| `startup_terminal(std::string user_name)` | `void` | Prints the project banner and a label for the supplied user name. It does not authenticate that user. |
| `register_user(std::string user_name, std::string password)` | `bool` | Creates a user entry and default preset data. Returns `true` when the database write succeeds. |
| `login_user(std::string user_name, std::string password)` | `bool` | Checks the user and password, then calls the preset loader. |
| `delete_user(std::string user_name, std::string password)` | `bool` | Verifies the credentials and removes the matching user entry. |
| `time()` | `std::string` | Returns the local timestamp in `DD-MM-YYYY HH:MM:SS` format. |
| `presetLoader` | `PresetLoader` | Preset-loader member used during login. |

### Example: register, log in, and delete a user

```cpp
#include <string>
#include "Terminal/Login-Register-Presetloading/usr-manager/usr-manager.hpp"

int main()
{
    UserManager users;

    const std::string username = "operator";
    const std::string password = "example-password";

    if (users.register_user(username, password))
    {
        // Registration succeeded.
    }

    if (users.login_user(username, password))
    {
        // Login and the preset-loader call succeeded.
    }

    // Only call this when account deletion is actually intended.
    // users.delete_user(username, password);

    return 0;
}
```

### Username handling

The implementation converts usernames to lowercase before looking them up or writing them to the database. For example, `Operator`, `OPERATOR`, and `operator` resolve to the same stored key.

Passwords are compared exactly as supplied. They are not converted to lowercase.

### Database path

The class starts with this preferred relative path:

```text
Terminal/Login-Register-Presetloading/preset-user.json
```

The implementation also checks a `../Terminal/Login-Register-Presetloading/preset-user.json` fallback. These paths are relative to the process working directory, not to the `.cpp` file. When the program cannot find or write the database, check the working directory and the path printed by the error output.

### JSON structure

The database has a top-level `users` object. Each username is a key under `users`:

```json
{
  "users": {
    "operator": {
      "password": "<stored password>",
      "created_at": "05-11-2026 18:30:00",
      "presets": {
        "standard_l1_lenght": 210,
        "standard_l2_lenght": 210,
        "standard_l3_lenght": 210,
        "standard_l4_lenght": 210,
        "standard_l5_lenght": 210,
        "standard_l6_lenght": 210,
        "product": "####",
        "axis_1_speed": 50,
        "axis_2_speed": 50,
        "axis_3_speed": 50,
        "axis_4_speed": 50,
        "axis_5_speed": 50,
        "axis_6_speed": 50
      }
    }
  }
}
```

The spelling `lenght` is the spelling currently used by the source code. Do not silently change these JSON keys without updating the code and migrating existing user data.

### Return values and common failures

- `register_user()` returns `false` for empty credentials, an existing username, invalid database structure, JSON parse errors, or a failed write.
- `login_user()` returns `false` when the credentials/database check fails or when `presetLoader.load_user_preset()` returns `false`.
- `delete_user()` returns `false` when credentials cannot be validated or when the database cannot be written.
- The functions print configured errors through `TerminalOUT` and write diagnostic messages through the logger.

### Important security warning

**The current implementation stores passwords as plain text in `preset-user.json`.** It also logs the loaded JSON object during database checking, which can expose those passwords in `log.txt`.

This is not suitable for a production user system. Before using real accounts or distributing the application:

1. Replace plain-text password storage with a suitable salted password-hashing approach.
2. Remove or redact the debug log that writes the complete JSON database.
3. Never log passwords or other credentials.
4. Restrict access to the database and log files.

The terminal password function hides typed characters on a supported console, but that does **not** encrypt or hash the password when it is stored.

---

## 12. Preset management — `PresetLoader`

**Files:**

```text
Terminal/Login-Register-Presetloading/preset-manager/preset-manager.hpp
Terminal/Login-Register-Presetloading/preset-manager/preset-manager.cpp
```

The header declares:

```cpp
bool load_user_preset(std::string user, std::string db_file);
void reset_to_standard_user_preset(std::string user, std::string db_file);
void change_user_preset(
    std::map<std::string, std::string> changes,
    std::string db_file
);
```

It also exposes:

```cpp
std::map<std::string, std::string> active_presets;
```

### Current implementation status

In the source archive reviewed for this guide, `PresetLoader::load_user_preset()` currently returns `true` without loading JSON values. The declared reset function does not have a corresponding implementation in that source snapshot, and the `change_user_preset` implementation is currently a separate free function with a different signature from the class declaration.

Treat preset loading, resetting, and changing as **unfinished** until these implementations are completed and tested. A successful return from the current `load_user_preset()` does not prove that preset values were loaded.

---

## 13. Logging system — `Logging`

**Files:**

```text
Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp
Terminal/Login-Register-Presetloading/logging-system/logging-system.cpp
```

The header declares a global instance named `logger` and the function:

```cpp
std::string log_to(std::string contents);
```

`log_to()` appends a timestamped line to the configured log file. It returns:

- `"OK"` when the write succeeds.
- `"ERROR: Could not open log file."` when the file cannot be opened.
- `"ERROR: Could not write to log file."` when writing fails.

### Example

```cpp
#include "Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

int main()
{
    logger.log_to("[INFO] Application started");
    logger.log_to("[DEBUG] Received a command block");
    return 0;
}
```

### Log location and debugging

The current header sets the path to:

```text
../Terminal/Login-Register-Presetloading/logging-system/log.txt
```

This is a relative path. Its result depends on the process working directory. If logging fails, check that the parent directory exists and that the application has permission to write to it. The logger does not create missing directories.

Use consistent log levels such as `[INFO]`, `[DEBUG]`, `[WARNING]`, and `[ERROR]`. Do not write passwords, tokens, complete credential records, or other secrets to the log.

---

## 14. Terminal interpreter — `TerminalInterpreter`

**Files:**

```text
Terminal/Terminal-Interpreter/Terminal-Interpreter.hpp
Terminal/Terminal-Interpreter/Terminal-Interpreter.cpp
```

The public interface is:

```cpp
void interpret(std::string input);
```

`interpret()` parses the command name and dispatches it to a matching handler in the command map.

### Current implementation status

The supplied implementation currently registers only one command, `test`. Its handler prints `test`. The command map and argument storage are defined in the `.cpp` file, not exposed as public members in the header.

### Example

```cpp
#include "Terminal/Terminal-Interpreter/Terminal-Interpreter.hpp"

int main()
{
    TerminalInterpreter interpreter;
    interpreter.interpret("test");
    return 0;
}
```

Current limitations include limited argument parsing, no quoted-argument handling, and no explicit error output for unknown commands. Extend the parser and command registry before relying on it for a full terminal command interface.

---

## 15. Debugging guide

When a feature fails, follow the data through the modules instead of changing multiple modules at once.

### A. Serial port is not listed

1. Check whether Windows assigns the device a COM number.
2. Check the implementation of `search_for_serial_ports()` in the current branch.
3. Remember that port discovery and opening a port are separate operations.
4. Print or log the exact returned vector before changing the connection code.
5. Confirm that no other application has the port open.

### B. Serial connection fails

1. Print the exact COM name and baud rate being passed to the function.
2. Check the returned status string.
3. Look up that error key in `Terminal/Terminal-OUT/error_list.txt`.
4. Confirm that the matching disconnect function is used for the selected handle.

### C. GUI sends a block but no commands are returned

1. Confirm that the block starts with `BEGINN` and ends with `END`.
2. Print every line returned by `read_serial_GUI_code_block()`.
3. Confirm that the validator accepted each line.
4. Pass only the command lines—not the `BEGINN` and `END` framing markers—to `DeCode_code_blk()`.
5. Print `parsed.size()`.
6. Use `std::holds_alternative<T>()` to check the type of each result before calling `std::get<T>()`.
7. Catch `std::exception` around the decoder call while numeric parsing uses `std::stoi`.

### D. A command passes validation but fails in the decoder

The validator and decoder currently have different syntax rules. Compare the regular expression for the command in `GUI-data-prep.hpp` with the corresponding parser branch in `DialogiXMove_dekodierer.cpp`. See [Known limitations](#16-known-limitations-and-development-notes).

### E. JSON login or registration fails

1. Print the database path selected by `resolve_database_path()`.
2. Confirm that the JSON file is readable and writable.
3. Validate that the root is an object and `users` is also an object.
4. Confirm that the username is stored in lowercase.
5. Check that the user's entry contains a string `password` field.
6. Check the JSON parse details printed by the application.
7. Do not publish logs or database files containing real credentials.

### F. Log file is missing

1. Check the process working directory.
2. Resolve `../Terminal/Login-Register-Presetloading/logging-system/log.txt` from that directory.
3. Confirm that the target directory exists and is writable.
4. Check the return value from `logger.log_to()`.

### Recommended debugging pattern

For each processing stage, record the input, the result, and the failure reason. Avoid logging secrets or sending unvalidated values directly to the hardware layer.

```cpp
logger.log_to("[DEBUG] Starting command decoding");

try
{
    auto parsed = de_code.DeCode_code_blk(code_block);
    logger.log_to("[DEBUG] Parsed command count: " + std::to_string(parsed.size()));
}
catch (const std::exception& error)
{
    logger.log_to(std::string("[ERROR] Decoder exception: ") + error.what());
}
```

---

## 16. Known limitations and development notes

The following points are important when working with the supplied source snapshot. They are documented so that developers do not mistake an interface or validator rule for a fully implemented feature.

1. **Validator/decoder format mismatch:** The GUI validator's `MOVE` regular expression accepts decimal-looking values and comma or whitespace separators. The decoder splits only on whitespace and stores integer fields using `std::stoi`. Use six whitespace-separated integer values until both modules share a single grammar and numeric policy.
2. **`std::stoi` validation:** The decoder does not request or check the position of the last parsed character. A token such as `12.5` can be read as `12` rather than being rejected as a complete invalid integer token. Strict numeric validation is required before hardware use.
3. **Chamber arguments:** The decoder currently stores only the second token for `CHAMBER`. A multi-token operation such as `CHAMBER FAN ON` is not preserved as a complete operation by the current decoder.
4. **Special command naming:** The GUI validator contains `SINGLE JOINT` and `DO AGAIN` grammar entries, while the decoder branches are named `JOINT` and `REPEAT`. These paths need a shared command specification.
5. **Preset manager:** Preset loading and changing are incomplete in the supplied source snapshot.
6. **Serial discovery:** The supplied archive uses `QueryDosDeviceW()` for COM-name enumeration. This does not provide the attached device's Plug and Play friendly name. Check the current branch before documenting a newer SetupAPI implementation.
7. **User credentials:** Passwords are stored as plain text, and a debug statement logs the full JSON database. These must be addressed before use with real accounts.
8. **Relative paths:** Database, error-file, and log-file locations depend on the working directory. Keep the VS Code task's working directory consistent or use paths resolved from a known application directory.
9. **Terminal interpreter:** Only the `test` command is registered in the supplied implementation.

---

## 17. Planned development

The following systems are part of the intended Heavy Core mk1 development plan. They should be marked complete only after implementation and testing in the repository.

- **Input error handling:** Reject malformed, incomplete, out-of-range, and unsupported command values with structured errors.
- **Inverse kinematics:** Pass validated robot-target values to the Python inverse-kinematics program and handle its result or failure.
- **`OLD` arguments:** Allow a MOVE argument to reuse the previous valid target value, for example `MOVE 110 OLD OLD OLD OLD OLD`. Resolve these values in a defined processing stage before IK; distinguish the last commanded target from measured hardware position.
- **Command routing:** Separate robot-motion commands from chamber commands and send each to the correct subsystem.
- **Sequential execution:** Send one command, wait for a defined acknowledgement and completion response, then advance to the next command in the vector/queue. Define timeout and error behavior.
- **Chamber execution:** Apply the same controlled command/response flow to chamber operations.
- **Sensor feedback:** Receive sensor values and device status over serial and forward them to the GUI.
- **GUI improvements:** Display connection state, current feedback, execution progress, and meaningful errors.

---

## 18. Safety note

Heavy Core mk1 is intended to control physical robotic hardware. A command that is syntactically valid is not necessarily safe to execute.

Before enabling physical movement, the control pipeline should include independent validation of joint and Cartesian limits, speed and acceleration limits, communication timeouts, and hardware state. Provide a physical emergency-stop mechanism that does not depend on the GUI or the normal command-processing loop. Test new command paths with motor power disabled or in a controlled, low-risk setup before testing them on an operating mechanism.

The decoder is only a text-to-data conversion stage. It must never be treated as the safety system.

###### `This dok was written by chatgpt with in the prompt the infos.`