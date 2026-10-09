#include "..\Terminal\Terminal-OUT\Terminal-OUT.hpp" 

#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"
#include "../Arm-logic/Serial-Data-logic/Serial-comection/serial-conection.hpp"


#include <iostream>
#include <vector>

using namespace std;

std::string example = "example_text";

int main() {
    TerminalOUT terminal_out;
    TerminalIN terminal_in;
    Serial Serial;

    terminal_out.load_error_message("../Terminal/Terminal-OUT/error_list.txt");

    terminal_out.terminal_custom_output("Input PORT: ", ansi_color_chart::green);
    string port = terminal_in.terminal_read_line();
    terminal_out.terminal_custom_output("Input baudrate: ", ansi_color_chart::green);
    int baudrate = terminal_in.terminal_read_line_int();

    Serial.serial_conect_GUI(port, baudrate);

    vector<string> output = Serial.check_serial_available(port, baudrate, "COM10", 11435, "COM10", 11435);
    terminal_out.terminal_custom_output(output[0], ansi_color_chart::green);

}