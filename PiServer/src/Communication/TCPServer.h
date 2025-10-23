#pragma once

#include <iostream>
#include <queue>
#include <shared_mutex>
#include <atomic>
#include <thread>

class TCPServer
{
public:
    TCPServer() {}
    ~TCPServer();

    bool waitForConnection(std::atomic<bool>& cancelConnectFlag, int port, const char* ipAddr = nullptr);
    void disconnect();

    bool receiveAll(void* buffer, int len, int maxWait = 5);  // returns error code: 1 success, 0 maxByteRead exceeded, -1 disconnect
    bool transmitAll(const void* data, int length);
private:
    int clientSock;
    std::atomic<bool> connected{false};
    std::atomic<bool> reconnecting{false};
    std::shared_mutex sockMut;

    // Helper function for connection to client
    int createListeningSock(int port, const char* ipAddr = nullptr);
};