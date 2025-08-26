#include "VehicleServer.h"

#include <chrono>

#include "../VehicleSys.h"
#include "Shared/TCPKeys.h"


VehicleServer::VehicleServer() {
    shutdownFlag.store(false);
    supervisorThread = std::thread([this]() { runSupervisor(); });
}

VehicleServer::~VehicleServer() {
    shutdownFlag.store(true);
    if (supervisorThread.joinable()) supervisorThread.join();
    disconnect();
}

bool VehicleServer::start() {
    std::atomic_bool cancelFlag(false);
    start(cancelFlag);
}

bool VehicleServer::start(std::atomic_bool& cancelFlag) {
    if (connectionState.exchange(ServerConnectionState::Listening) == ServerConnectionState::Disconnected) {
        std::cout << "Begin connecting" << std::endl;
        VehicleSys::getInstance().setConnectStatusLED(connectionState.load());
        reconnectRequested.store(false);
        if (server.waitForConnection(cancelFlag, PORT)) {
            connectionState.store(ServerConnectionState::Connected);
            stopFlag.store(false);
            if (!performHandshake()) {
                std::cout << "Failed handshake, closing connection." << std::endl;
                disconnect();
                return false;
            }
            std::cout << "STARTING WORKER THREADS" << std::endl;
            startWorkerThreads();
        } else {
            connectionState.store(ServerConnectionState::Disconnected);
        }
        return true;
    }
    return false;
}

void VehicleServer::disconnect() {
    std::cout << "Disconnect called" << std::endl;
    stopFlag.store(true);
    signalDisconnect();
    VehicleSys::getInstance().setConnectStatusLED(connectionState.load());
 
    stopWorkerThreads();
    server.disconnect();

    std::cout << "Draining queues" << std::endl;
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

void VehicleServer::runSupervisor() {
    while (!shutdownFlag.load()) {
        if (reconnectRequested.load()) {
            std::cout << "Reconnect Request Detected" << std::endl;
            stopWorkerThreads();  // stop safely
            VehicleSys::getInstance().setConnectStatusLED(connectionState.load());
            if (!start()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                reconnectRequested.store(false);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void VehicleServer::startWorkerThreads() {
    std::cout << "Starting worker threads" << std::endl;
    receiveThread = std::thread([this]() { runReceive(); });
    transmitThread = std::thread([this]() { runTransmit(); });
    updateThread = std::thread([this]() { runRegularUpdate(); });
}

void VehicleServer::stopWorkerThreads() {
    std::cout << "Stopping worker threads" << std::endl;
    if (receiveThread.joinable()) receiveThread.join();
    if (transmitThread.joinable()) transmitThread.join();
    if (updateThread.joinable())  updateThread.join();
}

void VehicleServer::runReceive() {
    try {
        std::cout << "runRecieve() started." << std::endl;

        while (!stopFlag.load()) {
            MessageHeader header;
            Message message;

            if (!server.receiveAll(&header, sizeof(header))) {
                std::cout << "Reconnect requested on header in runReceive()" << std::endl;
                message.messageID = MessageID::Disconnected;
                receiveQueue.push(std::move(message));
                signalDisconnect();
                return;
            }

            message.messageID = header.messageID;
            message.payload.resize(header.payloadLength);
            if (!server.receiveAll(message.payload.data(), header.payloadLength)) {
                std::cout << "Reconnect requested on payload in runReceive()" << std::endl;
                message.messageID = MessageID::Disconnected;
                message.payload.clear();
                receiveQueue.push(std::move(message));
                signalDisconnect();
                return;
            }

            if (message.messageID != MessageID::Invalid) {
                if (message.messageID == MessageID::Ping) {
                    sendMsg(message);   // send ping straight back
                } else if (VehicleSys::getInstance().isAutopilotActive() && message.messageID == MessageID::Drive) {
                    DriveCommand drive = extractPayload<DriveCommand>(message);
                    if (drive.speed != 0 || drive.brake != 0 || drive.steer != 0) {
                        Message stopAuto = { MessageID::StopAutopilot, {} };
                        receiveQueue.push(std::move(stopAuto));
                        receiveQueue.push(std::move(message));
                    }
                } else {
                    receiveQueue.push(std::move(message));
                }
            }
        }
    std::cout << "runReceive() exiting cleanly; stopFlag = true" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "runReceive() exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "runReceive() unknown exception" << std::endl;
    }
    std::cout << "runReceive() has exited." << std::endl;
}

void VehicleServer::runTransmit() {
    try {
        std::cout << "runTransmit() started." << std::endl;

        while (!stopFlag.load() && !reconnectRequested.load()) {
            auto optMsg = sendQueue.tryPop();
            if (!optMsg.has_value()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            const Message& message = optMsg.value();
            MessageHeader header = { static_cast<uint32_t>(message.payload.size()), message.messageID };

            if (!server.transmitAll(&header, sizeof(header)) ||
                !server.transmitAll(message.payload.data(), message.payload.size())) {
                std::cout << "[runTransmit] Reconnect Requested on transmit failure." << std::endl;
                signalDisconnect();
                break;
            }
        }

        std::cout << "runTransmit() exiting cleanly." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "runTransmit() exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "runTransmit() unknown exception" << std::endl;
    }

    std::cout << "runTransmit() has exited." << std::endl;
}

void VehicleServer::runRegularUpdate() {
    std::cout << "runRegularUpdate() started." << std::endl;

    constexpr std::chrono::milliseconds loopDelay(10);              // Controls how often loop runs
    constexpr std::chrono::milliseconds generalStatusInterval(500); // Send general status every 500ms
    constexpr std::chrono::milliseconds telemetryInterval(100);     // Send telemtry status every 100ms
    constexpr std::chrono::milliseconds lightsStatusInterval(100);  // Send lights status every 100ms
    constexpr std::chrono::milliseconds driveStatusInterval(25);   // Send drive status every 25ms

    auto lastGeneralStatusTime = std::chrono::steady_clock::now();
    auto lastTelemetryTime     = lastGeneralStatusTime;
    auto lastLightsStatusTime  = lastGeneralStatusTime;
    auto lastDriveStatusTime   = lastGeneralStatusTime;

    while (!stopFlag.load() && !reconnectRequested.load()) {
        const auto now = std::chrono::steady_clock::now();

        // --- General Status ---
        if (now - lastGeneralStatusTime >= generalStatusInterval) {
            std::cout << "[RegularUpdate] Sending general status..." << std::endl;
            GeneralStatus genStat = VehicleSys::getInstance().getGeneralStatus();
            sendMsg(makeMessageFrom(genStat));

            lastGeneralStatusTime = now;
        }

        // ---- Telemetry Data ----
        if (now - lastTelemetryTime >= telemetryInterval) {
            TelemetryData telemetry = VehicleSys::getInstance().getTelemetryData();
            sendMsg(makeMessageFrom(telemetry));

            lastTelemetryTime = now;
        }

        // --- Lights Status (periodic and reactive) ---
        if (now - lastLightsStatusTime >= lightsStatusInterval) {
            sendMsg(makeMessageFrom(VehicleSys::getInstance().getLightsStatus()));
            VehicleSys::getInstance().consumeLightsStatusDirty(); // clear flag (even if not set)
            lastLightsStatusTime = now;
        } else if (VehicleSys::getInstance().consumeLightsStatusDirty()) {
            // Reactively send updated lights info
            sendMsg(makeMessageFrom(VehicleSys::getInstance().getLightsStatus()));
        }

        // --- Drive Status (periodic and reactive) ---
        if (now - lastDriveStatusTime >= driveStatusInterval) {
            DriveStatus driveStatus = VehicleSys::getInstance().getDriveStatus();
            sendMsg(makeMessageFrom(driveStatus));
            lastDriveStatusTime = now;
        }

        std::this_thread::sleep_for(loopDelay);
    }

    std::cout << "runRegularUpdate() exiting cleanly." << std::endl;
}

bool VehicleServer::performHandshake()
{
    // 1. Receive ClientInit
    MessageHeader header;
    if (server.receiveAll(&header, sizeof(header)) <= 0) {
        std::cout << "failed to read header" << std::endl;
        return false;
    }
    if (header.messageID != MessageID::ClientInit || header.payloadLength != sizeof(ClientInit)) {
        std::cout << "Wrong message type: Type - " << static_cast<int>(header.messageID) << std::endl;
        return false;
    }

    std::vector<uint8_t> payload(header.payloadLength);
    if (server.receiveAll(payload.data(), payload.size()) <= 0) {
        std::cout << "Failed to read payload." << std::endl;
        return false;
    }

    Message msg = { header.messageID, std::move(payload) };
    ClientInit clientInit = extractPayload<ClientInit>(msg);

    // 2. Respond with ServerInit
    ServerInit response = {};
    response.generalStatus = VehicleSys::getInstance().getGeneralStatus();
    response.lightsStatus = VehicleSys::getInstance().getLightsStatus();
    response.autopilotStatus = VehicleSys::getInstance().getAutopilotStatus();

    MessageHeader responseHeader;
    responseHeader.messageID = MessageID::ServerInit;
    responseHeader.payloadLength = sizeof(ServerInit);

    Message reply = makeMessageFrom(response);
    if (!server.transmitAll(&responseHeader, sizeof(responseHeader))) {
        std::cout << "Failed to transmit header of server init." << std::endl;
        return false;
    }
    if (!server.transmitAll(reply.payload.data(), reply.payload.size())) {
        std::cout << "Failed to transmit payload of server init." << std::endl;
        return false;
    }

    return true;
}

void VehicleServer::signalDisconnect() 
{
    connectionState.store(ServerConnectionState::Disconnected);
    reconnectRequested.store(true);
}
