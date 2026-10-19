#include <vector>
#include <string>
#include <iostream>

#include "../Arm-logic/Serial-Data-logic/Serial-comection/serial-conection.hpp"
#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"


#include "../Terminal/Login-Register-Presetloading/usr-manager/usr-manager.hpp"

#pragma comment(lib, "OneCore.lib")

TerminalOUT terminal_out;
TerminalIN terminal_in;

using namespace std;

int main() {
    UserManager system;
    TerminalIN terminal_in;

    system.startup_terminal("David");

    terminal_out.terminal_custom_output("Menu option:", ansi_color_chart::white);
    int num = terminal_in.terminal_read_line_int();
    (void)num; // Menu actions are not implemented yet; current flow continues to registration.

    terminal_out.terminal_custom_output("Username:", ansi_color_chart::white);
    string user_name = terminal_in.terminal_read_line();
    terminal_out.terminal_custom_output("Password:", ansi_color_chart::white);
    string user_pas = terminal_in.terminal_read_password();

    if (system.register_user(user_name, user_pas)) {
        terminal_out.terminal_custom_output("Registration saved successfully.", ansi_color_chart::green);
    }

    
}
