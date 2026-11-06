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

    // Append successfully received serial bytes to the pending input buffer.
    void incoming_data_handler(
        BOOL success,
        DWORD bytesRead,
        char buffer[],
        string& current_line
        ) {
        if (!success) {
            // Preserve the read failure in the log for later diagnosis.
            DWORD error = GetLastError();
            logger.log_to("[ERROR]" + to_string(error));
            return;
        }

        // Keep partial messages buffered until a complete line is available.
        if (bytesRead > 0) {
            logger.log_to("[DEBUG]" + to_string(bytesRead));
            current_line.append(buffer, bytesRead);
        }
    }

    // Extract one newline-delimited message and remove its line ending.
    bool extract_line(string& current_line, string& line) {
        size_t newline = current_line.find('\n');

        if (newline == string::npos) {
            return false;
        }

        // Consume only the first line so any following data stays buffered.
        line = current_line.substr(0, newline);
        current_line.erase(0, newline + 1);

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        return true;
    }

    int save_nmbr = 0;

    // Rotate through the three saved code-block slots.
    void save_handle(vector<string> code_block) {
        if (save_nmbr >= 3) {
            // Clear all slots before starting a new save cycle.
            save_nmbr = 0;
            data_prep.code_save_slot_1.clear();
            data_prep.code_save_slot_2.clear();
            data_prep.code_save_slot_3.clear();
            logger.log_to("Clear saves");
            terminal_out.terminal_custom_output("Cleared saves", ansi_color_chart::green);
        }

        // Store the block in the first available slot.
        if (data_prep.code_save_slot_1.empty()) {
            data_prep.code_save_slot_1 = code_block;
            save_nmbr++;
            logger.log_to("Saved to 1");
            terminal_out.terminal_custom_output("Saved to 1", ansi_color_chart::green);
        }
        else if (data_prep.code_save_slot_2.empty()) {
            data_prep.code_save_slot_2 = code_block;
            save_nmbr++;
            logger.log_to("Saved to 2");
            terminal_out.terminal_custom_output("Saved to 2", ansi_color_chart::green);
        }
        else if (data_prep.code_save_slot_3.empty()) {
            data_prep.code_save_slot_3 = code_block;
            save_nmbr++;
            logger.log_to("Saved to 3");
            terminal_out.terminal_custom_output("Saved to 3", ansi_color_chart::green);
        }
        else {
            logger.log_to("[ERROR] All save slots are full");
            terminal_out.terminal_custom_output("All slots full! Clear them manually or restart.", ansi_color_chart::red);
        }
}
}

// Read one GUI command, then reject it if it does not match the command grammar.
string DataPrep::read_serial_GUI_per_line(){
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    do {

        if (extract_line(current_line, line)) {
            break;
        }

        // Read more bytes only when the buffer has no complete line.
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
    // Validate the completed line before passing it on to the caller.
    if(data_prep.check_incoming_data_validate(line) == false){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!comm_exist_ln"), ansi_color_chart::red);
        logger.log_to("[ERROR] Line command does not exist");
        return "";
    }
    return line;
}

// Read a framed GUI code block and optionally validate it before saving.
vector<string> DataPrep::read_serial_GUI_code_block() {
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    terminal_out.terminal_custom_output("Waiting for Serial BEGINN ", ansi_color_chart::white);
    logger.log_to("Waiting for Serial BEGINN ");

    // Ignore input until the block's opening marker is received.
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

    // Collect payload lines until the closing marker is received.
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
            // Keep payload lines while excluding the protocol's END marker.
            code_block.push_back(line);
            logger.log_to("[DEBUG] Line got pushed back: " + line);
        }
    } while(line != "END");

    terminal_out.terminal_custom_output("Serial END", ansi_color_chart::green);
    logger.log_to("Serial END");
    
    terminal_out.terminal_custom_output("Auto validation(Y/n)?", ansi_color_chart::white);
    string choice = terminal_in.terminal_read_line();

    // Count validation failures and leave invalid blocks available for correction.
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
        terminal_out.terminal_custom_output("Codeblock saved to local variable checking", ansi_color_chart::green);
        return code_block;


    }else{
        // Save directly when the user declines automatic validation.
        save_handle(code_block);
        terminal_out.terminal_custom_output("Codeblock saved to local variable without checking", ansi_color_chart::green);
        return code_block;
    }

}

// Normalize a command line, then check its command name and argument pattern.
bool DataPrep::check_incoming_data_validate(const string& raw_incoming_data_per_line){
    terminal_out.terminal_custom_output("Validating: " + raw_incoming_data_per_line, ansi_color_chart::white);
    logger.log_to("Validating: " + raw_incoming_data_per_line);

    // Ignore trailing whitespace and accept blank lines.
    string cleaned = raw_incoming_data_per_line;
    while(!cleaned.empty() && (cleaned.back() == ' ' || cleaned.back() == '\r' || cleaned.back() == '\t')) {
        cleaned.pop_back();
    }

    if(cleaned.empty()) return true;

    // Separate the command name from its remaining arguments.
    size_t firstSpace = raw_incoming_data_per_line.find_first_of(" ");
    string keyword = (firstSpace == string::npos) ? "" : raw_incoming_data_per_line.substr(0, firstSpace);
    string args = (firstSpace == string::npos) ? "" : raw_incoming_data_per_line.substr(firstSpace + 1);

    // Combine multi-word command names before looking them up in the grammar.
    if(keyword == "SINGLE" && args.rfind("JOINT", 0) == 0) {keyword = "SINGLE JOINT"; args = args.substr(6); }
    if (keyword == "DO" && args.rfind("AGAIN", 0) == 0) { keyword = "DO AGAIN"; args = args.substr(6); }

    while(!args.empty() && (args.front() == ' ' || args.front() == ';')) {
        args.erase(0, 1);
    }

    // Report unknown commands separately from malformed arguments.
    auto it = COMMAND_GRAMMAR.find(keyword);
    if (it == COMMAND_GRAMMAR.end()) {
        error_buffer = "Unknown command name: " + keyword;
        terminal_out.terminal_custom_output(error_buffer, ansi_color_chart::red);
        logger.log_to(error_buffer);
        error_count++;
        error_return_code_blk.push_back(raw_incoming_data_per_line + " -> Unknown command");
        return false;
    }

    // Match the remaining arguments against this command's registered pattern.
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
