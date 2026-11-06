
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
#include "../Arm-logic/DialogiXMove_dekodierer/DialogiXMove_dekodierer.hpp"
#include "../Arm-logic/Serial-Data-logic/Data-send-back/Data-send-back.hpp"
#include "../Arm-logic/Serial-Data-logic/read-serial-con1-2/read-serial-con1-2.hpp"

#include <windows.h>

#pragma comment(lib, "OneCore.lib")

using namespace std;

TerminalOUT terminal_out;

DeCode de_code;

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
    // ==========================================
    // STEP 1: SEARCH FOR AVAILABLE COM PORTS
    // ==========================================

    vector<string> serial_ports = serial.search_for_serial_ports();

    if (serial_ports.empty())
    {
        terminal_out.terminal_custom_output(
            "No serial ports found.",
            ansi_color_chart::red
        );

        return 0;
    }

    terminal_out.terminal_custom_output(
        "Available serial ports:",
        ansi_color_chart::green
    );

    for (const string& port : serial_ports)
    {
        terminal_out.terminal_custom_output(
            port,
            ansi_color_chart::white
        );
    }


    // ==========================================
    // STEP 2: SELECT COM PORT
    // ==========================================

    terminal_out.terminal_custom_output(
        "COM:",
        ansi_color_chart::white
    );

    string com = terminal_in.terminal_read_line();

    // Remove board information, e.g. " | Arduino"
    size_t separator = com.find(" | ");

    if (separator != string::npos)
    {
        com = com.substr(0, separator);
    }

    // Remove accidental whitespace
    size_t first = com.find_first_not_of(" \t\r\n");

    if (first == string::npos)
    {
        terminal_out.terminal_custom_output(
            "Invalid COM port.",
            ansi_color_chart::red
        );

        return 0;
    }

    com = com.substr(first);

    size_t last = com.find_last_not_of(" \t\r\n");
    com.erase(last + 1);

    if (com.rfind("COM", 0) != 0)
    {
        terminal_out.terminal_custom_output(
            "Invalid COM port name. Example: COM3",
            ansi_color_chart::red
        );

        return 0;
    }


    // ==========================================
    // STEP 3: SELECT BAUDRATE
    // ==========================================

    terminal_out.terminal_custom_output(
        "Baud:",
        ansi_color_chart::white
    );

    int baud = terminal_in.terminal_read_line_int();

    if (baud <= 0)
    {
        terminal_out.terminal_custom_output(
            "Invalid baudrate.",
            ansi_color_chart::red
        );

        return 0;
    }


    // ==========================================
    // STEP 4: CONNECT TO SERIAL PORT
    // ==========================================

    terminal_out.terminal_custom_output(
        "Connecting to serial port...",
        ansi_color_chart::yellow
    );

    string status = serial.serial_conect_GUI(com, baud);

    logger.log_to(status);

    if (status != "Connection was successful!")
    {
        terminal_out.terminal_custom_output(
            "Serial connection failed: " + status,
            ansi_color_chart::red
        );

        return 0;
    }

    terminal_out.terminal_custom_output(
        "Serial connection established!",
        ansi_color_chart::green
    );


    // ==========================================
    // STEP 5: RECEIVE CODE BLOCK
    // ==========================================

    terminal_out.terminal_custom_output(
        "Waiting for code block (BEGINN ... END)...",
        ansi_color_chart::yellow
    );

    vector<string> code_block =
        data_prep.read_serial_GUI_code_block();


    // ==========================================
    // STEP 6: DISPLAY RECEIVED CODE BLOCK
    // ==========================================

    if (code_block.empty())
    {
        terminal_out.terminal_custom_output(
            "Received code block is empty!",
            ansi_color_chart::red
        );

        serial.disconnect_serial_GUI();

        return 0;
    }

    terminal_out.terminal_custom_output(
        "Code block received:",
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
        "Code block complete.",
        ansi_color_chart::green
    );


    // ==========================================
    // STEP 7: DECODE CODE BLOCK
    // ==========================================

    vector<DeCode::CommandResult> parsed;

    try
    {
        parsed = de_code.DeCode_code_blk(code_block);
    }
    catch (const exception& error)
    {
        logger.log_to(
            string("[ERROR] Decoder exception: ") + error.what()
        );

        terminal_out.terminal_custom_output(
            "Decoder error: " + string(error.what()),
            ansi_color_chart::red
        );

        serial.disconnect_serial_GUI();

        return 0;
    }

    terminal_out.terminal_custom_output(
        "Parsed commands: " + to_string(parsed.size()),
        ansi_color_chart::yellow
    );


    // ==========================================
    // STEP 8: PROCESS DECODED COMMANDS
    // ==========================================

    bool move_found = false;

    for (size_t i = 0; i < parsed.size(); i++)
    {
        if (holds_alternative<DeCode::MOVE>(parsed[i]))
        {
            const DeCode::MOVE& move =
                get<DeCode::MOVE>(parsed[i]);

            terminal_out.terminal_custom_output(
                "MOVE command #" + to_string(i + 1),
                ansi_color_chart::green
            );

            terminal_out.terminal_custom_output(
                "X: " + to_string(move.X),
                ansi_color_chart::blue
            );

            move_found = true;
        }
    }

    if (!move_found)
    {
        terminal_out.terminal_custom_output(
            "No MOVE commands found in parsed data!",
            ansi_color_chart::red
        );
    }


    // ==========================================
    // STEP 9: DISCONNECT SERIAL
    // ==========================================

    serial.disconnect_serial_GUI();

    terminal_out.terminal_custom_output(
        "Serial connection closed.",
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