
#include <vector>
#include <string>
#include <iostream>

#include "../Arm-logic/Serial-Data-logic/Serial-conection/serial-conection.hpp"
#include "../Arm-logic/Serial-Data-logic/GUI-data-prep/GUI-data-prep.hpp"
#include "../ansi_color_chart/ansi_color_chart.hpp"
#include "../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Terminal/Terminal-IN/Terminal-IN.hpp"
#include "../Terminal/Login-Register-Presetloading/usr-manager/usr-manager.hpp"
#include "../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#pragma comment(lib, "OneCore.lib")

TerminalOUT terminal_out;

using namespace std;

int main() {
    UserManager system;
    TerminalIN terminal_in;

    system.startup_terminal("David");

    terminal_out.terminal_custom_output("Menu option:", ansi_color_chart::white);
    int num = terminal_in.terminal_read_line_int();

    if (num == 1) {
        // Registrierung
        terminal_out.terminal_custom_output("Username:", ansi_color_chart::white);
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output("Password:", ansi_color_chart::white);
        string user_pas = terminal_in.terminal_read_password();

        if (system.register_user(user_name, user_pas)) {
            terminal_out.terminal_custom_output(
                "Registration saved successfully.",
                ansi_color_chart::green
            );
        }
    }
    else if (num == 2) {
        // Login
        terminal_out.terminal_custom_output("Username:", ansi_color_chart::white);
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output("Password:", ansi_color_chart::white);
        string password = terminal_in.terminal_read_password();

        if (system.login_user(user_name, password)) {
            terminal_out.terminal_custom_output(
                "Login successful.",
                ansi_color_chart::green
            );
        }
    }
    else if (num == 3) {
        // Benutzer löschen
        terminal_out.terminal_custom_output("Username:", ansi_color_chart::white);
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output("Password:", ansi_color_chart::white);
        string password = terminal_in.terminal_read_password();

        if (system.delete_user(user_name, password)) {
            terminal_out.terminal_custom_output(
                "User deleted successfully.",
                ansi_color_chart::green
            );
        }
    }
    else if(num == 4){
        vector<string> serial_ports = serial.search_for_serial_ports();
        short num_ports = serial_ports.size();
        for (int i = 0; i < num_ports; i++) {
            terminal_out.terminal_custom_output(serial_ports[i], ansi_color_chart::white);
        }
        terminal_out.terminal_custom_output("COM:", ansi_color_chart::white);
        string com = terminal_in.terminal_read_line();
        terminal_out.terminal_custom_output("Baud", ansi_color_chart::white);
        int baud = terminal_in.terminal_read_line_int();
        string status = serial.serial_conect_GUI(com, baud);
        logger.log_to(status);
        string data;
        do{
            data = data_prep.read_serial_GUI_per_line();
        } while(data.empty());

        terminal_out.terminal_custom_output(data, ansi_color_chart::white);

    }
    else {
        terminal_out.terminal_custom_output(
            "Invalid menu option.",
            ansi_color_chart::red
        );
    }

    return 0;
}
