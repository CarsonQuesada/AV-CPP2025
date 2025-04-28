#pragma once

#include <iostream>
#include <queue>
#include <shared_mutex>
#include <atomic>
#include <thread>

#include "../VehicleSys.h"

class TCPServer
{
public:
    bool waitForConnection();
    void disconnect();
    void handleReconnect();

    int receiveAll(void* buffer, int maxByteRead);  // returns error code: 1 success, 0 maxByteRead exceeded, -1 disconnect
    bool transmitAll(const void* data, int length);

    TCPServer() {}
    ~TCPServer();
private:
    int clientSock;
    std::atomic<bool> connected{false};
    std::atomic<bool> reconnecting{false};
    std::shared_mutex sockMut;

    // Helper function for connection to client
    int createListeningSock(const char* ipAddr);

    // Helper function for recieving from client
    bool receive(void* buffer, int len, int maxWait = 5);

    // Helper function for sending to client
    bool transmit(const char* data, int length);
};