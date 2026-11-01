
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

#include <windows.h>

#pragma comment(lib, "OneCore.lib")

using namespace std;

TerminalOUT terminal_out;

bool run = true;

int main()
{
    UserManager system;
    TerminalIN terminal_in;

    system.startup_terminal("David");

    terminal_out.terminal_custom_output(
        "Menu option:",
        ansi_color_chart::white
    );

    int num = terminal_in.terminal_read_line_int();

    if (num == 1)
    {
        terminal_out.terminal_custom_output(
            "Username:",
            ansi_color_chart::white
        );
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output(
            "Password:",
            ansi_color_chart::white
        );
        string user_pas = terminal_in.terminal_read_password();

        if (system.register_user(user_name, user_pas))
        {
            terminal_out.terminal_custom_output(
                "Registration saved successfully.",
                ansi_color_chart::green
            );
        }
    }
    else if (num == 2)
    {
        terminal_out.terminal_custom_output(
            "Username:",
            ansi_color_chart::white
        );
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output(
            "Password:",
            ansi_color_chart::white
        );
        string password = terminal_in.terminal_read_password();

        if (system.login_user(user_name, password))
        {
            terminal_out.terminal_custom_output(
                "Login successful.",
                ansi_color_chart::green
            );
        }
    }
    else if (num == 3)
    {
        terminal_out.terminal_custom_output(
            "Username:",
            ansi_color_chart::white
        );
        string user_name = terminal_in.terminal_read_line();

        terminal_out.terminal_custom_output(
            "Password:",
            ansi_color_chart::white
        );
        string password = terminal_in.terminal_read_password();

        if (system.delete_user(user_name, password))
        {
            terminal_out.terminal_custom_output(
                "User deleted successfully.",
                ansi_color_chart::green
            );
        }
    }
    else if (num == 4)
    {
        // Verfügbare COM-Ports anzeigen
        vector<string> serial_ports = serial.search_for_serial_ports();

        if (serial_ports.empty())
        {
            terminal_out.terminal_custom_output(
                "No serial ports found.",
                ansi_color_chart::red
            );
            return 0;
        }

        for (const string& port : serial_ports)
        {
            terminal_out.terminal_custom_output(
                port,
                ansi_color_chart::white
            );
        }

        // COM-Port auswählen
        terminal_out.terminal_custom_output(
            "COM:",
            ansi_color_chart::white
        );
        string com = terminal_in.terminal_read_line();

        // Baudrate auswählen
        terminal_out.terminal_custom_output(
            "Baud:",
            ansi_color_chart::white
        );
        int baud = terminal_in.terminal_read_line_int();

        // Verbindung herstellen
        terminal_out.terminal_custom_output(
            "[DEBUG] Connecting to serial port...",
            ansi_color_chart::yellow
        );

        string status = serial.serial_conect_GUI(com, baud);
        logger.log_to(status);

        terminal_out.terminal_custom_output(
            "[DEBUG] Connection function returned.",
            ansi_color_chart::yellow
        );

        // Empfangsschleife
        terminal_out.terminal_custom_output(
            "[DEBUG] Waiting for serial data...",
            ansi_color_chart::yellow
        );

        while (true)
        {
            string data = data_prep.read_serial_GUI_per_line();

            if (!data.empty())
            {
                terminal_out.terminal_custom_output(
                    "[GUI DATA] " + data,
                    ansi_color_chart::white
                );
            }

            // CPU nicht unnötig belasten
            Sleep(1);
        }
    }
    else if (num == 5)
    {
        // Verfügbare COM-Ports anzeigen
        vector<string> serial_ports = serial.search_for_serial_ports();

        if (serial_ports.empty())
        {
            terminal_out.terminal_custom_output(
                "No serial ports found.",
                ansi_color_chart::red
            );
            return 0;
        }

        for (const string& port : serial_ports)
        {
            terminal_out.terminal_custom_output(
                port,
                ansi_color_chart::white
            );
        }

        // COM-Port auswählen
        terminal_out.terminal_custom_output(
            "COM:",
            ansi_color_chart::white
        );
        string com = terminal_in.terminal_read_line();

        // Baudrate auswählen
        terminal_out.terminal_custom_output(
            "Baud:",
            ansi_color_chart::white
        );
        int baud = terminal_in.terminal_read_line_int();

        // Verbindung herstellen
        terminal_out.terminal_custom_output(
            "[DEBUG] Connecting to serial port...",
            ansi_color_chart::yellow
        );

        string status = serial.serial_conect_GUI(com, baud);
        logger.log_to(status);

        terminal_out.terminal_custom_output(
            status,
            ansi_color_chart::white
        );

        // Codeblock empfangen
        terminal_out.terminal_custom_output(
            "[DEBUG] Waiting for code block (BEGIN)...",
            ansi_color_chart::yellow
        );

        vector<string> code_block = data_prep.read_serial_GUI_code_block();

        // Empfangenen Codeblock ausgeben
        terminal_out.terminal_custom_output(
            "[DEBUG] Code block received:",
            ansi_color_chart::green
        );

        for (const string& line : code_block)
        {
            terminal_out.terminal_custom_output(
                line,
                ansi_color_chart::white
            );
        }

        terminal_out.terminal_custom_output(
            "[DEBUG] Code block complete.",
            ansi_color_chart::green
        );
    }
    
    else
    {
        terminal_out.terminal_custom_output(
            "Invalid menu option.",
            ansi_color_chart::red
        );
    }

    return 0;
}