#include "TCPClient.h"

#include <cassert>
#include <thread>
#include <mutex>
#include <cassert>

#include "Shared/TCP.h"
#include "Shared/TCPCommunication.h"

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

bool TCPClient::tryConnect()
{
    const int retryDelayMs = 1000;

    while (!connected.load())
    {
        if (tryConnect(IP, PORT)) {
            std::cout << "Connected locally to IP address: " << IP << std::endl;
            connected.store(true);
            return true;
        }

        connected.store(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(retryDelayMs));
        std::cout << "Reconnecting\n";
    }

    return true;
}

bool TCPClient::tryConnect(const char *ipAddr, int port)
{
    int status;

    // Start WinSock /////////////////////////////////////////////////////////////
    // NOTE: This only applies to Windows, there is nothing like this for linux //
    WSADATA data;
	WORD version = MAKEWORD(2, 2);
	status = WSAStartup(version, &data);
	if (status != 0)
	{
		printf("Can't Start WinSock %d", status);
		return false;
	}
    //////////////////////////////////////////////////////////////////////////////

    // Create socket /////////////////////////////////////////////////////////////
    std::unique_lock<std::shared_mutex> lock(sockMut);
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        return false;
    }
    //////////////////////////////////////////////////////////////////////////////

    // Create Hint Structure for Socket //////////////////////////////////////////
    sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	status = inet_pton(AF_INET, ipAddr, &server.sin_addr);
    if (status <= 0) {
        std::cout << "Invalid address: " << ipAddr << std::endl;
        return false;
    }
    //////////////////////////////////////////////////////////////////////////////

    // Connect to server /////////////////////////////////////////////////////////
    status = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if (status < 0) {
        std::cerr << "Connection failed\n";
        return false;
    }
    //////////////////////////////////////////////////////////////////////////////

    return true;
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

void TCPClient::handleReconnect()
{
    std::cout << "Disconnect occurred. Trying to Reconnect..." << std::endl;

    if (!reconnecting.exchange(true)) {
        // Handle reconnect in this thread
        disconnect();
        std::cout << "[TCPClient] Reconnecting..." << std::endl;
        tryConnect();
        std::cout << "[TCPClient] Reconnected successfully.\n";
        reconnecting.store(false);
    } else {
        // Reconnect already being handled in another thread. Wait until connected
        while (reconnecting.load())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int TCPClient::receiveAll(void *buffer, int maxByteRead)
{
    bool success;
    tcpHeader messageSize;

    success = receive(&messageSize, sizeof(tcpHeader));
    if (!success) {
        return -1;  // signal disconnect
    }

    messageSize = ntohs(messageSize);
    if (messageSize > maxByteRead) {
        printf("Message exceeds maximum read specification. Max read: %i, Message size %i\n", maxByteRead, messageSize);
        assert(false);
        
        char* removeBuff = new char[messageSize];
        success = receive(removeBuff, messageSize, 1);   // clear TCP buffer of invalid message
        delete[] removeBuff;

        return success ? 0 : -1;
    }

    success = receive(buffer, messageSize);
    return success ? 1 : -1;
}

bool TCPClient::receive(void* buffer, int length, int maxWait)
{
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
                        return false; // TCP disconnected incorrectly
                    }
                }
            }
        }
    } else {
        return false; // Not connected
    }

    return true;
}

bool TCPClient::transmitAll(const void *data, int length)
{
    tcpHeader header = htons(length);

    if (!transmit((const char*)&header, sizeof(tcpHeader)))
        return false;
    
    if (!transmit((const char*)data, length))
        return false;

    return true;
}

bool TCPClient::transmit(const char *data, int length)
{
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
            int bytesSent = send(sock, data + totalSent, length - totalSent, 0);
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
