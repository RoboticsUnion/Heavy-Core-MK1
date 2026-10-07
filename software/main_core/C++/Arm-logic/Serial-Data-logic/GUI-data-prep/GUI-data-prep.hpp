#pragma once
#include <string>
#include <vector>

class Serial {
    public:
        
        char read_serial_GUI(); // returns raw data unproofed reads it from serial GUI port

        char check_incoming_data(char raw_incoming_data); // returns the proofed data input is raw data

        void save_icoming_data(char incoming_char); // saves incoming chars in to an vektor !ONLY FOR CODE BLOCK!

        std::string read_vektor_data(int line);

    private:
        std::vector<std::string> g_code_buffer; //buffer for the g-code data that is being read from the serial port

        std::string current_line = ""; //current line of data that is being read from the serial port

};