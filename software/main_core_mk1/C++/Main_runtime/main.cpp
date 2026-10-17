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
