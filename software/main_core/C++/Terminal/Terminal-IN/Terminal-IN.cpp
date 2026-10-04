#define NOMINMAX // needed for conflict of windows.h and max()

#include "../Terminal-OUT/Terminal-OUT.hpp"

#include "../../ansi_color_chart/ansi_color_chart.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include "Terminal-IN.hpp"
#include <windows.h>

#include <limits>

using namespace std;
string user_input;
int number_convert;

string TerminalIN::terminal_read_line() {
    cin >> user_input;
    return user_input;
}

int TerminalIN::terminal_read_line_int() {
    TerminalOUT terminal;
    cin >> user_input;
    try { // try the input if it is not an int it searches for an error code returns ist and retrys
        number_convert = std::stoi(user_input);
        return number_convert;

    }
    catch (const invalid_argument& e) {
        terminal.load_error_message("Terminal/Terminal-OUT/error_list.txt"); //loads the error messages from the file "error_list.txt" and returns them as a vector of strings
        terminal.terminal_custom_output(terminal.terminal_error_output("error_only_int"), ansi_color_chart::yellow); //searches for the error message corresponding to the error reason passed to the function and returns it as a string
        terminal.terminal_custom_output("\n", ansi_color_chart::black);
        terminal.terminal_standard_output(); //make a -> for the next input
        return TerminalIN::terminal_read_line_int(); //recursively calls the function again to get a valid integer input from the user
    }
    catch (const out_of_range& e) {
        terminal.load_error_message("Terminal/Terminal-OUT/error_list.txt"); //loads the error messages from the file "error_list.txt" and returns them as a vector of strings
        terminal.terminal_custom_output(terminal.terminal_error_output("out_of_range"), ansi_color_chart::yellow); //searches for the error message corresponding to the error reason passed to the function and returns it as a string
        terminal.terminal_custom_output("\n", ansi_color_chart::black); 
        terminal.terminal_standard_output();
        return TerminalIN::terminal_read_line_int();
    }
        
}

string TerminalIN::terminal_read_password() {

    // deactivates the input echo for cin it gets read with getline() -> clear buffer
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // verry important deletes input buffer rest

    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT)); 

    string s;
    getline(cin, s);   

    SetConsoleMode(hStdin, mode);

    cout << endl;

    return s;

    
}
