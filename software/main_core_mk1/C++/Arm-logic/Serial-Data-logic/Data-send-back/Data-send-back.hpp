#pragma once
#include <string>

class data_send_back {
    public:
        bool send_data_back_GUI(std::string contents);
        bool send_data_back_CON1(std::string contents);
        bool send_data_back_CON2(std::string contents);

    private:
        
};  

extern data_send_back data_send;