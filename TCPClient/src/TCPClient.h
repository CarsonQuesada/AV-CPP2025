#pragma once

#include <iostream>
#include <shared_mutex>
#include <atomic>

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

class TCPClient
{
public:
    TCPClient();
    ~TCPClient();

    // For connection to server
    bool tryConnect(const char* ipAddr, int port, std::atomic<bool>& cancelFlag, int timeoutMs = 5000);
    void disconnect();

    int receiveAll(void* buffer, int length, int maxWait = 5);  // return code: 1 success -1 disconnect
    int transmitAll(const void* data, int length);

private:
    SOCKET sock;
    std::atomic<bool> connected{false};
    std::atomic<bool> reconnecting{false};
    std::shared_mutex sockMut;
    std::mutex transmitMut;
};