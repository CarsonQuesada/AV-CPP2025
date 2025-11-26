#include "VehicleClient.h"

#include <iomanip>

#include "Shared/Keys.h"
#include "Shared/DebugHelpers.h"
#include "VehicleState.h"

VehicleClient::VehicleClient() {
}

VehicleClient::~VehicleClient() {
    shutdownFlag.store(true);

    disconnect();             // already closes socket and joins workers

    // if a connect thread was running, wait for it
    if (connectionThread.joinable()) connectionThread.join();
}

bool VehicleClient::connectLocally()
{
    if (connectionState.exchange(ClientConnectionState::Connecting) == ClientConnectionState::Disconnected)
    {
        // Launch a thread to connect
        if (connectionThread.joinable()) connectionThread.join(); // cleanup any previous connection thread

        connectionThread = std::thread([this]() {
            if (connect(LOCAL_PI_IP, LOCAL_TCP_PORT)) {
                currConnectionType = ConnectionType::Local;
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
            if (connect(VM_PUBLIC_IP, REMOTE_TCP_PORT)) {
                currConnectionType = ConnectionType::Remote;
            }
        });

        return true;
    }
    else {
        std::cout << "Connection state currently connected, connecting or reconnecting" << std::endl;
        return false;
    }
}

bool VehicleClient::connect(const std::string& ipAddr, const int port)
{
    bool success;
    std::cout << "Connecting to " << ipAddr << std::endl;
    stop();
    connectionState.store(ClientConnectionState::Connecting);
    cancelConnect.store(false);

    // Try to connect via TCPClient
    if (client.tryConnect(ipAddr.c_str(), port, cancelConnect, 5000)) {
        std::cout << "Connect SUCCEEDED" << std::endl;
        std::cout << "Connected to " << ipAddr << std::endl;
        success = onConnect();
    } else {
        std::cout << "Connect FAILED" << std::endl;
        connectionState.store(ClientConnectionState::Disconnected);
        currConnectionType.store(ConnectionType::None);
        cancelConnect.store(false);
        success = false;
    }

    return success;
}

bool VehicleClient::reconnect()
{
    if (lastConnectionType == ConnectionType::None) return false;

    auto prev = connectionState.exchange(ClientConnectionState::Reconnecting);
    if (prev == ClientConnectionState::Reconnecting) return false;

    if (connectionThread.joinable()) connectionThread.join();

    connectionThread = std::thread([this]() {
        ConnectionType type = lastConnectionType.load();
        if (type == ConnectionType::Local) {
            connect(LOCAL_PI_IP, LOCAL_TCP_PORT);
        } else if (type == ConnectionType::Remote) {
            connect(VM_PUBLIC_IP, REMOTE_TCP_PORT);
        } else {
            connectionState.store(ClientConnectionState::Disconnected);
        }
    });
    return true;
}

void VehicleClient::disconnect()
{
    currConnectionType = ConnectionType::None;

    stop(); // does close + join

    // Drain queues (non-blocking)
    while (receiveQueue.tryPop().has_value()) { }
    while (sendQueue.tryPop().has_value())     { }
}

bool VehicleClient::onConnect()
{
    if (!performHandshake()) {
        std::cout << "Handshake Failed" << std::endl;
        return false;
    }

    stopFlag.store(false);
    connectionState.store(ClientConnectionState::Connected);
    cancelConnect.store(false);

    std::lock_guard<std::mutex> lock(threadStartMutex);
    startWorkerThreads();
    return true;
}

void VehicleClient::stop()
{
    stopFlag.store(true);
    cancelConnect.store(true);

    // first forcibly unblock any I/O
    client.disconnect(); 

    stopWorkerThreads();    // now safe to join
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

// This function is run in its own thread. 
// Responsible for receiving messages from the server.
// Responsible for auto reconnect on server disconnect.
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
                if (stopFlag.load()) break; // intentional stop
                if (status == 0) continue;  // timeout, keep polling

                // Hard error / peer closed -> reconnect
                message.messageID = MessageID::Disconnected;
                receiveQueue.push(message);

                onServerDisconnect();   // Set state
                reconnect();            // Try to reconnect
                break;
            }

            // Checks for valid header
            if (header.payloadLength == 0 || header.payloadLength > MAX_PAYLOAD) {
                std::cerr << "[CLIENT] BAD header from server: id=" << int(header.messageID)
                        << " len=" << header.payloadLength << " — resetting\n";
                disconnect();
                break;
            }
            auto expect = expectedPayloadSize(header.messageID);
            if (!expect.has_value()) {
                std::cerr << "[CLIENT] BAD id from server: " << int(header.messageID)
                        << " (" << msgName(header.messageID) << ") — resetting\n";
                disconnect();
                break;
            }

            // Copy messageID from header to message
            message.messageID = header.messageID;

            // payload read
            message.payload.resize(header.payloadLength);
            if (header.payloadLength > 0) {
                status = client.receiveAll(message.payload.data(), header.payloadLength, 1);
                if (status <= 0) {
                    if (stopFlag.load()) break;
                    if (status == 0) continue; // timeout, try again
                    std::cout << "Reconnect Requested" << std::endl;
                    
                    message.messageID = MessageID::Disconnected;
                    receiveQueue.push(message);

                    onServerDisconnect();   // Set state
                    reconnect();            // Try to reconnect
                    break;
                }
            }

            // Check for valid payload
            if (message.payload.size() != expect.value()) {
                std::cerr << "[CLIENT] BAD payload size for id=" << int(header.messageID)
                        << " (" << msgName(header.messageID) << ") len=" << message.payload.size()
                        << " expected=" << expect.value() << " — resetting\n";
                disconnect();
                break;
            }

            // If invalid message ID, skip
            if (message.messageID == MessageID::Invalid) {
                continue;
            }

            // Handle Ping messages internally
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

            // Push to receive queue
            receiveQueue.push(std::move(message));
        }
    } catch (const std::exception& ex) {
        std::cerr << "runReceive() exception: " << ex.what() << std::endl;
        disconnect();
    } catch (...) {
        std::cerr << "runReceive() unknown exception\n";
        disconnect();
    }
}

// This function is run in its own thread. 
// Responsible for transmitting messages from the send queue.
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

        // Do checks before sending
        auto expect = expectedPayloadSize(message.messageID);
        if (!expect.has_value()) {
            std::cerr << "[CLIENT] REFUSE to send id=" << int(message.messageID)
                    << " (" << msgName(message.messageID) << "): not allowed on wire\n";
            continue; // drop it
        }
        if (message.payload.size() != expect.value()) {
            std::cerr << "[CLIENT] BAD PAYLOAD for id=" << int(message.messageID)
                    << " (" << msgName(message.messageID) << "): len=" << message.payload.size()
                    << " expected=" << expect.value() << " — dropping & resetting\n";
            disconnect(); // fail fast: prevent corrupting the stream
            return;
        }

        // Debug output
        // std::cout << "Sent header for message ID " << static_cast<int>(header.messageID) << " with payload length " << header.payloadLength << std::endl;
        // std::cout << "Payload: ";
        // for (auto b : message.payload)
        //     std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b) << ' ';
        // std::cout << std::dec << std::endl;

        MessageHeader header;
        header.messageID = message.messageID;
        header.payloadLength = message.payload.size();

        // Send header
        if (!client.transmitAll(&header, sizeof(header))) {
            // Detected disconnect or error
            onServerDisconnect();
            return;
        }

        // Send payload
        if (!client.transmitAll(message.payload.data(), message.payload.size())) {
            // Detected disconnect or error
            onServerDisconnect();
            return;
        }
    }
}

// This function is run in its own thread.
// Responsible for regular updates such as sending ping messages.
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
            Ping ping;
            ping.clientSendTimeNs = getCurrentTimeNs();

            MessageHeader header;
            header.messageID = MessageID::Ping;
            header.payloadLength = sizeof(ping);
            Message pingMsg = makeMessageFrom(ping);
            sendMsg(std::move(pingMsg));

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
    if (client.receiveAll(&header, sizeof(header)) <= 0) return false;
    if (header.messageID != MessageID::ServerInit || header.payloadLength != sizeof(ServerInit)) return false;

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

void VehicleClient::onServerDisconnect()
{
    lastConnectionType.store(currConnectionType.load());
    currConnectionType.store(ConnectionType::None);
    connectionState.store(ClientConnectionState::Disconnected);
}

uint64_t VehicleClient::getCurrentTimeNs()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}
