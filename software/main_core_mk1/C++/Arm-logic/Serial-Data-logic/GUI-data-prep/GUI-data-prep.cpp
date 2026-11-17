<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
#include <algorithm>
#include <cctype>
>>>>>>> Stashed changes

DataPrep data_prep;

PresetLoader prset_loader;

TerminalIN terminal_in;

using namespace std;

namespace {

<<<<<<< Updated upstream
    // Append successfully received serial bytes to the pending input buffer.
=======
<<<<<<< Updated upstream
=======
    // Append successfully received serial bytes to the pending input buffer.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
    void incoming_data_handler(
        BOOL success,
        DWORD bytesRead,
        char buffer[],
        string& current_line
        ) {
        if (!success) {
<<<<<<< Updated upstream
            // Preserve the read failure in the log for later diagnosis.
=======
<<<<<<< Updated upstream
=======
            // Preserve the read failure in the log for later diagnosis.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
            DWORD error = GetLastError();
            logger.log_to("[ERROR]" + to_string(error));
            return;
        }

<<<<<<< Updated upstream
        // Keep partial messages buffered until a complete line is available.
=======
<<<<<<< Updated upstream
=======
        // Keep partial messages buffered until a complete line is available.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        if (bytesRead > 0) {
            logger.log_to("[DEBUG]" + to_string(bytesRead));
            current_line.append(buffer, bytesRead);
        }
    }

<<<<<<< Updated upstream
    // Extract one newline-delimited message and remove its line ending.
=======
<<<<<<< Updated upstream
=======
    // Extract one newline-delimited message and remove its line ending.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
    bool extract_line(string& current_line, string& line) {
        size_t newline = current_line.find('\n');

        if (newline == string::npos) {
            return false;
        }

<<<<<<< Updated upstream
        // Consume only the first line so any following data stays buffered.
=======
<<<<<<< Updated upstream
=======
        // Consume only the first line so any following data stays buffered.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        line = current_line.substr(0, newline);
        current_line.erase(0, newline + 1);

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        return true;
    }

    int save_nmbr = 0;

<<<<<<< Updated upstream
    // Rotate through the three saved code-block slots.
    void save_handle(vector<string> code_block) {
        if (save_nmbr >= 3) {
            // Clear all slots before starting a new save cycle.
=======
<<<<<<< Updated upstream
    void save_handle(vector<string> code_block) {// AI overview
        if (save_nmbr >= 3) {
=======
    // Rotate through the three saved code-block slots.
    void save_handle(vector<string> code_block) {
        if (save_nmbr >= 3) {
            // Clear all slots before starting a new save cycle.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
            save_nmbr = 0;
            data_prep.code_save_slot_1.clear();
            data_prep.code_save_slot_2.clear();
            data_prep.code_save_slot_3.clear();
            logger.log_to("Clear saves");
            terminal_out.terminal_custom_output("Cleared saves", ansi_color_chart::green);
        }

<<<<<<< Updated upstream
        // Store the block in the first available slot.
=======
<<<<<<< Updated upstream
        // 2. Save into the next available empty slot
=======
        // Store the block in the first available slot.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
// Read one GUI command, then reject it if it does not match the command grammar.
=======
<<<<<<< Updated upstream
=======
// Read one GUI command, then reject it if it does not match the command grammar.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
string DataPrep::read_serial_GUI_per_line(){
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    do {

        if (extract_line(current_line, line)) {
            break;
        }

<<<<<<< Updated upstream
        // Read more bytes only when the buffer has no complete line.
=======
<<<<<<< Updated upstream
=======
        // Read more bytes only when the buffer has no complete line.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    // Validate the completed line before passing it on to the caller.
    if(data_prep.check_incoming_data_validate(line) == false){
=======
<<<<<<< Updated upstream
    if(data_prep.check_incoming_data_validate(line) == false){ // checking if preset is right from GUI there will be "MOVE X10" ...
=======
    // Validate the completed line before passing it on to the caller.
    if(data_prep.check_incoming_data_validate(line) == false){
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!comm_exist_ln"), ansi_color_chart::red);
        logger.log_to("[ERROR] Line command does not exist");
        return "";
    }
    return line;
}

<<<<<<< Updated upstream
// Read a framed GUI code block and optionally validate it before saving.
=======
<<<<<<< Updated upstream
=======
// Read a framed GUI code block and optionally validate it before saving.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
vector<string> DataPrep::read_serial_GUI_code_block() {
    char buffer[256]; // buffer for incoming line
    DWORD bytesRead = 0;
    string line;
    terminal_out.terminal_custom_output("Waiting for Serial BEGINN ", ansi_color_chart::white);
    logger.log_to("Waiting for Serial BEGINN ");
<<<<<<< Updated upstream

    // Ignore input until the block's opening marker is received.
=======
<<<<<<< Updated upstream
=======

    // Ignore input until the block's opening marker is received.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
    // Collect payload lines until the closing marker is received.
=======
<<<<<<< Updated upstream
=======
    // Collect payload lines until the closing marker is received.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            // Keep payload lines while excluding the protocol's END marker.
=======
<<<<<<< Updated upstream
=======
            // Keep payload lines while excluding the protocol's END marker.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
            code_block.push_back(line);
            logger.log_to("[DEBUG] Line got pushed back: " + line);
        }
    } while(line != "END");

    terminal_out.terminal_custom_output("Serial END", ansi_color_chart::green);
    logger.log_to("Serial END");
    
    terminal_out.terminal_custom_output("Auto validation(Y/n)?", ansi_color_chart::white);
    string choice = terminal_in.terminal_read_line();

<<<<<<< Updated upstream
    // Count validation failures and leave invalid blocks available for correction.
=======
<<<<<<< Updated upstream
=======
    // Count validation failures and leave invalid blocks available for correction.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
        // Save directly when the user declines automatic validation.
=======
<<<<<<< Updated upstream
=======
        // Save directly when the user declines automatic validation.
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        save_handle(code_block);
        terminal_out.terminal_custom_output("Codeblock saved to local variable without checking", ansi_color_chart::green);
        return code_block;
    }

}

<<<<<<< Updated upstream
// Normalize a command line, then check its command name and argument pattern.
=======
<<<<<<< Updated upstream
>>>>>>> Stashed changes
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
=======
// Normalize a command line, then check its command name and argument pattern.
bool DataPrep::check_incoming_data_validate(const string& raw_incoming_data_per_line) {

    terminal_out.terminal_custom_output(
        "Validating: " + raw_incoming_data_per_line,
        ansi_color_chart::white
    );

    logger.log_to("Validating: " + raw_incoming_data_per_line);

    // Remove leading and trailing whitespace
    string cleaned = raw_incoming_data_per_line;

    auto is_space = [](unsigned char c) {
        return std::isspace(c);
    };

    cleaned.erase(
        cleaned.begin(),
        std::find_if(cleaned.begin(), cleaned.end(),
            [&](unsigned char c) { return !is_space(c); })
    );

    cleaned.erase(
        std::find_if(cleaned.rbegin(), cleaned.rend(),
            [&](unsigned char c) { return !is_space(c); }).base(),
        cleaned.end()
    );

    // Ignore empty lines
    if (cleaned.empty()) {
        return true;
    }

    string keyword;
    string args;

    // Special handling for standalone HOME[n]
    if (cleaned.rfind("HOME[", 0) == 0) {
        keyword = "HOME";
        args = cleaned.substr(4);
    }
    else {

        // Separate command name from arguments
        size_t firstSpace = cleaned.find_first_of(" \t");

        if (firstSpace == string::npos) {
            keyword = cleaned;
            args = "";
        }
        else {
            keyword = cleaned.substr(0, firstSpace);
            args = cleaned.substr(firstSpace + 1);
        }
    }

    // Handle multi-word commands
    if (keyword == "SINGLE" && args.rfind("JOINT ", 0) == 0) {
        keyword = "SINGLE JOINT";
        args = args.substr(6);
    }

    // Remove leading whitespace from arguments
    args.erase(
        args.begin(),
        std::find_if(args.begin(), args.end(),
            [&](unsigned char c) { return !is_space(c); })
    );

    // Find command in grammar
    auto it = COMMAND_GRAMMAR.find(keyword);

    if (it == COMMAND_GRAMMAR.end()) {

        error_buffer = "Unknown command name: " + keyword;

        terminal_out.terminal_custom_output(
            error_buffer,
            ansi_color_chart::red
        );

        logger.log_to(error_buffer);

        error_count++;

        error_return_code_blk.push_back(
            raw_incoming_data_per_line + " -> Unknown command"
        );

        return false;
    }

    // Validate command arguments
    if (!std::regex_match(args, it->second)) {

        error_buffer = "Syntax constraints broken for command: " + keyword;

        terminal_out.terminal_custom_output(
            error_buffer,
            ansi_color_chart::yellow
        );

        logger.log_to(error_buffer);

        error_count++;

        error_return_code_blk.push_back(
            raw_incoming_data_per_line + " -> Syntax error"
        );

>>>>>>> Stashed changes
        return false;
    }

    return true;
<<<<<<< Updated upstream

}
<<<<<<< Updated upstream
=======

=======
}
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
