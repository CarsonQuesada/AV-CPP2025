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
    bool tryConnect();  // tries to connect to local and remote addresses
    bool tryConnect(const char *ipAddr, int port);
    void disconnect();
    void handleReconnect();

    int receiveAll(void* buffer, int maxByteRead);  // returns error code: 1 success, 0 maxByteRead exceeded, -1 disconnect
    bool transmitAll(const void* data, int length);

private:
    SOCKET sock;
    std::atomic<bool> connected{false};
    std::atomic<bool> reconnecting{false};
    std::shared_mutex sockMut;

    // For recieving from server
    bool receive(void* buffer, int len, int maxWait = 5);

    // For sending to server
    bool transmit(const char* data, int length);
};