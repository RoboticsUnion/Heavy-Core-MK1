#include "GUI-data-prep.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../Serial-conection/serial-conection.hpp"

#include "../../../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#include "../../../Terminal/Login-Register-Presetloading/preset-manager/preset-manager.hpp"

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <regex>

DataPrep data_prep;

PresetLoader prset_loader;

TerminalIN terminal_in;

using namespace std;

namespace {

    void incoming_data_handler(
        BOOL success,
        DWORD bytesRead,
        char buffer[],
        string& current_line
        ) {
        if (!success) {
            DWORD error = GetLastError();
            logger.log_to("[ERROR]" + to_string(error));
            return;
        }

        if (bytesRead > 0) {
            logger.log_to("[DEBUG]" + to_string(bytesRead));
            current_line.append(buffer, bytesRead);
        }
    }

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

    int save_nmbr = 0;

    void save_handle(vector<string> code_block) {
        bool save_slots_full = false;

        while (save_slots_full == false) {
            if (data_prep.code_save_slot_1.empty()) {
                data_prep.code_save_slot_1 = code_block;
                save_nmbr++;
                logger.log_to("Saved to 1");
                terminal_out.terminal_custom_output("Saved to 1", ansi_color_chart::green);
                // preset should load in the json
                save_slots_full = true;
            }
            else if (data_prep.code_save_slot_2.empty()) {
                data_prep.code_save_slot_2 = code_block;
                save_nmbr++;
                logger.log_to("Saved to 2");
                terminal_out.terminal_custom_output("Saved to 2", ansi_color_chart::green);
                // preset should load in the json
                save_slots_full = true;
            }
            else if (data_prep.code_save_slot_3.empty()) {
                data_prep.code_save_slot_3 = code_block;
                save_nmbr++;
                logger.log_to("Saved to 3");
                terminal_out.terminal_custom_output("Saved to 3", ansi_color_chart::green);
                // preset should load in the json
                save_slots_full = true;
            }
            else {
                logger.log_to("[ERROR] All save slots are full");
                save_slots_full = true;
            }

            if (save_nmbr == 3) {
                save_nmbr = 0;
                data_prep.code_save_slot_1.clear();
                data_prep.code_save_slot_2.clear();
                data_prep.code_save_slot_3.clear();
                logger.log_to("Clear saves");
                terminal_out.terminal_custom_output("Cleared saves", ansi_color_chart::green);
            }
        }
    }
}

string DataPrep::read_serial_GUI_per_line(){
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    do {

        if (extract_line(current_line, line)) {
            break;
        }

        BOOL success = ReadFile(
            serial.m_hSerialGUI,
            buffer,
            sizeof(buffer),
            &bytesRead,
            nullptr
        );

        incoming_data_handler(
            success, bytesRead, buffer, current_line
        );

        if (!success) {
            return "";
        }
} while (line.empty());

    logger.log_to("[DEBUG]" + line);
    if(data_prep.check_incoming_data_validate(line) == false){ // checking if preset is right from GUI there will be "MOVE X10" ...
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!comm_exist_ln"), ansi_color_chart::red);
        logger.log_to("[ERROR] Line command does not exist");
        return "";
    }
    return line;
}

vector<string> DataPrep::read_serial_GUI_code_block() {
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    terminal_out.terminal_custom_output("Waiting for Serial BEGINN ", ansi_color_chart::white);
    logger.log_to("Waiting for Serial BEGINN ");
    do{
        line.clear();
        if (extract_line(current_line, line)) {

        }else{
            BOOL success = ReadFile(  // read file
                serial.m_hSerialGUI,
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
            incoming_data_handler(success, bytesRead, buffer, data_prep.current_line);
        }
        Sleep(1);
        
    } while(line != "BEGINN");

    terminal_out.terminal_custom_output("Serial BEGINN ", ansi_color_chart::green);
    logger.log_to("Serial BEGINN ");

    vector<string> code_block;

    terminal_out.terminal_custom_output("Reading... waiting for END", ansi_color_chart::white);
    logger.log_to("Reading... waiting for END");

    do{
        line.clear();
        if(extract_line(current_line, line)){

        }else{
            BOOL success = ReadFile(  // read file
                serial.m_hSerialGUI,
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
            incoming_data_handler(success, bytesRead, buffer, data_prep.current_line);

            
        }
        if (!line.empty() && line != "END") {
            code_block.push_back(line);
            logger.log_to("[DEBUG] Line got pushed back: " + line);
        }
    } while(line != "END");

    terminal_out.terminal_custom_output("Serial END", ansi_color_chart::green);
    logger.log_to("Serial END");
    
    terminal_out.terminal_custom_output("Auto validation(Y/n)?", ansi_color_chart::white);
    string choice = terminal_in.terminal_read_line();

    int errors = 0;
    
    if(choice == "Y" || choice == "y"){

        for(const auto& line : code_block) {
            if(check_incoming_data_validate(line) == false){
                errors ++;

            }
        }
        if(errors == 0){
            terminal_out.terminal_custom_output("No errors found!", ansi_color_chart::green);
        } else{
            terminal_out.terminal_custom_output("Errors found! Pleas correct them.", ansi_color_chart::red);
            return code_block;
        }
        save_handle(code_block);
        terminal_out.terminal_custom_output("Codeblock saved to local variable without checking", ansi_color_chart::green);
        return code_block;


    }else{
        save_handle(code_block);
        terminal_out.terminal_custom_output("Codeblock saved to local variable without checking", ansi_color_chart::green);
        return code_block;
    }

}


bool DataPrep::check_incoming_data_validate(const string& raw_incoming_data_per_line){
    terminal_out.terminal_custom_output("Validating: " + raw_incoming_data_per_line, ansi_color_chart::white);
    logger.log_to("Validating: " + raw_incoming_data_per_line);

    string cleaned = raw_incoming_data_per_line;
    while(!cleaned.empty() && (cleaned.back() == ' ' || cleaned.back() == '\r' || cleaned.back() == '\t')) {
        cleaned.pop_back();
    }

    if(cleaned.empty()) return true;

    size_t firstSpace = raw_incoming_data_per_line.find_first_of(" ");
    string keyword = (firstSpace == string::npos) ? "" : raw_incoming_data_per_line.substr(0, firstSpace);
    string args = (firstSpace == string::npos) ? "" : raw_incoming_data_per_line.substr(firstSpace + 1);

    if(keyword == "SINGLE" && args.rfind("JOINT", 0) == 0) {keyword = "SINGLE JOINT"; args = args.substr(6); }
    if (keyword == "DO" && args.rfind("AGAIN", 0) == 0) { keyword = "DO AGAIN"; args = args.substr(6); }

    while(!args.empty() && (args.front() == ' ' || args.front() == ';')) {
        args.erase(0, 1);
    }

    auto it = COMMAND_GRAMMAR.find(keyword);
    if (it == COMMAND_GRAMMAR.end()) {
        error_buffer = "Unknown command name: " + keyword;
        terminal_out.terminal_custom_output(error_buffer, ansi_color_chart::red);
        logger.log_to(error_buffer);
        error_count++;
        error_return_code_blk.push_back(raw_incoming_data_per_line + " -> Unknown command");
        return false;
    }

    if (!regex_match(args, it->second)) {
        error_buffer = "Syntax constraints broken for command: " + keyword;
        terminal_out.terminal_custom_output(error_buffer, ansi_color_chart::yellow);
        logger.log_to(error_buffer);
        error_count++;
        error_return_code_blk.push_back(raw_incoming_data_per_line + " -> Syntax error");
        return false;
    }

    return true;

}

