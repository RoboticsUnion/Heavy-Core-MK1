#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

class DataPrep {
    public:
        
        std::string read_serial_GUI_per_line(); // reads line from serial port one line

        std::vector<std::string> read_serial_GUI_code_block(); // reads line from serial port complete code block in vector line to line

        bool check_incoming_data_validate(const std::string& raw_incoming_data_per_line); // returns the proofed data input is raw data line


        std::vector<std::string> code_save_slot_1; // save slot 1 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> code_save_slot_2; // save slot 2 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> code_save_slot_3; // save slot 3 for a code block only variable should been loaded when you login out of json

        std::vector<std::string> error_return_code_blk; // return variable for existing errors in the code blk

        int error_count = 0; // variable for the errors that are in the code blk

        std::string error_buffer;


    private:
        std::vector<std::string> g_code_buffer; //buffer for the g-code data that is being read from the serial port

        std::string current_line = ""; //current line of data that is being read from the serial port

        const std::unordered_map<std::string, std::regex> COMMAND_GRAMMAR = { //COMMAND list for checking
            {"HAA",            std::regex(R"(^\s*(#|1|DUMMY)?\s*$)")},
            {"XSTOPX",         std::regex(R"(^\s*(#|1|DUMMY)?\s*$)")},
            {"XENDX",          std::regex(R"(^\s*(#|1|DUMMY)?\s*$)")},
            {"END",            std::regex(R"(^\s*(#|1|DUMMY)?\s*$)")},
            {"BEGINN",         std::regex(R"(^\s*(#|1|DUMMY)?\s*$)")},

            {"ENAM",         std::regex(R"(^\s*(ALL|[1-6]([,\s]+[1-6])*)\s*$)")},
            {"DISM",         std::regex(R"(^\s*(ALL|[1-6]([,\s]+[1-6])*)\s*$)")},
            {"ENAC",         std::regex(R"(^\s*(ALL|[1-6]([,\s]+[1-6])*)\s*$)")},
            {"DISC",         std::regex(R"(^\s*(ALL|[1-6]([,\s]+[1-6])*)\s*$)")},

            {"MOVE",         std::regex(R"(^\s*(-?\d+\.?\d*([,\s]+-?\d+\.?\d*){5})\s*$)")},
    
            {"CHAMBER",      std::regex(R"(^\s*(FAN (ON|OFF|SPEED\+|SPEED-|AUTO)|LIGHTS (ON|OFF)|PSU (ON|OFF)|READ - (HUM|PRESS|TEMP|CONTROLER TEMP))\s*$)")},
    
            {"SINGLE JOINT", std::regex(R"(^\s*MOVE[,\s]+[1-7][,\s]+-?\d+\.?\d*\s*$)")},
    
            {"DO AGAIN",     std::regex(R"(^.+$)")} 
        };

};

extern DataPrep data_prep;