#include "VehicleClient.h"

#include "Shared/Keys.h"
#include "VehicleState.h"

VehicleClient::VehicleClient() {
    supervisorThread = std::thread([this]() { runSupervisor(); });
}

VehicleClient::~VehicleClient() {
    shutdownFlag.store(true);

    disconnect();             // already closes socket and joins workers

    // if a connect thread was running, wait for it
    if (connectionThread.joinable()) connectionThread.join();

    // supervisor thread exits when shutdownFlag==true
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
    reconnectRequested.store(false);   // << prevent supervisor from racing a reconnect

    stop();                            // does close + join

    // Drain queues (non-blocking)
    while (receiveQueue.tryPop().has_value()) { /* no-op */ }
    while (sendQueue.tryPop().has_value())     { /* no-op */ }
}

bool VehicleClient::start()
{
    if (!performHandshake()) {
        std::cout << "Handshake Failed" << std::endl;
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
    startWorkerThreads();
    return true;   // << add this
}

void VehicleClient::stop()
{
    stopFlag.store(true);
    cancelConnect.store(true);

    // IMPORTANT: first forcibly unblock any I/O
    client.disconnect();           // should call shutdown(fd, SHUT_RDWR) then close(fd)

    // wake any waits (if you add condition_variables for TX later)
    // tx_cv.notify_all();  // example

    stopWorkerThreads();           // now safe to join
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
    try {
        int status;
        while (!stopFlag.load()) 
        {
            MessageHeader header{};
            Message message;

            // header read
            int status = client.receiveAll(&header, sizeof(header), /*maxWaitSec=*/1);
            if (status <= 0) {
                // If we are intentionally stopping/disconnecting, just exit quietly
                if (stopFlag.load()) break;

                // Timeout -> just loop again (avoid spurious reconnect)
                if (status == 0) continue;

                // Hard error / peer closed -> request reconnect
                message.messageID = MessageID::Disconnected;
                receiveQueue.push(message);
                reconnectRequested.store(true);
                break;
            }


            message.messageID = header.messageID;

            constexpr uint32_t MAX_PAYLOAD_LENGTH = 1024 * 1024;
            std::cerr << "Payload length: " << header.payloadLength << std::endl;
            if (header.payloadLength > MAX_PAYLOAD_LENGTH) {
                std::cerr << "Payload too large!" << std::endl;
                reconnectRequested.store(true);
                break;
            }

            message.payload.resize(header.payloadLength);
            if (header.payloadLength > 0) {
                status = client.receiveAll(message.payload.data(), header.payloadLength, 1);
                if (status <= 0) {
                    if (stopFlag.load()) break;
                    if (status == 0) continue; // timeout, try again
                    std::cout << "Reconnect Requested" << std::endl;
                    message.messageID = MessageID::Disconnected;
                    receiveQueue.push(message);
                    reconnectRequested.store(true);
                    break;
                }
            }

            if (message.messageID == MessageID::Invalid) {
                continue;
            }

            if (header.messageID == MessageID::Ping) {
                // Be tolerant during disconnect / half-closed sockets
                if (message.payload.size() == sizeof(Ping)) {
                    Ping ping = extractPayload<Ping>(message);
                    uint64_t now = getCurrentTimeNs();
                    pingRTTms = (now - ping.clientSendTimeNs) / 1'000'000.0;
                } else {
                    // Treat as keepalive or ignore
                    std::cerr << "Ping payload size unexpected: " 
                              << message.payload.size() << " (expected " << sizeof(Ping) << ")\n";
                }
                continue; // don't push Ping to app queue
            }

            std::cout << "Received Feedback: " << static_cast<int>(message.messageID) << std::endl;
            receiveQueue.push(std::move(message));
        }
    } catch (const std::exception& ex) {
        std::cerr << "runReceive() exception: " << ex.what() << std::endl;
        reconnectRequested.store(true);
    } catch (...) {
        std::cerr << "runReceive() unknown exception\n";
        reconnectRequested.store(true);
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
    VehicleState::getInstance().stateMode = serverInit.stateMode;
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
