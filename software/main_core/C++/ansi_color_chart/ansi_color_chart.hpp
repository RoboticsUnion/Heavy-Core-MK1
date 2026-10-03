#pragma once
#include <string>

namespace ansi_color_chart {
    const std::string reset = "\033[0m";
    const std::string bold = "\033[1m";
    const std::string underline = "\033[4m";
    const std::string blink = "\033[5m";
    const std::string reverse = "\033[7m";
    const std::string hidden = "\033[8m";
    const std::string strikethrough = "\033[9m";
    
    const std::string black = "\033[30m";
    const std::string red = "\033[31m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string blue = "\033[34m";
    const std::string magenta = "\033[35m";
    const std::string cyan = "\033[36m";
    const std::string white = "\033[37m";
    const std::string bright_black = "\033[90m";
    const std::string bright_red = "\033[91m";
    const std::string bright_green = "\033[92m";
    const std::string bright_yellow = "\033[93m";
    const std::string bright_blue = "\033[94m";
    const std::string bright_magenta = "\033[95m";
    const std::string bright_cyan = "\033[96m";
    const std::string bright_white = "\033[97m";
    const std::string bg_black = "\033[40m";
    const std::string bg_red = "\033[41m";
    const std::string bg_green = "\033[42m";
    const std::string bg_yellow = "\033[43m";
    const std::string bg_blue = "\033[44m";
    const std::string bg_magenta = "\033[45m";
    const std::string bg_cyan = "\033[46m";
    const std::string bg_white = "\033[47m";
    const std::string bg_bright_black = "\033[100m";
    const std::string bg_bright_red = "\033[101m";
    const std::string bg_bright_green = "\033[102m";
    const std::string bg_bright_yellow = "\033[103m";
    const std::string bg_bright_blue = "\033[104m";
    const std::string bg_bright_magenta = "\033[105m";
    const std::string bg_bright_cyan = "\033[106m";
    const std::string bg_bright_white = "\033[107m";
}