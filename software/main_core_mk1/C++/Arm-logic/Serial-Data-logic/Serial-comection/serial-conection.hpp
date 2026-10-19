#pragma once
#include <string>
#include <vector>
#include <windows.h> // windows API

class Serial {
    public:
        std::string serial_conect_GUI(std::string PORT_GUI, int baudrate_GUI); // connects to the serial GUI port with the specified baudrate and returns a string indicating the status of the connection
        void disconnect_serial_GUI(); // disconnects from the serial GUI port
        std::string serial_conect_CON1(std::string PORT_CON1, int baudrate_CON1); // connects to the serial CON1 port with the specified baudrate and returns a string indicating the status of the connection
        void disconnect_serial_CON1(); // disconnects from the serial CON1 port
        std::string serial_conect_CON2(std::string PORT_CON2, int baudrate_CON2); // connects to the serial CON2 port with the specified baudrate and returns a string indicating the status of the connection
        void disconnect_serial_CON2(); // disconnects from the serial CON2 port
        
        std::vector<std::string> check_serial_available(std::string PORT_GUI, int baudrate_GUI, std::string PORT_CON1, int baudrate_CON1, std::string PORT_CON2, int baudrate_CON2); // checks the availability of the serial GUI, CON1, and CON2 ports and returns a vector of strings indicating the status of each port

        std::vector<std::string> search_for_serial_ports(); // searches for available serial ports on the system and returns a vector of strings containing the names of the available ports
        
    private:
    
        static constexpr int standard_baudrate_GUI = 9600; //default baudrate for serial connection
        static constexpr int standard_baudrate_CON1 = 9600; //default baudrate for serial connection
        static constexpr int standard_baudrate_CON2 = 9600;//default baudrate for serial connection

        const std::string standard_PORT_GUI = "COM6"; //default port for serial connection
        const std::string standard_PORT_CON1 = "COM3"; //default port for serial connection
        const std::string standard_PORT_CON2 = "COM4"; //default port for serial connection

        HANDLE m_hSerialGUI = INVALID_HANDLE_VALUE; // Handle for the serial port connection
        HANDLE m_hSerialCON1 = INVALID_HANDLE_VALUE; // Handle for the serial port connection
        HANDLE m_hSerialCON2 = INVALID_HANDLE_VALUE; // Handle for the serial port connection

        std::vector<std::string> return_handle = {"", "", ""}; // Vector to store the status of the serial connections (GUI, CON1, CON2)

        std::vector<std::string> availablePorts; // Vector to store the names of available serial ports on the system

};

extern Serial serial;