#include "GUI-data-prep.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../Serial-conection/serial-conection.hpp"

#include "../../../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

DataPrep data_prep;

using namespace std;

namespace{
    string incoming_data_handler(BOOL success, DWORD bytesRead, char buffer[], string& current_line) {
        if (!success){ // checks if smth went wrong

            DWORD error = GetLastError();
            logger.log_to("[ERROR]" + to_string(error));
            return "";
        }

        if (bytesRead > 0) {
            logger.log_to("[DEBUG]" + to_string(bytesRead));
            current_line.append(buffer, bytesRead);
        }

        size_t newline = current_line.find('\n');

        if (newline == string::npos) {
            return "";
        }

        std::string line = current_line.substr(0, newline);
        current_line.erase(0, newline + 1);

        if (!line.empty() && line.back() == '\r'){  // line pop_back
        
            line.pop_back();
        }

        return line;
        }
}

string DataPrep::read_serial_GUI_per_line()
{
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    BOOL success = ReadFile(  // read file
        serial.m_hSerialGUI,
        buffer,
        sizeof(buffer),
        &bytesRead,
        nullptr
    );

    string line = incoming_data_handler(success, bytesRead, buffer, data_prep.current_line);

    logger.log_to("[DEBUG]" + line);

    return line;
}

vector<string> DataPrep::read_serial_GUI_code_block() {
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    do{
        BOOL success = ReadFile(  // read file
            serial.m_hSerialGUI,
            buffer,
            sizeof(buffer),
            &bytesRead,
            nullptr
        );
        line = incoming_data_handler(success, bytesRead, buffer, data_prep.current_line);
        Sleep(1);
    } while(line != "BEGIN");

    vector<string> code_block;

    do{
        BOOL success = ReadFile(  // read file
            serial.m_hSerialGUI,
            buffer,
            sizeof(buffer),
            &bytesRead,
            nullptr
        );
        line = incoming_data_handler(success, bytesRead, buffer, data_prep.current_line);
        if (!line.empty() && line != "END") {
            code_block.push_back(line);
        }
    } while(line != "END");

    return code_block;

}