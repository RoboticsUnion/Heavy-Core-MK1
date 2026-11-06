#include "Data-send-back.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../Serial-conection/serial-conection.hpp"

#include "../../../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#include "../../../Terminal/Login-Register-Presetloading/preset-manager/preset-manager.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

Serial serial;

TerminalOUT terminal_out;

bool data_send_back::send_data_back_GUI(string contents){
    if(serial.m_hSerialGUI == INVALID_HANDLE_VALUE){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("INVALID_GUI_HANDLE"), ansi_color_chart::red);
    }

    DWORD bytesWritten = 0;

    bool success = WriteFile(
        serial.m_hSerialGUI,
        contents.c_str(),
        contents.length(),
        &bytesWritten,
        NULL
    );

    if(!success){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!WRITING_GUI"), ansi_color_chart::red);
        return false;
    }

    return true;
    
}

bool data_send_back::send_data_back_CON1(string contents){

    if(serial.m_hSerialCON1 == INVALID_HANDLE_VALUE){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("INVALID_CON1_HANDLE"), ansi_color_chart::red);
    }

    DWORD bytesWritten = 0;

    bool success = WriteFile(
        serial.m_hSerialCON1,
        contents.c_str(),
        contents.length(),
        &bytesWritten,
        NULL
    );

    if(!success){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!WRITING_CON1"), ansi_color_chart::red);
        return false;
    }

    return true;
    

}

bool data_send_back::send_data_back_CON2(string contents){
    
    if(serial.m_hSerialCON2 == INVALID_HANDLE_VALUE){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("INVALID_CON2_HANDLE"), ansi_color_chart::red);
    }

    DWORD bytesWritten = 0;

    bool success = WriteFile(
        serial.m_hSerialCON2,
        contents.c_str(),
        contents.length(),
        &bytesWritten,
        NULL
    );

    if(!success){
        terminal_out.terminal_custom_output(terminal_out.terminal_error_output("!WRITING_CON2"), ansi_color_chart::red);
        return false;
    }

    return true;
    

}