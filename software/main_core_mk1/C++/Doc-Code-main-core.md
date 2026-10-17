# Documentation of HeavyMk1 Code

## Naming Conventions
* **Main folders** – Top-level directory structure
* **Sub folders** – Module and feature-specific directories
* **Assets folders** – Static files, configurations, and resources

---

## Core Functions Overview
* **Terminal-IN** – Handles user input via the terminal
* **Terminal-OUT** – Manages terminal text and error outputs
* **Interpret** – Processes and interprets terminal commands
* **Serial-Connection** – Manages connections to serial devices

---

## Detailed Function Reference

### Terminal Modules

#### Terminal - IN
* `terminal_read_line();`
  Reads a line of input from the terminal and returns it as a string.
* `terminal_read_line_int();`
  Reads a line of input from the terminal. Returns it as a string *only* if the input is an integer.
* `terminal_read_password();`
  Reads a line of input while hiding the characters (ideal for passwords).

#### Terminal - OUT
* `terminal_custom_output(std::string content, std::string color);`
  Prints the `content` string in the specified `color` to the terminal.
* `terminal_standard_output();`
  Prints the default terminal prompt (`--> `).
* `terminal_error_output(std::string error_reason);`
  Outputs a formatted error message based on the provided reason.
* `load_error_message(const std::string config_file_name);`
  Loads error definitions from `error_list.txt` and returns them as a vector of strings.

##### Special Error Handling Features
You can load an external configuration file for advanced error reporting:
```cpp
load_error_message(const std::string config_file_name);
```
Using `terminal_error_output(std::string error_reason);` allows easy control over error messages. Simply pass a reason that matches the `"Reason Reasoning"` format configured in your `error.txt`.

```cpp
#include <vector>
#include <string>


#include "../Arm-logic/Serial-Data-logic/Serial-comection/serial-conection.hpp"
#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"

#pragma comment(lib, "OneCore.lib")

using namespace std;

int main() {
    TerminalIN terminal_in;
    TerminalOUT terminal_out;

    terminal_out.load_error_message("../Terminal/Terminal-OUT/error_list.txt");

    terminal_out.terminal_standard_output();

    string read_in = terminal_in.terminal_read_line();

    terminal_out.terminal_custom_output(read_in, ansi_color_chart::red);

    terminal_out.terminal_standard_output();

    int number = terminal_in.terminal_read_line_int();

    string number_str = to_string(number);

    terminal_out.terminal_custom_output(number_str, ansi_color_chart::green);

    terminal_out.terminal_standard_output();

    string pasword = terminal_in.terminal_read_password();

    terminal_out.terminal_custom_output(pasword, ansi_color_chart::red);

    // in error_list.txt "error_only_int - only integer input"

    string error = terminal_out.terminal_error_output("error_only_int");

    terminal_out.terminal_custom_output(error, ansi_color_chart::red);

}

```

---

### Serial Connection Module

#### GUI Port Management
* `serial_conect_GUI(std::string PORT_GUI, int baudrate_GUI);`
  Connects to the serial GUI port using the specified baud rate. Returns a status string.
* `disconnect_serial_GUI();`
  Closes the active connection to the serial GUI port.

#### CON1 Port Management
* `serial_conect_CON1(std::string PORT_CON1, int baudrate_CON1);`
  Connects to the CON1 serial port using the specified baud rate. Returns a status string.
* `disconnect_serial_CON1();`
  Closes the active connection to the CON1 serial port.

#### CON2 Port Management
* `serial_conect_CON2(std::string PORT_CON2, int baudrate_CON2);`
  Connects to the CON2 serial port using the specified baud rate. Returns a status string.
* `disconnect_serial_CON2();`
  Closes the active connection to the CON2 serial port.

#### Utility Functions
* `check_serial_available(std::string PORT_GUI, int baudrate_GUI, std::string PORT_CON1, int baudrate_CON1, std::string PORT_CON2, int baudrate_CON2);`
  Checks availability for GUI, CON1, and CON2 ports simultaneously. Returns a vector of status strings.
* `std::vector<std::string> search_for_serial_ports();`
  Scans the host system for any available serial ports and returns their names in a vector.

```cpp
#include <vector>
#include <string>

#include "../Arm-logic/Serial-Data-logic/Serial-comection/serial-conection.hpp"
#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"

#pragma comment(lib, "OneCore.lib")

using namespace std;

int main() {
    
    Serial serial; 
    TerminalOUT terminal_out;
    TerminalIN terminal_in;

    terminal_out.load_error_message("../Terminal/Terminal-OUT/error_list.txt");

    vector<string> serial_ports = serial.search_for_serial_ports();

    if (serial_ports.empty()) {
        terminal_out.terminal_custom_output("No serial ports found.", ansi_color_chart::yellow);
    } else {
        terminal_out.terminal_custom_output("Available serial ports:", ansi_color_chart::bright_blue);
        short num_ports = serial_ports.size();
        for (int i = 0; i < num_ports; i++) {
            terminal_out.terminal_custom_output(serial_ports[i], ansi_color_chart::white);
        }
    }

    vector<string> status = serial.check_serial_available("COM3", 115200, "COM4", 115200, "COM5", 115200);

    for (const string& port_status : status) {
        terminal_out.terminal_custom_output(port_status, ansi_color_chart::white);
    }

    // Verbindungen testen (Variablenname angepasst)
    serial.serial_conect_CON1("COM3", 115200);
    serial.disconnect_serial_CON1();

    serial.serial_conect_CON1("COM4", 115200);
    serial.disconnect_serial_CON1();

    serial.serial_conect_CON1("COM5", 115200);
    serial.disconnect_serial_CON1();
}

```
#### Output:
The output from the code above
```cpp
Available serial ports:
COM5 | Standard COM
COM4 | Standard COM
Checking conection status to Serial GUI, CON1 and CON2
warning_GUI_ser_disc -The serial conection to the GUI is not opened.
warning_CON1_ser_disc -The serial conection to the CON1 is not opened.
warning_CON2_ser_disc -The serial conection to the CON2 is not opened.
Some serial Ports are disconnected
GUI-NOT-CONECTED
CON1-NOT-CONECTED
CON2-NOT-CONECTED
Trying to connect to: COM3 with BAUD: 115200
error_opening_port_CON1 -An error hapened during opening an port to CON1. Try restart CON1 / check usb conection / WARNING dont use it till it functions normaly!
Trying to connect to: COM4 with BAUD: 115200
error_opening_port_CON1 -An error hapened during opening an port to CON1. Try restart CON1 / check usb conection / WARNING dont use it till it functions normaly!
Trying to connect to: COM5 with BAUD: 115200
Connection was successful!
CON1 Port disconected

```

