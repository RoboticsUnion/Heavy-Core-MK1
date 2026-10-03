#pragma once
#include <string>
#include <vector>

class TerminalOUT {
    public:
        void terminal_custom_output(std::string content, std::string color);

        void terminal_standard_output();

        std::string terminal_error_output(std::string error_reason);

        std::vector<std::string> load_error_message(const std::string config_file_name);



    private:
        const std::string standard_output = "--> ";

        const std::string config_file_name = "../Terminal/Terminal-OUT/error_list.txt";

        std::vector<std::string> errors = load_error_message(config_file_name);

};