#pragma once
#include <string>
#include <vector>

class DataPrep {
    public:
        
        std::string read_serial_GUI_per_line(); // reads line from serial port one line

        std::vector<std::string> read_serial_GUI_code_block(); // reads line from serial port complete code block in vector line to line

        bool check_incoming_data_per_line(std::string raw_incoming_data_per_line); // returns the proofed data input is raw data line

        bool check_incoming_data_code_block(std::vector<std::string> raw_incoming_data_code_block); // returns the proofed data input is raw data vector

        std::vector<std::string> code_save_slot_1; // save slot 1 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> code_save_slot_2; // save slot 2 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> code_save_slot_3; // save slot 3 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> error_return_code_blk; // return variable for existing errors in the code blk

        int error_count = 0; // variable for the errors that are in the code blk

        std::string error_buffer;

    private:
        std::vector<std::string> g_code_buffer; //buffer for the g-code data that is being read from the serial port

        std::string current_line = ""; //current line of data that is being read from the serial port

};

extern DataPrep data_prep;