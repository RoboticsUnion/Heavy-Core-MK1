#pragma once
#include <string>
#include <vector>

class TerminalOUT {
    public:
        void terminal_custom_output(std::string content, std::string color); //gives you the custom output for the terminal, which is the content passed to the function with the color passed to the function

        void terminal_standard_output(); //gives you the standard output for the terminal, which is "--> "

        std::string terminal_error_output(std::string error_reason); //gives you the error output for the terminal, which is the error message corresponding to the error reason passed to the function

        std::vector<std::string> load_error_message(const std::string config_file_name); // loads the error messages from the file "error_list.txt" and returns them as a vector of strings



    private:
        const std::string standard_output = "--> ";

        const std::string config_file_name = "../Terminal/Terminal-OUT/error_list.txt";

        std::vector<std::string> errors = load_error_message(config_file_name);

};