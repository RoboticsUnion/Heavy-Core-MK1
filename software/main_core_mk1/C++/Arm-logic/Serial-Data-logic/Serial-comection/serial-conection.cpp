#include "serial-conection.hpp" 
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
# include <vector>

TerminalOUT terminal_out;
TerminalIN terminal_in;

using namespace std;


string Serial::serial_conect_GUI(string PORT_GUI, int baudrate_GUI) {

    terminal_out.terminal_custom_output("Trying to connect to: " + PORT_GUI + " with BAUD: " + to_string(baudrate_GUI), ansi_color_chart::yellow);

    
    // fuses the Port_gui with "\\\\.\\"
    string portName = "\\\\.\\" + PORT_GUI;

    // creates a handle for the PORT rules/conduct
    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );
    // if the handle value is invalid the system will report it
    if (hSerial == INVALID_HANDLE_VALUE) {
        
        string error = terminal_out.terminal_error_output("error_opening_port_GUI");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_opening_port_GUI";
    }
    // start a dcb for configuring baudrates
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    // error handeling for dcb
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_reading_setting_GUI");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_reading_setting_GUI";
    }
    // dcb configuring
    dcbSerialParams.BaudRate = baudrate_GUI;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    // error set atributes
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_set_conection_atributs");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_set_conection_atributs_GUI";
    }
    // timeout configuration
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    // stores handle for later use
    this->m_hSerialGUI = hSerial; // Store the handle for later use

    terminal_out.terminal_custom_output("Connection was successful!", ansi_color_chart::green);

    return "Connection was successful!";
}

void Serial::disconnect_serial_GUI() {
    // closing conection
    if (m_hSerialGUI != INVALID_HANDLE_VALUE) {
        CloseHandle(this->m_hSerialGUI);
        this->m_hSerialGUI = INVALID_HANDLE_VALUE;
        terminal_out.terminal_custom_output("Gui Port disconected", ansi_color_chart::green);

    }
}

string Serial::serial_conect_CON1(string PORT_CON1, int baudrate_CON1) {

    terminal_out.terminal_custom_output("Trying to connect to: " + PORT_CON1 + " with BAUD: " + to_string(baudrate_CON1), ansi_color_chart::yellow);
    
    // fuses the Port_gui with "\\\\.\\"
    string portName = "\\\\.\\" + PORT_CON1;

    // creates a handle for the PORT rules/conduct
    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );
    // if the handle value is invalid the system will report it
    if (hSerial == INVALID_HANDLE_VALUE) {
        
        string error = terminal_out.terminal_error_output("error_opening_port_CON1");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_opening_port_CON1";
    }
    // start a dcb for configuring baudrates
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    // error handeling for dcb
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_reading_setting_CON1");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_reading_setting_CON1";
    }
    // dcb configuring
    dcbSerialParams.BaudRate = baudrate_CON1;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    // error set atributes
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_set_conection_atributs");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_set_conection_atributs_CON1";
    }
    // timeout configuration
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    // stores handle for later use
    this->m_hSerialCON1 = hSerial; // Store the handle for later use

    terminal_out.terminal_custom_output("Connection was successful!", ansi_color_chart::green);

    return "Connection was successful!";
}

void Serial::disconnect_serial_CON1() {
    // closing conection
    if (m_hSerialCON1 != INVALID_HANDLE_VALUE) {
        CloseHandle(this->m_hSerialCON1);
        this->m_hSerialCON1 = INVALID_HANDLE_VALUE;
        terminal_out.terminal_custom_output("CON1 Port disconected", ansi_color_chart::green);

    }
}

string Serial::serial_conect_CON2(string PORT_CON2, int baudrate_CON2) {

    terminal_out.terminal_custom_output("Trying to connect to: " + PORT_CON2 + " with BAUD: " + to_string(baudrate_CON2), ansi_color_chart::yellow);
    
    // fuses the Port_con2 with "\\\\.\\"
    string portName = "\\\\.\\" + PORT_CON2;

    // creates a handle for the PORT rules/conduct
    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );
    // if the handle value is invalid the system will report it
    if (hSerial == INVALID_HANDLE_VALUE) {
        
        string error = terminal_out.terminal_error_output("error_opening_port_CON2");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_opening_port_CON2";
    }
    // start a dcb for configuring baudrates
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    // error handeling for dcb
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_reading_setting_CON2");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_reading_setting_CON2";
    }
    // dcb configuring
    dcbSerialParams.BaudRate = baudrate_CON2;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    // error set atributes
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        
        string error = terminal_out.terminal_error_output("error_set_conection_atributs");
        terminal_out.terminal_custom_output(error, ansi_color_chart::yellow);
        return "error_set_conection_atributs_CON2";
    }
    // timeout configuration
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    // stores handle for later use
    this->m_hSerialCON2 = hSerial; // Store the handle for later use

    terminal_out.terminal_custom_output("Connection was successful!", ansi_color_chart::green);

    return "Connection was successful!";
}

void Serial::disconnect_serial_CON2() {
    // closing conection
    if (m_hSerialCON2 != INVALID_HANDLE_VALUE) {
        CloseHandle(this->m_hSerialCON2);
        this->m_hSerialCON2 = INVALID_HANDLE_VALUE;
        terminal_out.terminal_custom_output("CON2 Port disconected", ansi_color_chart::green);

    }
}

string Serial::check_serial_available(string PORT_GUI, int baudrate_GUI, string PORT_CON1, int baudrate_CON1, string PORT_CON2, int baudrate_CON2) {
    terminal_out.terminal_custom_output("Checking conection status to Serial GUI, CON1 and CON2", ansi_color_chart::bright_blue);
    DWORD errors;
    COMSTAT status;

    vector<string> return_handle = {"", "", ""};

    if(!ClearCommError(this->m_hSerialGUI, &errors, &status)) {
        CloseHandle(this->m_hSerialGUI);
        this->m_hSerialGUI = INVALID_HANDLE_VALUE;
        return_handle[0] = "GUI-NOT-CONECTED";
        terminal_out.terminal_error_output("warning_GUI_ser_disc");  
    }

    if(!ClearCommError(this->m_hSerialCON1, &errors, &status)) {
        CloseHandle(this->m_hSerialCON1);
        this->m_hSerialCON1 = INVALID_HANDLE_VALUE;
        return_handle[1] = "CON1-NOT-CONECTED";
        terminal_out.terminal_error_output("warning_CON1_ser_disc");  
    }

    if(!ClearCommError(this->m_hSerialCON2, &errors, &status)) {
        CloseHandle(this->m_hSerialCON2);
        this->m_hSerialCON2 = INVALID_HANDLE_VALUE;
        return_handle[2] = "CON2-NOT-CONECTED";
        terminal_out.terminal_error_output("warning_CON2_ser_disc");  
    }

    if(return_handle == std::vector<std::string>{"", "", ""}) {
        terminal_out.terminal_custom_output("All Serial Ports are connected", ansi_color_chart::green);
        return "return_handle";
    }

    if(return_handle != std::vector<std::string>{"", "", ""}) {
        terminal_out.terminal_custom_output("Some serial Ports are disconnected", ansi_color_chart::red);
        return "return_handle";
    }
    
}