#include "read-serial-con1-2.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../Serial-conection/serial-conection.hpp"

#include "../../../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#include "../../../Terminal/Login-Register-Presetloading/preset-manager/preset-manager.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>

data_read_back data_rd_bck;

using namespace std;

namespace  {

    // Display a terminal error and record that it was reported.
    void print_error(const std::string& key) {
        terminal_out.terminal_custom_output(
        terminal_out.terminal_error_output(key),
        ansi_color_chart::red
        );
        logger.log_to("[INFO] error output");
    }

    // Remove one complete line from the buffered serial data.
    bool extract_line(string& current_line, string& line) {
        
        size_t newline = current_line.find('\n');

        if (newline == string::npos) {
            return false;
        }

        line = current_line.substr(0, newline);
        current_line.erase(0, newline + 1);

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        return true;
    }

    // Log failed reads and append received bytes for later line parsing.
    void incoming_data_handler(
        BOOL success,
        DWORD bytesRead,
        char buffer[],
        string& current_line
        ) {
        if (!success) {
            DWORD error = GetLastError();
            logger.log_to("[ERROR]" + to_string(error));
            print_error("!READING_CON1_2");
            return;
        }

        if (bytesRead > 0) {
            logger.log_to("[DEBUG]" + to_string(bytesRead));
            current_line.append(buffer, bytesRead);
        }
    }

    // Read until one newline-terminated serial line is available.
    string read_line(HANDLE serial_con1_2){
        char buffer[256]; // buffer for incoming line
        DWORD bytesRead = 0;
        string line;
        do {

            if (extract_line(data_rd_b.current_line, line)) {
                break;
            }

            BOOL success = ReadFile(
                serial_con1_2,
                buffer,
                sizeof(buffer),
                &bytesRead,
                nullptr
            );

            incoming_data_handler(
                success, bytesRead, buffer, data_rd_b.current_line
            );

            if (!success) {
                return "";
                print_error("!READING_CON1_2_HANDLE");
            }
        } while (line.empty());

            logger.log_to("[DEBUG] Controler" + line);
            return line;
        }

    // Wait for BEGINN, then collect lines until the END marker arrives.
    vector<string> read_blk(HANDLE serial_con1_2){
        char buffer[256]; // buffer for incoming line
        DWORD bytesRead = 0;
        string line;
        terminal_out.terminal_custom_output("Waiting for Serial BEGINN ", ansi_color_chart::white);
        logger.log_to("Waiting for Serial BEGINN ");

        do{
            line.clear();
            if (extract_line(data_rd_b.current_line, line)) {

            }else{
                BOOL success = ReadFile(  // read file
                    serial_con1_2,
                    buffer,
                    sizeof(buffer),
                    &bytesRead,
                    nullptr
                );
                if(!success){
                    DWORD error = GetLastError();
                    logger.log_to("[ERROR] " + to_string(error));
                    return {};
                }
                incoming_data_handler(success, bytesRead, buffer, data_rd_b.current_line);
            }
            Sleep(1);
                
        } while(line != "BEGINN");

        terminal_out.terminal_custom_output("Serial BEGINN ", ansi_color_chart::green);
        logger.log_to("Serial BEGINN ");

    // Keep only non-empty payload lines; protocol markers are excluded.
    vector<string> code_block;

    terminal_out.terminal_custom_output("Reading... waiting for END", ansi_color_chart::white);
    logger.log_to("Reading... waiting for END");

    do{
        line.clear();
        if(extract_line(data_rd_b.current_line, line)){

        }else{
            BOOL success = ReadFile(  // read file
                serial_con1_2,
                buffer,
                sizeof(buffer),
                &bytesRead,
                nullptr
            );
            if(!success) {
                DWORD error = GetLastError();
                logger.log_to("[ERROR] " + to_string(error));
                return {};
            }
            incoming_data_handler(success, bytesRead, buffer, data_rd_b.current_line);
                
        }
        if (!line.empty() && line != "END") {
            code_block.push_back(line);
            logger.log_to("[DEBUG] Line got pushed back: " + line);
        }
    } while(line != "END");

    terminal_out.terminal_custom_output("Serial END", ansi_color_chart::green);
    logger.log_to("Serial END");
    }

}

// Read one line from the first serial connection.
std::string data_read_back::read_data_back_line_CON1(){
    return read_line(serial.m_hSerialCON1);
    
}

// Read a framed data block from the second serial connection.
std::vector<std::string> data_read_back::read_data_back_blk_CON2(){
    return read_blk(serial.m_hSerialCON2);
}

// Read one line from the second serial connection.
std::string data_read_back::read_data_back_line_CON2(){
    return read_line(serial.m_hSerialCON2);
    
}

// Read a framed data block from the first serial connection.
std::vector<std::string> data_read_back::read_data_back_blk_CON1(){
    return read_blk(serial.m_hSerialCON1);
}
