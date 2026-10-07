#include "serial-conection.hpp" 
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include <iostream>
#include <windows.h>

TerminalOUT terminal_out;
TerminalIN terminal_in;

using namespace std;

string Serial::serial_conect_GUI(string PORT_GUI, int baudrate_GUI) {

    terminal_out.terminal_custom_output("Trying to connect to: " + PORT_GUI + " with BAUD: " + to_string(baudrate_GUI), ansi_color_chart::yellow);

    string portName = "\\\\.\\" + PORT_GUI;

    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        terminal_out.load_error_message("../../Terminal/Terminal-OUT/error_list.txt");
        string error = terminal_out.terminal_error_output("error_opening_port_GUI");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_opening_port_GUI";
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        terminal_out.load_error_message("../../Terminal/Terminal-OUT/error_list.txt");
        string error = terminal_out.terminal_error_output("error_reading_setting_GUI");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_reading_setting_GUI";
    }

    dcbSerialParams.BaudRate = baudrate_GUI;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        terminal_out.load_error_message("../../Terminal/Terminal-OUT/error_list.txt");
        string error = terminal_out.terminal_error_output("error_set_conection_atributs");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_set_conection_atributs_GUI";
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    this->m_hSerialGUI = hSerial; // Store the handle for later use

    terminal_out.terminal_custom_output("Connection was successful!", ansi_color_chart::green);

    return "Connection was successful!";
    

}

void Serial::disconnect_serial_GUI() {
    if (m_hSerialGUI != INVALID_HANDLE_VALUE) {
        CloseHandle(this->m_hSerialGUI);
        this->m_hSerialGUI = INVALID_HANDLE_VALUE;
        terminal_out.terminal_custom_output("Gui Port disconected", ansi_color_chart::green);

    }
}


string Serial::serial_conect_CON1(string PORT_CON1, int baudrate_CON1) {
    
}



string Serial::serial_conect_CON2(string PORT_CON2, int baudrate_CON2) {
    
}