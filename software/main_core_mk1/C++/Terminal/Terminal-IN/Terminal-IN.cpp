#define NOMINMAX

#include "../Terminal-OUT/Terminal-OUT.hpp"
#include "../../ansi_color_chart/ansi_color_chart.hpp"
#include "Terminal-IN.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>

using namespace std;

string TerminalIN::terminal_read_line() {
    string user_input;
    getline(cin, user_input);
    return user_input;
}

int TerminalIN::terminal_read_line_int() {
    TerminalOUT terminal;
    string input;

    while (true) {
        if (!getline(cin, input)) {
            return 0;
        }

        try {
            size_t parsed_chars = 0;
            const int value = stoi(input, &parsed_chars);
            const size_t extra_chars = input.find_first_not_of(" \t\r\n", parsed_chars);

            if (extra_chars == string::npos) {
                return value;
            }

            terminal.terminal_custom_output(
                terminal.terminal_error_output("error_only_int"),
                ansi_color_chart::yellow
            );
        }
        catch (const invalid_argument&) {
            terminal.terminal_custom_output(
                terminal.terminal_error_output("error_only_int"),
                ansi_color_chart::yellow
            );
        }
        catch (const out_of_range&) {
            terminal.terminal_custom_output(
                terminal.terminal_error_output("out_of_range"),
                ansi_color_chart::yellow
            );
        }

        terminal.terminal_standard_output();
    }
}

string TerminalIN::terminal_read_password() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    const bool have_console_mode = GetConsoleMode(hStdin, &mode) != 0;

    if (have_console_mode) {
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    }

    string password;
    getline(cin, password);

    if (have_console_mode) {
        SetConsoleMode(hStdin, mode);
    }

    cout << endl;
    return password;
}
