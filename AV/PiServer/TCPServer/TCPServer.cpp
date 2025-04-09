#include "TCPServer.h"

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "Debug/Logger.h"

int TCPServer::get_user_configurations()
{
    int userInput = 0;
	std::cout << "What address should I listen on? 1 for local, 2 for VPN, 3 for custom: ";
	std::cin >> userInput;

    bool validInput;
    do {
        validInput = true;
        switch (userInput)
        {
            case 1:
                ipAddress = "192.168.5.132";
                tcpPort = 54000;
                break;
            case 2:
                ipAddress = "10.8.0.2";
                tcpPort = 54000;
                break;
            case 3:
                std::cout << "Enter IP: ";
                std::cin >> ipAddress;
                std::cout << "\nEnter Port: ";
                std::cin >> tcpPort;
                break;
            default:
                std::cout << "Invalid input!" << std::endl;
                validInput = false;
        }
    } while (!validInput);

	printf("Accepted values: IP = %s Port = %i", ipAddress.c_str(), tcpPort);

    // --- Prompt for Maximum Speed ---
    int maxSpeed;
	std::cout << "\nSet max speed (1-100): ";
	std::cin >> maxSpeed;
	
	// Ensure the speed is within valid bounds
	while(maxSpeed <= 0) {
		std::cout << "\nSet max speed (1-100): ";
		std::cin >> maxSpeed;
	}

	if (maxSpeed > 100) {
		maxSpeed = 100; // Cap speed at 100 if user input exceeds the limit
	}
	std::cout << "Speed set to " << maxSpeed << "\n";

    return maxSpeed;
}

bool TCPServer::setup_TCP_server()
{
    bool socketBound = false;
    int listening;
    std::cout << "Opening Socket! Listening at " << ipAddress << ": Port " << tcpPort << std::endl;
    do {
        // --- Create a Listening Socket ---
        listening = socket(AF_INET, SOCK_STREAM, 0); // Create a socket for IPv4 and TCP
        if (listening == -1) { // Check if socket creation failed
            std::cerr << "Can't create socket";
            return -1; // Return error code
        }

        // --- Configure the Socket Address ---
        sockaddr_in hint;           		// Structure to hold server address details
        hint.sin_family = AF_INET;  		// Specify IPv4
        hint.sin_port = htons(tcpPort);		// Convert port number to network byte order
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr); // Convert IP address to binary format

        // --- Bind the Socket to the IP and Port ---
        if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) { // Attempt to bind the socket
            ASSERT(true, "Can't bind to IP/Port");
            socketBound = false; // Retry the setup process if binding fails
        } else {
            LOG(LogLevel::INFO, "Bound successfully");
            socketBound = true;
        }
    }   while (!socketBound);

	// --- Mark the Socket for Listening ---
	if (listen(listening, SOMAXCONN) == -1)	{ // Attempt to listen for incoming connections
		std::cerr << "Can't listen";
		return -3; // Return error code
	}

	// --- Accept a Client Connection ---
	sockaddr_in client;     // Structure to hold client address details
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];	// Buffer to store client's hostname
	char svc[NI_MAXSERV];	// Buffer to store client's service name

	clientSocket = accept(listening, (sockaddr*)&client, &clientSize); // Accept an incoming connection
	close(listening); // Close the listening socket after accepting a client

	// --- Resolve Client Information ---
	std::memset(host, 0, NI_MAXHOST);	// Clear the host buffer
	std::memset(svc, 0, NI_MAXSERV);	// Clear the service buffer
	int result = getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);

	if (result) {
		// If hostname resolution is successful, print the hostname and service
		std::cout << host << " connected on " << svc << " connection 1"<< std::endl;
	}
	else {
		// If hostname resolution fails, fall back to raw IP and port
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on " << ntohs(client.sin_port) << " connection 2"<< std::endl;
	}
	std::cout << "EXITING TCP STARTUP" << std::endl;

	if (clientSocket)
    {
        std::cout << "TCP server setup OK!" << std::endl;
        return connected = true;
    }
	else
    {
        std::cout << "Failed to setup TCP server!" << std::endl;
        return connected = false;
    }
}

bool TCPServer::retrieve_client_control(UserInput& userInput)
{
    int bytesRead = 0;

    do {
        socketBuff.clear_buffer();
        bytesRead = recv(clientSocket, socketBuff.expose_buffer(), bufferSize, MSG_DONTWAIT);

        if (bytesRead > 0) {
            LOG(LogLevel::INFO, "Read byte count: %i", bytesRead);
            LOG(LogLevel::INFO, "Received: %s", socketBuff.expose_buffer());
        } else if (bytesRead == 0) {
            LOG(LogLevel::INFO, "Connection closed gracefully by user\n");
            close(clientSocket);
            connected = false;
            return false; 	// Connection closed by user gracefully
        } else if (!(errno == EWOULDBLOCK || errno == EAGAIN)) {
            LOG(LogLevel::WARNING, "TCP disconnected incorrectly\n");
            close(clientSocket);
            connected = false;
            return false;   // TCP disconnected incorrectly
        }
    } while (!(bytesRead >= preParseBuffSize && bytesRead <= (preParseBuffSize * 3)));

    userInput = socketBuff.parse_control_data();

    return true;
}



TCPServer::~TCPServer()
{
    if (connected)
        close(clientSocket);
}

void TCPServer::closeSocket()
{
    if (connected) {
        close(clientSocket);
        connected = false;
    }
}

// int TCPServer::retrieve_serial_control(UserInputBuff &serialBuff)
// {
//     serialBuff.dataReady = false;
//     int bytesRead = serialPort.retrieve_serial_data(serialBuff);

//     // check for valid received byte count
//     if (bytesRead == preParseBuffSize) {
//         serialBuff.dataReady = true;	// Mark data as ready
//     } else {
//         serialBuff1.dataReady = false; 	// Mark data as not ready if insufficient bytes or serial is disabled
//     }

//     return bytesRead;
// }
