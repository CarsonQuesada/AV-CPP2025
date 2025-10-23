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
    // Copy current socket without blocking the reader for long
    SOCKET s_copy = INVALID_SOCKET;
    {
        std::shared_lock<std::shared_mutex> rlk(sockMut);
        s_copy = sock;
    }

    // Interrupt any pending I/O immediately
    if (s_copy != INVALID_SOCKET) {
        shutdown(s_copy, SD_BOTH);
    }

    // Now take the exclusive lock and close / reset state
    {
        std::unique_lock<std::shared_mutex> wlk(sockMut);
        if (sock != INVALID_SOCKET) {
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
        connected.store(false, std::memory_order_release);
    }
}

int TCPClient::receiveAll(void* buffer, int length, int maxWait)
{
    if (!connected.load(std::memory_order_acquire))
        return 0; // not connected

    int bytesRead = 0;

    while (bytesRead < length) {
        // Snapshot the socket under a shared lock, then release it
        SOCKET s_copy;
        {
            std::shared_lock<std::shared_mutex> rlk(sockMut);
            s_copy = sock;
        }
        if (s_copy == INVALID_SOCKET) return 0;

        fd_set readfds; FD_ZERO(&readfds); FD_SET(s_copy, &readfds);
        timeval timeout{ maxWait, 0 };

        int activity = select(0, &readfds, nullptr, nullptr, &timeout);
        if (activity == SOCKET_ERROR) {
            // select error -> treat as hard failure
            return -1;
        } else if (activity == 0) {
            // timeout
            return 0;
        }

        int n = recv(s_copy, (char*)buffer + bytesRead, length - bytesRead, 0);
        if (n > 0) {
            bytesRead += n;
            continue;
        }
        if (n == 0) {
            // peer closed
            return 0;
        }
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            // Spurious — loop again
            continue;
        }
        // real recv error
        return -1;
    }

    return 1; // success
}

int TCPClient::transmitAll(const void* data, int length)
{
    if (!connected.load(std::memory_order_acquire))
        return -2;

    int totalSent = 0;

    while (totalSent < length) {
        SOCKET s_copy;
        {
            std::shared_lock<std::shared_mutex> rlk(sockMut);
            s_copy = sock;
        }
        if (s_copy == INVALID_SOCKET) return 0;

        fd_set writefds; FD_ZERO(&writefds); FD_SET(s_copy, &writefds);
        timeval timeout{ 1, 0 };
        int ready = select(0, nullptr, &writefds, nullptr, &timeout);
        if (ready == SOCKET_ERROR) return -1;
        if (ready == 0) return 0; // send timeout

        int n = send(s_copy, (const char*)data + totalSent, length - totalSent, 0);
        if (n > 0) { totalSent += n; continue; }
        if (n == 0) { return 0; }

        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) continue;
        return -1;
    }

    return 1;
}
