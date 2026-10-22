#pragma once
#include <string>


class Logging {
    public:
        std::string log_to(std::string contents);

    private:
        std::string log_txt_path = "log.txt";
};  

extern Logging log;