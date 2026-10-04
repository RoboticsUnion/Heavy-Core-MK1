#pragma once
#include <string>
#include <vector>

class TerminalIN {
    public:
        std::string terminal_read_line(); //reads a line of input from the terminal and returns it as a string
        int terminal_read_line_int(); //reads a line of input from the terminal and returns it as a string, but only if the input is an integer
        std::string terminal_read_password(); //reads a line of input from the terminal and returns it as a string, but hides the input from the terminal (for password input)

    private:
};