#include "VehicleClient.h"

#include "Shared/Keys.h"

VehicleClient::VehicleClient() {
    supervisorThread = std::thread([this]() { runSupervisor(); });
}

VehicleClient::~VehicleClient() {
    std::cout << "Pause 5" << std::endl;
    disconnect();

    client.disconnect();

    if (connectionThread.joinable()) connectionThread.join();
    if (supervisorThread.joinable()) supervisorThread.join();
    std::cout << "Pause 6" << std::endl;
}

bool VehicleClient::connectLocally()
{
    if (connectionState.exchange(ClientConnectionState::Connecting) == ClientConnectionState::Disconnected)
    {
        // Launch a thread to connect
        if (connectionThread.joinable()) connectionThread.join(); // cleanup any previous connection thread

        connectionThread = std::thread([this]() {
            if (connect(LOCAL_PI_IP)) {
                lastConnectionType = ConnectionType::Local;
            }
        });

        return true;
    }
    else {
        std::cout << "Connection state currently connected, connecting or reconnecting" << std::endl;
        return false;
    }
}

bool VehicleClient::connectRemotely()
{
    std::cout << "Connecting remotely 1" << std::endl;
    if (connectionState.exchange(ClientConnectionState::Connecting) == ClientConnectionState::Disconnected)
    {
        std::cout << "Connecting remotely 2" << std::endl;
        if (connectionThread.joinable()) connectionThread.join(); // cleanup any previous connection thread

        connectionThread = std::thread([this]() {
            if (connect(TAILSCALE_PI_IP)) {
                lastConnectionType = ConnectionType::Remote;
            }
        });

        return true;
    }
    else {
        std::cout << "Connection state currently connected, connecting or reconnecting" << std::endl;
        return false;
    }
}

bool VehicleClient::connect(const std::string& ipAddr)
{
    std::cout << "Connecting to " << ipAddr << std::endl;
    stop();
    connectionState.store(ClientConnectionState::Connecting);
    cancelConnect.store(false);
    std::cout << "Made it past stop" << std::endl;

    // Try to connect via TCPClient
    if (client.tryConnect(ipAddr.c_str(), PORT, cancelConnect, 5000)) {
        std::cout << "Connect SUCCEEDED" << std::endl;
        // Try connect succeeded
        stopFlag.store(false);
        connectionState.store(ClientConnectionState::Connected);
        cancelConnect.store(false);
        start();
        std::cout << "Connected to " << ipAddr << std::endl;
        return true;
    } else {
        std::cout << "Connect FAILED" << std::endl;
        // Try connect failed
        connectionState.store(ClientConnectionState::Disconnected);
        cancelConnect.store(false);
        return false;
    }
}

void VehicleClient::runSupervisor() {
    while (!stopFlag.load()) {
        if (reconnectRequested.load()) {
            stopWorkerThreads();
            if (reconnect()) {
                startWorkerThreads();
            } else {
                reconnectRequested.store(true); // Retry again
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool VehicleClient::reconnect()
{
    if (lastConnectionType != ConnectionType::None && connectionState.exchange(ClientConnectionState::Reconnecting) != ClientConnectionState::Reconnecting) {
        // If there is a last connection type and if no thread is currently Connecting
        if (lastConnectionType == ConnectionType::Local)
            return connect(LOCAL_PI_IP);
        else if (lastConnectionType == ConnectionType::Remote)
            return connect(TAILSCALE_PI_IP);
        else {
            std::cout << "Invalid connection type in VehicleClient::reconnect()" << std::endl;
            connectionState.store(ClientConnectionState::Disconnected);
            return false;
        }
    } else {
        return false;
    }
}

void VehicleClient::disconnect()
{
    lastConnectionType = ConnectionType::None;
    stop();
}

void VehicleClient::start()
{
    std::lock_guard<std::mutex> lock(threadStartMutex);
    if (receiveThread.joinable() || transmitThread.joinable() || updateThread.joinable()) {
        std::cerr << "start() called while threads already running!" << std::endl;
        return;
    }
    stopFlag.store(false);
    startWorkerThreads();
}

void VehicleClient::stop()
{
    stopFlag.store(true);
    cancelConnect.store(true); // in case we're reconnecting
    stopWorkerThreads();

    client.disconnect();
    connectionState = ClientConnectionState::Disconnected;
}

void VehicleClient::startWorkerThreads() {
    receiveThread = std::thread([this]() { runReceive(); });
    transmitThread = std::thread([this]() { runTransmit(); });
    updateThread  = std::thread([this]() { runRegularUpdate(); });
}

void VehicleClient::stopWorkerThreads() {
    if (receiveThread.joinable()) {
        receiveThread.join(); 
        receiveThread = std::thread();
    }

    if (transmitThread.joinable()) {
        transmitThread.join(); 
        transmitThread = std::thread();
    }

    if (updateThread.joinable()) {
        updateThread.join(); 
        updateThread = std::thread();
    }
}

void VehicleClient::runReceive()
{
    int status;

    while (!stopFlag.load()) 
    {
        MessageHeader header;
        Message message;

        status = client.receiveAll(&header, sizeof(header));
        if (status < 0) {
            // Client disconnected from server
            message.messageID = MessageID::Disconnected;
            receiveQueue.push(message);
            reconnectRequested.store(true);
            return;
        }

        message.messageID = header.messageID;
        message.payload.resize(header.payloadLength);
        status = client.receiveAll(message.payload.data(), header.payloadLength);
        if (status < 0) {
            // Client disconnected from server
            message.messageID = MessageID::Disconnected;
            receiveQueue.push(message);
            reconnectRequested.store(true);
            return;
        }
        
        if (message.messageID != MessageID::Invalid) {
            std::cout << "Received Feedback: " << static_cast<int>(message.messageID) << std::endl;
            receiveQueue.push(message);
        }
    }
}

void VehicleClient::runTransmit()
{
    while (!stopFlag.load())
    {
        auto optionalMessage = sendQueue.tryPop();

        if (!optionalMessage.has_value()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // avoid busy waiting
            continue;
        }

        const Message& message = optionalMessage.value();
        MessageHeader header;
        header.messageID = message.messageID;
        header.payloadLength = message.payload.size();

        bool status = client.transmitAll(&header, sizeof(header));
        if (!status) {
            reconnectRequested.store(true);
            return;
        }

        status = client.transmitAll(message.payload.data(), message.payload.size());
        if (!status) {
            reconnectRequested.store(true);
            return;
        }
    }
}

void VehicleClient::runRegularUpdate()
{
    const std::chrono::milliseconds interval(10);
    const int pingInterval = 300;
    bool status;

    int pingIntervalCount = 0;
    while (!stopFlag.load()) {
        std::this_thread::sleep_for(interval);
        // increment interval counts
        pingIntervalCount++;

        if (pingIntervalCount == pingInterval) {
            // Send ping command and reset pingIntervalCount
            pingIntervalCount = 0;
            // Only need to send header
            MessageHeader header;
            header.messageID = MessageID::Ping;
            header.payloadLength = 0;
            status = client.transmitAll(&header, sizeof(header));
            if (!status) {
                reconnectRequested.store(true);
                return;
            }
        }
    }
}
