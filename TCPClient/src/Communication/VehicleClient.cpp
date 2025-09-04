#include "VehicleClient.h"

#include "Shared/Keys.h"
#include "VehicleState.h"

VehicleClient::VehicleClient() {
    supervisorThread = std::thread([this]() { runSupervisor(); });
}

VehicleClient::~VehicleClient() {
    shutdownFlag.store(true);
    disconnect();

    client.disconnect();

    if (connectionThread.joinable()) connectionThread.join();
    if (supervisorThread.joinable()) supervisorThread.join();
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
    bool success;
    std::cout << "Connecting to " << ipAddr << std::endl;
    stop();
    connectionState.store(ClientConnectionState::Connecting);
    cancelConnect.store(false);

    // Try to connect via TCPClient
    if (client.tryConnect(ipAddr.c_str(), PORT, cancelConnect, 5000)) {
        std::cout << "Connect SUCCEEDED" << std::endl;
        std::cout << "Connected to " << ipAddr << std::endl;
        // Try connect succeeded
        success = start();
    } else {
        std::cout << "Connect FAILED" << std::endl;
        // Try connect failed
        connectionState.store(ClientConnectionState::Disconnected);
        cancelConnect.store(false);
        success = false;
    }

    return success;
}

void VehicleClient::runSupervisor() {
    while (!shutdownFlag.load()) {
        if (reconnectRequested.load()) {
            std::cout << "Reconnect detected in supervisor" << std::endl;
            stopWorkerThreads();
            if (reconnect()) {
                std::cout << "Reconnect successful" << std::endl;
            } else {
                connectionState.store(ClientConnectionState::Disconnected);
            }
            reconnectRequested.store(false);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool VehicleClient::reconnect()
{
    std::cout << "Doing reconnect" << std::endl;
    if (lastConnectionType != ConnectionType::None && connectionState.exchange(ClientConnectionState::Reconnecting) != ClientConnectionState::Reconnecting) {
        // If there is a last connection type and if no thread is currently reconnecting
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

    // Drain queues
    while (true) {
        auto messageOpt = receiveQueue.tryPop();
        if (!messageOpt.has_value()) break;
        // Optionally: process or log messageOpt.value()
    }

    while (true) {
        auto messageOpt = sendQueue.tryPop();
        if (!messageOpt.has_value()) break;
        // Optionally: process or log messageOpt.value()
    }
}

bool VehicleClient::start()
{
    if (!performHandshake()) {
        return false;
    }

    stopFlag.store(false);
    connectionState.store(ClientConnectionState::Connected);
    cancelConnect.store(false);

    std::lock_guard<std::mutex> lock(threadStartMutex);
    if (receiveThread.joinable() || transmitThread.joinable() || updateThread.joinable()) {
        std::cerr << "start() called while threads already running!" << std::endl;
        return false;
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
    std::cout << "Started worker threads" << std::endl;
}

void VehicleClient::stopWorkerThreads() {
    std::cout << "Stopping worker threads" << std::endl;
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
    std::cout << "Stopped worker threads" << std::endl;
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
            break;
        }

        message.messageID = header.messageID;

        constexpr uint32_t MAX_PAYLOAD_LENGTH = 1024 * 1024; // 1 MB limit, adjust as needed
        std::cerr << "Payload length: " << header.payloadLength << std::endl;
        if (header.payloadLength > MAX_PAYLOAD_LENGTH) {
            std::cerr << "Payload too large!" << std::endl;
            reconnectRequested.store(true);
            break;
        }

        message.payload.resize(header.payloadLength);
        status = client.receiveAll(message.payload.data(), header.payloadLength);
        if (status < 0) {
            // Client disconnected from server
            std::cout << "Reconnect Requested" << std::endl;
            message.messageID = MessageID::Disconnected;
            receiveQueue.push(message);
            reconnectRequested.store(true);
            break;
        }
        
        if (message.messageID != MessageID::Invalid) {
            if (header.messageID == MessageID::Ping) {
                Ping ping = extractPayload<Ping>(message); // Assuming you have this
                uint64_t now = getCurrentTimeNs();
                pingRTTms = (now - ping.clientSendTimeNs) / 1'000'000.0;
                continue;
            } else {
                std::cout << "Received Feedback: " << static_cast<int>(message.messageID) << std::endl;
                receiveQueue.push(message);
            }
        }
    }
}

void VehicleClient::runTransmit()
{
    while (!stopFlag.load() && !reconnectRequested.load())
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
        //std::cout << "Sending message: " << static_cast<int>(header.messageID) << std::endl;

        std::cout << "Header: Message type - " << static_cast<int>(header.messageID) << " Message length - " << header.payloadLength << " bytes" << std::endl;
        bool status = client.transmitAll(&header, sizeof(header));
        if (!status) {
            std::cout << "Reconnect Requested on header" << std::endl;
            reconnectRequested.store(true);
            return;
        }

        std::cout << "Payload size: " << message.payload.size() << " bytes" << std::endl;
        status = client.transmitAll(message.payload.data(), message.payload.size());
        if (!status) {
            std::cout << "Reconnect Requested on payload" << std::endl;
            reconnectRequested.store(true);
            return;
        }
    }
}

void VehicleClient::runRegularUpdate()
{
    const std::chrono::milliseconds loopInterval(10);
    const std::chrono::milliseconds pingInterval(3000); // 300 × 10ms = 3000ms

    auto lastPingTime = std::chrono::steady_clock::now();

    bool status;

    while (!stopFlag.load()) {
        std::this_thread::sleep_for(loopInterval);

        auto now = std::chrono::steady_clock::now();

        // ---- Ping ----
        if (now - lastPingTime >= pingInterval) {
            // Send ping command
            Ping pingMsg;
            pingMsg.clientSendTimeNs = getCurrentTimeNs();

            MessageHeader header;
            header.messageID = MessageID::Ping;
            header.payloadLength = sizeof(pingMsg);

            status = client.transmitAll(&header, sizeof(header));
            if (!status) {
                std::cout << "Reconnect Requested" << std::endl;
                reconnectRequested.store(true);
                return;
            }
            status = client.transmitAll(&pingMsg, header.payloadLength);
            if (!status) {
                std::cout << "Reconnect Requested" << std::endl;
                reconnectRequested.store(true);
                return;
            }

            lastPingTime = now;
        }
    }
}

bool VehicleClient::performHandshake()
{
    std::cout << "Performing handshake." << std::endl;
    // 1. Send ClientInit
    ClientInit init = {};
    MessageHeader initHeader;
    initHeader.messageID = MessageID::ClientInit;
    initHeader.payloadLength = sizeof(init);
    Message initMsg = makeMessageFrom(init);
    std::cout << "Made it 1" << std::endl;
    if (!client.transmitAll(&initHeader, sizeof(initHeader))) {
        std::cout << "Failed to send messageID." << std::endl;
        return false;
    }
    if (!client.transmitAll(initMsg.payload.data(), initMsg.payload.size())) {
        std::cout << "Failed to send the payload." << std::endl;
        return false;
    }

    // 2. Receive ServerInit
    MessageHeader header;
    std::cout << "Made it 2" << std::endl;
    if (client.receiveAll(&header, sizeof(header)) <= 0) return false;
    if (header.messageID != MessageID::ServerInit || header.payloadLength != sizeof(ServerInit)) return false;

    std::cout << "Made it 3" << std::endl;
    std::vector<uint8_t> payload(header.payloadLength);
    if (client.receiveAll(payload.data(), payload.size()) <= 0) return false;

    Message msg = { header.messageID, std::move(payload) };
    ServerInit serverInit = extractPayload<ServerInit>(msg);
    VehicleState::getInstance().genStatus = serverInit.generalStatus;
    VehicleState::getInstance().autoStatus = serverInit.autopilotStatus;
    VehicleState::getInstance().driveStatus = serverInit.driveStatus;
    VehicleState::getInstance().lightStatus = serverInit.lightsStatus;

    std::cout << "Handshake successful." << std::endl;

    // You can store this info in internal variables if needed
    return true;
}

uint64_t VehicleClient::getCurrentTimeNs()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}
