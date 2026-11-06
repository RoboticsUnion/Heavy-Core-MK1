#pragma once
#include <string>
#include <vector>

class data_read_back {
    public:
        std::string read_data_back_line_CON1();
        std::vector<std::string> read_data_back_blk_CON2();

        std::string read_data_back_line_CON2();
        std::vector<std::string> read_data_back_blk_CON1();

        std::string current_line = ""; //current line of data that is being read from the serial port


    private:
        
        
        
};

extern data_read_back data_rd_b;