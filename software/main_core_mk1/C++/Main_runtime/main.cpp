#include <iostream>
#include <vector>
#include <string>
#include <windows.h>


#include "../Arm-logic/Serial-Data-logic/Serial-comection/serial-conection.hpp"
#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"

// 2. Bindet die Windows-Bibliothek für GetCommPorts direkt beim Linken ein
#pragma comment(lib, "OneCore.lib")


using namespace std;

// Globale Testvariable (jetzt kennt der Compiler std::string!)
std::string example = "example_text";

int main() {
    Serial Serial;
    TerminalOUT terminal_out;
    TerminalIN terminal_in;

    terminal_out.load_error_message("../Terminal/Terminal-OUT/error_list.txt");

    vector<string> serial_ports = Serial.search_for_serial_ports();

    int i;

    if (serial_ports.empty()) {
        terminal_out.terminal_custom_output("No serial ports found.", ansi_color_chart::yellow);
    } else {
        terminal_out.terminal_custom_output("Available serial ports:", ansi_color_chart::bright_blue);
        short num_ports = serial_ports.size();
        for (i = 0; i < num_ports; i++) {
            terminal_out.terminal_custom_output(serial_ports[i], ansi_color_chart::white);
        }
    }

}
