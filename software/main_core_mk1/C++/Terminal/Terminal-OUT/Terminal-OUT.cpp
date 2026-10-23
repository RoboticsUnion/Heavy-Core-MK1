#include "Terminal-OUT.hpp"

#include "../../ansi_color_chart/ansi_color_chart.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {
    vector<string> read_error_file(const string& path) {
        ifstream in(path);
        vector<string> messages;
        if (!in.is_open()) {
            return messages;
        }

        string line;
        while (getline(in, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                messages.push_back(line);
            }
        }
        return messages;
    }

    vector<string> load_default_errors() {
        // The executable may be started from the project root or Main_runtime.
        const vector<string> candidates = {
            "Terminal/Terminal-OUT/error_list.txt",
            "../Terminal/Terminal-OUT/error_list.txt"
        };
        for (const auto& path : candidates) {
            vector<string> messages = read_error_file(path);
            if (!messages.empty()) {
                return messages;
            }
        }
        return {};
    }
}

vector<string> TerminalOUT::errors = load_default_errors();

void TerminalOUT::terminal_standard_output() {
    cout << standard_output;
}

void TerminalOUT::terminal_custom_output(string content, string color) {
    cout << color << content << "\n" << ansi_color_chart::reset;
}

vector<string> TerminalOUT::load_error_message(const string config_file_name) {
    vector<string> messages = read_error_file(config_file_name);

    // Use known project-relative fallbacks when the supplied relative path
    // does not match the current working directory.
    if (messages.empty()) {
        const vector<string> candidates = {
            "Terminal/Terminal-OUT/error_list.txt",
            "../Terminal/Terminal-OUT/error_list.txt"
        };
        for (const auto& path : candidates) {
            messages = read_error_file(path);
            if (!messages.empty()) {
                break;
            }
        }
    }

    if (messages.empty()) {
        cerr << "Error: Could not load error definitions. Tried: "
             << config_file_name
             << ", Terminal/Terminal-OUT/error_list.txt, and "
             << "../Terminal/Terminal-OUT/error_list.txt.\n";
        return errors;
    }

    errors = messages;
    return errors;
}

string TerminalOUT::terminal_error_output(string error_reason) {
    for (const auto& error : errors) {
        const size_t delimiter = error.find(" -");
        const string key = (delimiter != string::npos)
            ? error.substr(0, delimiter)
            : error;

        if (key == error_reason) {
            return error;
        }
    }

    return ansi_color_chart::red + "Error not found: '" + error_reason +
           "'. Check Terminal/Terminal-OUT/error_list.txt." +
           ansi_color_chart::reset;
}
