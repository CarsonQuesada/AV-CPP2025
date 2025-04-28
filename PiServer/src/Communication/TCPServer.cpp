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

#include "Debug/Logger.h"
#include "Shared/TCP.h"

bool TCPServer::waitForConnection()
{
    VehicleSys::getInstance().setConnectionStatus(ConnectionStatus::Reconnecting);

    while (true) {
        int serverSock = createListeningSock(IP);

        if (serverSock < 0) {
            std::cerr << "No valid socket to listen on. Retrying in 5s...\n";
            sleep(5);
            continue;
        }

        std::cout << "Waiting for a connection...\n";
        int clientSockFd = accept(serverSock, nullptr, nullptr);
        close(serverSock); // Done listening after one connection

        if (clientSockFd < 0) {
            perror("accept");
            continue;
        }

        std::cout << "Accepted connection\n";

        // Set to non-blocking
        int flags = fcntl(clientSockFd, F_GETFL, 0);
        if (flags == -1 || fcntl(clientSockFd, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl O_NONBLOCK");
            close(clientSockFd);
            continue;
        }

        std::unique_lock<std::shared_mutex> lock(sockMut);
        clientSock = clientSockFd;
        connected.store(true);
        VehicleSys::getInstance().setConnectionStatus(ConnectionStatus::Connected);
        return true;
    }
}

TCPServer::~TCPServer()
{
    disconnect();
    VehicleSys::getInstance().setConnectionStatus(ConnectionStatus::Disabled);
}

int TCPServer::createListeningSock(const char *ipAddr)
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
    addr.sin_port = htons(PORT);
    status = inet_pton(AF_INET, ipAddr, &addr.sin_addr);
    if (status <= 0) {
        std::cout << "Invalid address: " << ipAddr << std::endl;
        return status;
    }

    // bind the listening socket /////////////////////////////////////////////////
    status = bind(sock, (sockaddr*)&addr, sizeof(addr));
    if (status < 0) {
        perror(("bind failed on " + std::string(ipAddr)).c_str());
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

    std::cout << "Listening on " << ipAddr << ":" << PORT << std::endl;
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

void TCPServer::handleReconnect()
{
    if (!reconnecting.exchange(true)) {
        VehicleSys::getInstance().setConnectionStatus(ConnectionStatus::Reconnecting);
        disconnect();

        std::cout << "[TCPClient] Reconnecting..." << std::endl;
        while (!waitForConnection())
            std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "[TCPClient] Reconnected successfully.\n";
        reconnecting.store(false);
    } else {
        while (reconnecting.load()) 
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int TCPServer::receiveAll(void *buffer, int maxByteRead)
{
    bool success;
    tcpHeader messageSize;
    success = receive(&messageSize, sizeof(tcpHeader));
    if (!success) { 
        return -1;  // signal disconnect
    }

    messageSize = ntohs(messageSize);
    if (messageSize > maxByteRead) {
        ASSERT(true, "Message exceeds maximum read specification. Max read: %i, Message size %i", maxByteRead, messageSize);
        
        char* removeBuff = new char[messageSize];
        success = receive(removeBuff, messageSize, 1);   // clear TCP buffer of invalid message
        delete[] removeBuff;
        if (!success)
            return -1;  // signal disconnect
        else
            return 0;   // signal max byte read exceeded for message
    }

    success = receive(buffer, messageSize);
    if (!success) {
        return -1;  // signal disconnect
    }

    return 1;   // Signal success
}

bool TCPServer::receive(void *buffer, int length, int maxWait)
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
                LOG(LogLevel::WARNING, "Error in select(): %s\n", strerror(errno));
                return false;
            } else if (activity == 0) {
                // Timeout reached, no data received
                LOG(LogLevel::INFO, "Timeout reached while waiting for data.\n");
                return false;
            } else if (FD_ISSET(clientSock, &readfds)) {
                // Begin recieving message
                int bytesRecovered = recv(clientSock, (char*)buffer + bytesRead, length - bytesRead, MSG_DONTWAIT);
    
                if (bytesRecovered > 0) {
                    bytesRead += bytesRecovered;
                } else if (bytesRecovered == 0) {
                    LOG(LogLevel::INFO, "Connection closed gracefully by user\n");
                    return false; 	// Connection closed by user gracefully
                } else if (bytesRecovered < 0) {
                    if (errno == EWOULDBLOCK || errno == EAGAIN) {
                        LOG(LogLevel::INFO, "Recieved no data\n");
                    } else {
                        LOG(LogLevel::WARNING, "TCP disconnected incorrectly\n");
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
    tcpHeader header = htons(length);

    if (!transmit((const char*)&header, sizeof(tcpHeader)))
        return false;
    
    if (!transmit((const char*)data, length))
        return false;

    return true;
}

bool TCPServer::transmit(const char *data, int length)
{
    int totalSent = 0;
    const int timeoutSeconds = 1;

    std::shared_lock<std::shared_mutex> lock(sockMut); // shared with receive()
    if (connected.load()) {
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
            int bytesSent = send(clientSock, data + totalSent, length - totalSent, 0);
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
    }

    return true;
}
