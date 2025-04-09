#pragma once
#include <iostream>

#include <pigpiod_if2.h>

#include "Pigpio.h"
#include "TCPServer/TCPServer.h"

////////////////////////////////////////////////////////
// WARNING: this class may not work because of buffer //
////////////////////////////////////////////////////////

constexpr const char* serialPortPath = "/dev/ttyS0";

// Singleton class for SerialPort
class SerialPort
{
public:
    static SerialPort& get_instance();
    int retrieve_serial_data(UserInputBuff& serialBuff);
    bool initialize();
    void cleanup();
private:
    bool initialized = false;
    int piHandle;
    int serialHandle;

    SerialPort() {}                              // Private constructor to make sure there is only one instance
    SerialPort(const SerialPort&) = delete;             // Prevent copy construction
    SerialPort& operator=(const SerialPort&) = delete;  // Prevent assignment
    ~SerialPort();
};