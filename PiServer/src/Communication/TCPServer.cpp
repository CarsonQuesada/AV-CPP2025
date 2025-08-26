#include "TCPServer.h"

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <mutex>
#include <chrono>

bool TCPServer::waitForConnection(std::atomic<bool>& cancelConnectFlag, int port, const char* ipAddr)
{
    while (!cancelConnectFlag.load()) {
        int serverSock;
        if (ipAddr == nullptr || std::string(ipAddr) == "0.0.0.0")
            serverSock = createListeningSock(port);
        else
            serverSock = createListeningSock(port, ipAddr);

        if (serverSock < 0) {
            std::cerr << "No valid socket to listen on. Retrying in 5s...\n";
            for (int i = 0; i < 5 && !cancelConnectFlag.load(); i++) sleep(1);
            continue;
        }

        std::cout << "Waiting for a connection...\n";

        fd_set fds;
        struct timeval tv;
        while (!cancelConnectFlag.load()) {
            FD_ZERO(&fds);
            FD_SET(serverSock, &fds);
            tv.tv_sec = 1;
            tv.tv_usec = 0;

            int ret = select(serverSock + 1, &fds, nullptr, nullptr, &tv);
            if (ret > 0 && FD_ISSET(serverSock, &fds)) {
                int clientSockFd = accept(serverSock, nullptr, nullptr);
                close(serverSock);

                if (clientSockFd < 0) {
                    perror("accept");
                    break; // back to outer loop
                }

                std::cout << "Accepted connection! clientSock = " << clientSockFd << std::endl;

                // set non-blocking
                int flags = fcntl(clientSockFd, F_GETFL, 0);
                fcntl(clientSockFd, F_SETFL, flags | O_NONBLOCK);

                std::unique_lock<std::shared_mutex> lock(sockMut);
                clientSock = clientSockFd;
                connected.store(true);
                return true;
            }
        }

        close(serverSock);
    }
    return false; // cancelled
}

TCPServer::~TCPServer()
{
    disconnect();
}

int TCPServer::createListeningSock(int port, const char *ipAddr)
{
    int status;
    // Create socket /////////////////////////////////////////////////////////////
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    // Set socket option to allow reuse of sock in short time span ///////////////
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    // Create Hint Structure for Socket //////////////////////////////////////////
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ipAddr == nullptr || std::string(ipAddr) == "0.0.0.0") {
        addr.sin_addr.s_addr = INADDR_ANY;
    } else {
        status = inet_pton(AF_INET, ipAddr, &addr.sin_addr);
        if (status <= 0) {
            std::cout << "Invalid address: " << ipAddr << std::endl;
            close(sock);
            return status;
        }
    }

    // bind the listening socket /////////////////////////////////////////////////
    status = bind(sock, (sockaddr*)&addr, sizeof(addr));
    if (status < 0) {
        std::string ipStr = (ipAddr != nullptr) ? ipAddr : "0.0.0.0";
        perror(("bind failed on " + ipStr).c_str());
        close(sock);
        return status;
    }

    // Begin listening ///////////////////////////////////////////////////////////
    status = listen(sock, 1);
    if (status < 0) {
        perror("listen");
        close(sock);
        return status;
    }

    const char* ipToPrint = ipAddr ? ipAddr : "0.0.0.0";
    std::cout << "Listening on " << ipToPrint << ":" << port << std::endl;
    return sock;
}

void TCPServer::disconnect()
{
    std::unique_lock<std::shared_mutex> lock(sockMut);
    if (connected.load()) {
        shutdown(clientSock, SHUT_RDWR);
        close(clientSock);
        connected.store(false);
    }
}

bool TCPServer::receiveAll(void *buffer, int length, int maxWait)
{
    int bytesRead = 0;

    // Set up select()
    fd_set readfds;
    timeval timeout;

    std::shared_lock<std::shared_mutex> lock(sockMut); // shared with transmit()
    if (connected.load()) {
        while (bytesRead < length) {
            FD_ZERO(&readfds);           // Clear the readfds set
            FD_SET(clientSock, &readfds); // Add the client socket to the read set
            timeout.tv_sec = maxWait;   // Timeout after 5 seconds
            timeout.tv_usec = 0;  // Timeout after 5 seconds
            int activity = select(clientSock + 1, &readfds, nullptr, nullptr, &timeout);    // Wait for the socket to be ready for reading, with timeout
    
            if (activity < 0) {
                std::cout << "Error in select(): " << strerror(errno) << std::endl;
                return false;
            } else if (activity == 0) {
                // Timeout reached, no data received
                std::cout << "Timeout reached while waiting for data." << std::endl;
                return false;
            } else if (FD_ISSET(clientSock, &readfds)) {
                // Begin recieving message
                int bytesRecovered = recv(clientSock, (char*)buffer + bytesRead, length - bytesRead, 0);
    
                if (bytesRecovered > 0) {
                    bytesRead += bytesRecovered;
                } else if (bytesRecovered == 0) {
                    std::cout << "Connection closed gracefully by user" << std::endl;
                    return false; 	// Connection closed by user gracefully
                } else if (bytesRecovered < 0) {
                    if (errno == EWOULDBLOCK || errno == EAGAIN) {
                        std::cout << "Recieved no data" << std::endl;
                    } else {
                        std::cout << "TCP disconnected incorrectly" << std::endl;
                        return false;   // TCP disconnected incorrectly
                    }
                }
            }
        }
    } else {
        return false;
    }

    return true;
}

bool TCPServer::transmitAll(const void *data, int length)
{
    int totalSent = 0;
    const int timeoutSeconds = 1;

    std::shared_lock<std::shared_mutex> lock(sockMut); // shared with receive()

    while (totalSent < length) {
        // Wait for the socket to be writable
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(clientSock, &writefds);

        struct timeval timeout;
        timeout.tv_sec = timeoutSeconds;
        timeout.tv_usec = 0;

        int ready = select(clientSock + 1, nullptr, &writefds, nullptr, &timeout);
        if (ready < 0) {
            std::cerr << "select() error: " << strerror(errno) << "\n";
            return false;
        } else if (ready == 0) {
            std::cerr << "sendAll() timeout while waiting to send.\n";
            return false;
        }

        // Write to socket
        int bytesSent = send(clientSock, (const char*)data + totalSent, length - totalSent, 0);
        if (bytesSent < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue; // Try again
            } else {
                std::cerr << "send() error: " << strerror(errno) << "\n";
                return false;
            }
        } else if (bytesSent == 0) {
            std::cerr << "Connection closed by peer.\n";
            return false;
        }

        totalSent += bytesSent;
    }

    return true;
}
