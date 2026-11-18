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
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;

DataPrep data_prep;
PresetLoader prset_loader;
TerminalIN terminal_in;

namespace {

    // Append successfully received serial bytes to the pending input buffer.
    void incoming_data_handler(
        BOOL success,
        DWORD bytesRead,
        const char buffer[],
        string& current_line
    ) {
        if (!success) {
            const DWORD error = GetLastError();
            logger.log_to("[ERROR] " + to_string(error));
            return;
        }

        if (bytesRead > 0) {
            logger.log_to("[DEBUG] Received " + to_string(bytesRead) + " serial bytes");
            current_line.append(buffer, bytesRead);
        }
    }

    // Extract one complete newline-terminated line from the receive buffer.
    bool extract_line(string& current_line, string& line) {
        const size_t newline = current_line.find('\n');

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

    // Save code blocks in three rotating slots.
    void save_handle(const vector<string>& code_block) {
        if (save_nmbr >= 3) {
            save_nmbr = 0;
            data_prep.code_save_slot_1.clear();
            data_prep.code_save_slot_2.clear();
            data_prep.code_save_slot_3.clear();

            logger.log_to("Cleared all code-block save slots");
            terminal_out.terminal_custom_output(
                "Cleared saves",
                ansi_color_chart::green
            );
        }

        if (data_prep.code_save_slot_1.empty()) {
            data_prep.code_save_slot_1 = code_block;
            ++save_nmbr;
            logger.log_to("Saved code block to slot 1");
            terminal_out.terminal_custom_output("Saved to 1", ansi_color_chart::green);
        }
        else if (data_prep.code_save_slot_2.empty()) {
            data_prep.code_save_slot_2 = code_block;
            ++save_nmbr;
            logger.log_to("Saved code block to slot 2");
            terminal_out.terminal_custom_output("Saved to 2", ansi_color_chart::green);
        }
        else if (data_prep.code_save_slot_3.empty()) {
            data_prep.code_save_slot_3 = code_block;
            ++save_nmbr;
            logger.log_to("Saved code block to slot 3");
            terminal_out.terminal_custom_output("Saved to 3", ansi_color_chart::green);
        }
        else {
            logger.log_to("[ERROR] All save slots are full");
            terminal_out.terminal_custom_output(
                "All slots full! Clear them manually or restart.",
                ansi_color_chart::red
            );
        }
    }
}

string DataPrep::read_serial_GUI_per_line() {
    char buffer[256];
    DWORD bytesRead = 0;
    string line;

    do {
        if (extract_line(current_line, line)) {
            break;
        }

        const BOOL success = ReadFile(
            serial.m_hSerialGUI,
            buffer,
            sizeof(buffer),
            &bytesRead,
            nullptr
        );

        if (!success) {
            const DWORD error = GetLastError();
            logger.log_to("[ERROR] Serial read failed: " + to_string(error));
            return "";
        }

        incoming_data_handler(success, bytesRead, buffer, current_line);
    } while (line.empty());

    logger.log_to("[DEBUG] Received line: " + line);

    if (!check_incoming_data_validate(line)) {
        terminal_out.terminal_custom_output(
            terminal_out.terminal_error_output("!comm_exist_ln"),
            ansi_color_chart::red
        );
        logger.log_to("[ERROR] Line command does not exist or is invalid");
        return "";
    }

    return line;
}

vector<string> DataPrep::read_serial_GUI_code_block() {
    char buffer[256];
    DWORD bytesRead = 0;
    string line;

    terminal_out.terminal_custom_output(
        "Waiting for Serial BEGINN",
        ansi_color_chart::white
    );
    logger.log_to("Waiting for Serial BEGINN");

    // Wait for the BEGINN marker.
    do {
        line.clear();

        if (!extract_line(current_line, line)) {
            const BOOL success = ReadFile(
                serial.m_hSerialGUI,
                buffer,
                sizeof(buffer),
                &bytesRead,
                nullptr
            );

            if (!success) {
                const DWORD error = GetLastError();
                logger.log_to("[ERROR] Serial read failed: " + to_string(error));
                return {};
            }

            incoming_data_handler(success, bytesRead, buffer, current_line);
        }

        if (line.empty()) {
            Sleep(1);
        }
    } while (line != "BEGINN");

    terminal_out.terminal_custom_output("Serial BEGINN", ansi_color_chart::green);
    logger.log_to("Serial BEGINN");

    vector<string> code_block;

    terminal_out.terminal_custom_output(
        "Reading code block... waiting for END",
        ansi_color_chart::white
    );
    logger.log_to("Reading code block... waiting for END");

    // Collect payload lines until the closing END marker arrives.
    do {
        line.clear();

        if (!extract_line(current_line, line)) {
            const BOOL success = ReadFile(
                serial.m_hSerialGUI,
                buffer,
                sizeof(buffer),
                &bytesRead,
                nullptr
            );

            if (!success) {
                const DWORD error = GetLastError();
                logger.log_to("[ERROR] Serial read failed: " + to_string(error));
                return {};
            }

            incoming_data_handler(success, bytesRead, buffer, current_line);
            Sleep(1);
            continue;
        }

        if (!line.empty() && line != "END") {
            code_block.push_back(line);
            logger.log_to("[DEBUG] Added code-block line: " + line);
        }
    } while (line != "END");

    terminal_out.terminal_custom_output("Serial END", ansi_color_chart::green);
    logger.log_to("Serial END");

    terminal_out.terminal_custom_output("Auto validation (Y/n)?", ansi_color_chart::white);
    const string choice = terminal_in.terminal_read_line();

    if (choice == "Y" || choice == "y") {
        int errors = 0;

        for (const auto& code_line : code_block) {
            if (!check_incoming_data_validate(code_line)) {
                ++errors;
            }
        }

        if (errors == 0) {
            terminal_out.terminal_custom_output(
                "No errors found!",
                ansi_color_chart::green
            );
        }
        else {
            terminal_out.terminal_custom_output(
                "Errors found! Please correct them.",
                ansi_color_chart::red
            );
            return code_block;
        }

        save_handle(code_block);
        terminal_out.terminal_custom_output(
            "Code block saved locally after validation",
            ansi_color_chart::green
        );
        return code_block;
    }

    // Save directly if automatic validation was declined.
    save_handle(code_block);
    terminal_out.terminal_custom_output(
        "Code block saved locally without validation",
        ansi_color_chart::green
    );
    return code_block;
}

// Normalize a command line, then check its command name and argument pattern.
bool DataPrep::check_incoming_data_validate(const string& raw_incoming_data_per_line) {
    terminal_out.terminal_custom_output(
        "Validating: " + raw_incoming_data_per_line,
        ansi_color_chart::white
    );
    logger.log_to("Validating: " + raw_incoming_data_per_line);

    auto is_space = [](unsigned char character) {
        return std::isspace(character) != 0;
    };

    // Trim leading and trailing whitespace before parsing.
    string cleaned = raw_incoming_data_per_line;

    cleaned.erase(
        cleaned.begin(),
        find_if(cleaned.begin(), cleaned.end(),
            [&](unsigned char character) { return !is_space(character); })
    );

    cleaned.erase(
        find_if(cleaned.rbegin(), cleaned.rend(),
            [&](unsigned char character) { return !is_space(character); }).base(),
        cleaned.end()
    );

    if (cleaned.empty()) {
        return true;
    }

    string keyword;
    string args;

    // HOME[n] is a command whose argument is attached directly to its name.
    if (cleaned.rfind("HOME[", 0) == 0) {
        keyword = "HOME";
        args = cleaned.substr(4);
    }
    else {
        const size_t first_space = cleaned.find_first_of(" \t");

        if (first_space == string::npos) {
            keyword = cleaned;
            args.clear();
        }
        else {
            keyword = cleaned.substr(0, first_space);
            args = cleaned.substr(first_space + 1);
        }
    }

    // Recognize the supported two-word command names.
    if (keyword == "SINGLE" && args.rfind("JOINT", 0) == 0) {
        keyword = "SINGLE JOINT";
        args.erase(0, 5);
    }
    else if (keyword == "DO" && args.rfind("AGAIN", 0) == 0) {
        keyword = "DO AGAIN";
        args.erase(0, 5);
    }

    // Remove whitespace and optional semicolon separators before the arguments.
    while (!args.empty() &&
           (is_space(static_cast<unsigned char>(args.front())) || args.front() == ';')) {
        args.erase(args.begin());
    }

    const auto it = COMMAND_GRAMMAR.find(keyword);

    if (it == COMMAND_GRAMMAR.end()) {
        error_buffer = "Unknown command name: " + keyword;

        terminal_out.terminal_custom_output(error_buffer, ansi_color_chart::red);
        logger.log_to(error_buffer);

        ++error_count;
        error_return_code_blk.push_back(
            raw_incoming_data_per_line + " -> Unknown command"
        );
        return false;
    }

    if (!regex_match(args, it->second)) {
        error_buffer = "Syntax constraints broken for command: " + keyword;

        terminal_out.terminal_custom_output(error_buffer, ansi_color_chart::yellow);
        logger.log_to(error_buffer);

        ++error_count;
        error_return_code_blk.push_back(
            raw_incoming_data_per_line + " -> Syntax error"
        );
        return false;
    }

    return true;
}
