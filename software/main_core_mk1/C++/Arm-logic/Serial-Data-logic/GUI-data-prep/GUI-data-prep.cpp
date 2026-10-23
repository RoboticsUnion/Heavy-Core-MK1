#include "GUI-data-prep.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../Serial-conection/serial-conection.hpp"

#include <iostream>
#include <windows.h>
#include <vector>

DataPrep data_prep;

std::string DataPrep::read_serial_GUI_per_line(){
    char buffer[256];
    DWORD bytesRead = 0;

    BOOL success = ReadFile(
        serial.m_hSerialGUI,
        buffer,
        sizeof(buffer),
        &bytesRead,
        nullptr
    );

    if (!success || bytesRead == 0) {
        return "";
    }

    current_line.append(buffer, bytesRead);

    std::size_t newline = current_line.find('\n');

    if (newline == std::string::npos) {
        return "";
    }

    std::string line = current_line.substr(0, newline);
    current_line.erase(0, newline + 1);

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    return line;
}