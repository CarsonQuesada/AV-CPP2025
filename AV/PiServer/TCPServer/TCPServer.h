#pragma once

#include <iostream>

#include "UserInputBuff.h"

class TCPServer
{
public:
    int get_user_configurations();
    bool setup_TCP_server();
    bool retrieve_client_control(UserInput& userInput);
    void closeSocket();
    ~TCPServer();
    //int retrieve_serial_control(UserInputBuff& serialBuff); // Should remove this
private:
    bool connected;
    std::string ipAddress;
    int tcpPort;
    int clientSocket;
    UserInputBuff socketBuff;
};