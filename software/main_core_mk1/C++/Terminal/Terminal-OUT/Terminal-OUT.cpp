#include "Terminal-OUT.hpp"

#include "../../ansi_color_chart/ansi_color_chart.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

void TerminalOUT::terminal_standard_output() {
    cout << standard_output; // gives you the standard output for the terminal, which is "--> "
}

void TerminalOUT::terminal_custom_output(string content, string color) {
    cout << color + content + ansi_color_chart::reset; // gives you the custom output for the terminal, which is the content passed to the function with the color passed to the function
}

vector<string> TerminalOUT::load_error_message(const string config_file_name) { // loads the error messages from the file "error_list.txt" and returns them as a vector of strings
    string str;
    ifstream in(config_file_name);
    vector<string> newVector;
    while (getline(in, str)) {
        if (!str.empty()) newVector.push_back(str);
    }
    return newVector;

}

string TerminalOUT::terminal_error_output(string error_reason) { // gives you the error output for the terminal, which is the error message corresponding to the error reason passed to the function
    int error_index = 0;

    for (const auto& error : errors) {
        size_t first_space = error.find(' '); // finds the first space in the error message, which is used to separate the error reason from the error description
        string first_word = (first_space != string::npos) ? error.substr(0, first_space) : error;
        if (first_word == error_reason) {
            return error; // returns the error message corresponding to the error reason passed to the function
        }
    }

    return ansi_color_chart::red + "Error not found" + ansi_color_chart::reset; // returns an error message if the error reason passed to the function is not found in the error messages loaded from the file "error_list.txt"
}

