#include "..\Terminal\Terminal-OUT\Terminal-OUT.hpp" 

#include "../ansi_color_chart/ansi_color_chart.hpp"


#include <iostream>

std::string example = "example_text";

int main() {
    TerminalOUT terminal;
    terminal.terminal_standard_output();
    terminal.terminal_custom_output("\n Custom_output_example\n", ansi_color_chart::blue);
    terminal.terminal_custom_output(example, ansi_color_chart::green);
    std::string error = terminal.terminal_error_output("example_error_reason");
    std::cout << "\n" + error;

}