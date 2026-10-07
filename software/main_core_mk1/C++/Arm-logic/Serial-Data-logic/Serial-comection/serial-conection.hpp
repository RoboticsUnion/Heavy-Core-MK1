#pragma once
#include <string>
#include <vector>
#include <windows.h>

class Serial {
    public:
        std::string serial_conect_GUI(std::string PORT_GUI, int baudrate_GUI); // connects to the serial GUI port with the specified baudrate and returns a string indicating the status of the connection
        void disconnect_serial_GUI(); // disconnects from the serial GUI port
        std::string serial_conect_CON1(std::string PORT_CON1, int baudrate_CON1);
        void disconnect_serial_CON1();
        std::string serial_conect_CON2(std::string PORT_CON2, int baudrate_CON2);
        void disconnect_serial_CON2();
        
        std::string check_serial_available(std::string PORT_GUI, int baudrate_GUI, std::string PORT_CON1, int baudrate_CON1, std::string PORT_CON2, int baudrate_CON2);
        
    private:
    
        static constexpr int standard_baudrate_GUI = 9600; //default baudrate for serial connection
        static constexpr int standard_baudrate_CON1 = 9600; 
        static constexpr int standard_baudrate_CON2 = 9600;

        const std::string standard_PORT_GUI = "COM6";
        const std::string standard_PORT_CON1 = "COM3";
        const std::string standard_PORT_CON2 = "COM4";

        HANDLE m_hSerialGUI = INVALID_HANDLE_VALUE; // Handle for the serial port connection
        HANDLE m_hSerialCON1 = INVALID_HANDLE_VALUE; // Handle for the serial port connection
        HANDLE m_hSerialCON2 = INVALID_HANDLE_VALUE; // Handle for the serial port connection

};