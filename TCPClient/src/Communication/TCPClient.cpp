#include "TCPClient.h"

#include <cassert>
#include <thread>
#include <mutex>
#include <cassert>

TCPClient::TCPClient()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // Handle error
    }
}

TCPClient::~TCPClient()
{
    disconnect();
    WSACleanup();
}

bool TCPClient::tryConnect(const char* ipAddr, int port, std::atomic<bool>& cancelFlag, int timeoutMs)
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    // if (WSAStartup(version, &data) != 0) {
    //     std::cerr << "Can't Start WinSock\n";
    //     return false;
    // }

    std::unique_lock<std::shared_mutex> lock(sockMut);
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return false;
    }

    // Set to non-blocking
    u_long nonBlocking = 1;
    ioctlsocket(sock, FIONBIO, &nonBlocking);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddr, &server.sin_addr) <= 0) {
        std::cerr << "Invalid IP address\n";
        closesocket(sock);
        return false;
    }

    int status = connect(sock, (sockaddr*)&server, sizeof(server));
    if (status == 0) {
        // Connected immediately
        return true;
    }

    if (WSAGetLastError() != WSAEWOULDBLOCK) {
        std::cerr << "Immediate connect() failed\n";
        closesocket(sock);
        return false;
    }

    // Use select() to wait for socket to be writable (indicates success)
    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);

    timeval timeout;
    timeout.tv_sec = timeoutMs / 1000;
    timeout.tv_usec = (timeoutMs % 1000) * 1000;

    const int interval = 100; // check every 100ms
    int waited = 0;

    while (waited < timeoutMs && !cancelFlag.load()) {
        timeval checkTime = { 0, interval * 1000 };

        fd_set checkWriteSet = writeSet;
        int sel = select(0, nullptr, &checkWriteSet, nullptr, &checkTime);
        if (sel > 0 && FD_ISSET(sock, &checkWriteSet)) {
            // Check for socket errors
            int optVal;
            socklen_t optLen = sizeof(optVal);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&optVal, &optLen);
            if (optVal == 0) {
                // Connected successfully
                connected.store(true);
                nonBlocking = 0;
                ioctlsocket(sock, FIONBIO, &nonBlocking); // restore blocking
                return true;
            } else {
                std::cerr << "Connection failed: socket error\n";
                break;
            }
        }

        waited += interval;
    }

    std::cerr << "Connection attempt timed out or cancelled\n";
    closesocket(sock);
    return false;
}

void TCPClient::disconnect()
{
    std::unique_lock<std::shared_mutex> lock(sockMut);
    if (connected.load()) {
        shutdown(sock, SD_BOTH);
        closesocket(sock);
        connected.store(false);
    }
}

int TCPClient::receiveAll(void* buffer, int length, int maxWait)
{
    if (!connected)
        return false; // signal no connection to server

    int bytesRead = 0;
    fd_set readfds;
    timeval timeout;
    int activity;

    std::shared_lock<std::shared_mutex> lock(sockMut); // shared with transmit()

    if (connected.load()) {
        while (bytesRead < length) {
            FD_ZERO(&readfds);              // Clear the readfds set
            FD_SET(sock, &readfds);         // Add the client socket to the read set
            timeout.tv_sec = maxWait;       // Timeout after maxWait seconds
            timeout.tv_usec = 0;

            // Use select() to check if the socket is ready to be read
            activity = select(0, &readfds, nullptr, nullptr, &timeout);

            if (activity == SOCKET_ERROR) {
                std::cout << "Error in select(): " << WSAGetLastError() << std::endl;
                return false;
            } else if (activity == 0) {
                // Timeout reached, no data received
                std::cout << "Timeout reached while waiting for data" << std::endl;
                return false;
            } else if (FD_ISSET(sock, &readfds)) {
                // Begin receiving the message
                int bytesRecovered = recv(sock, (char*)buffer + bytesRead, length - bytesRead, 0);

                if (bytesRecovered > 0) {
                    bytesRead += bytesRecovered;
                } else if (bytesRecovered == 0) {
                    std::cout << "Connection closed gracefully by user" << std::endl;
                    return false; // Connection closed by user gracefully
                } else if (bytesRecovered < 0) {
                    int err = WSAGetLastError();
                    if (err == WSAEWOULDBLOCK) {
                        std::cout << "Received no data\n" << std::endl;
                    } else {
                        std::cout << "TCP disconnected incorrectly\n" << std::endl;
                        return -1; // TCP disconnected incorrectly
                    }
                }
            }
        }
    } else {
        return false; // Not connected
    }

    return true;
}

int TCPClient::transmitAll(const void *data, int length)
{
    if (!connected)
        return -2; // signal no connection to server

    int totalSent = 0;
    const int timeoutSeconds = 1;

    std::shared_lock<std::shared_mutex> lock(sockMut); // shared with receive()
    if (connected.load()) {
        while (totalSent < length) {
            // Wait for the socket to be writable
            fd_set writefds;
            FD_ZERO(&writefds);
            FD_SET(sock, &writefds);

            struct timeval timeout;
            timeout.tv_sec = timeoutSeconds;
            timeout.tv_usec = 0;

            int ready = select(0, nullptr, &writefds, nullptr, &timeout);
            if (ready < 0) {
                std::cerr << "select() error: " << WSAGetLastError() << std::endl;
                return false;
            } else if (ready == 0) {
                std::cerr << "sendAll() timeout while waiting to send.\n";
                return false;
            }

            // Write to socket
            int bytesSent = send(sock, (const char*)data + totalSent, length - totalSent, 0);
            if (bytesSent < 0) {
                int err = WSAGetLastError();
                if (err == WSAEWOULDBLOCK) {
                    continue; // Try again
                } else {
                    std::cerr << "send() error: " << err << "\n";
                    return false;
                }
            } else if (bytesSent == 0) {
                std::cerr << "Connection closed by peer.\n";
                return false;
            }

            totalSent += bytesSent;
        }
    }

    return true;
}
