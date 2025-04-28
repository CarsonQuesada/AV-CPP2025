#include "VehicleServer.h"

#include <chrono>

#include "../VehicleSys.h"

bool VehicleServer::begin()
{
    stopFlag.store(false);
    return server.waitForConnection();
}

void VehicleServer::stop()
{
    stopFlag.store(true);
    server.disconnect();
}

void VehicleServer::runReceive()
{
    VehicleCommand command;
    int status;


    while (!stopFlag.load()) 
    {
        status = server.receiveAll(&command, sizeof(VehicleCommand));
        if (status == 0) {
            // Byte read limit excceded
            command.commandID = VehicleCommandID::Invalid;
        } else if (status < 0) {
            // Client disconnected from server
            command.commandID = VehicleCommandID::Disconnected;
            commandQueue.push(command);
            std::cout << "Disconnect occurred. Trying to Reconnect..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            server.handleReconnect();
            continue;
        }
        
        if (command.commandID != VehicleCommandID::Invalid) {
            if (VehicleSys::getInstance().isAutopilotActive() && command.commandID == VehicleCommandID::Drive) {
                // Only forward non-zero drive commands when autopilot is active
                if (command.drive.speed != 0 || command.drive.brake != 0 || command.drive.steer != 0) {
                    VehicleCommand toggleAuto;
                    toggleAuto.commandID = VehicleCommandID::Autopilot;
                    toggleAuto.autopilot.autopilotCmd = AutopilotCommandID::Stop;
                    commandQueue.push(toggleAuto);  // Signal stop autopilot
                    commandQueue.push(command);     // Send drive command
                }
            } else {
                // Forward all other commands or if autopilot is off
                commandQueue.push(command);
            }
        }
    }
}

void VehicleServer::runTransmit()
{
    VehicleFeedback feedback;
    bool status;

    while (!stopFlag.load())
    {
        feedback = feedbackQueue.waitAndPop();

        size_t size = getFeedbackSize(feedback);
        if (size == 0)
        {
            std::cerr << "Invalid or unsupported FeedbackID. Skipping." << std::endl;
            continue;
        }

        status = server.transmitAll(&feedback, size);
        if (!status)
            server.handleReconnect();
    }
}

void VehicleServer::runRegularUpdate()
{
    const std::chrono::milliseconds waitInterval(50);
    const std::chrono::milliseconds pingInterval(3000); // Ping every 3000ms
    const std::chrono::milliseconds statusUpdateInterval(100); // Update status every 100ms

    auto prevPing = std::chrono::steady_clock::now();
    auto prevUpdate = std::chrono::steady_clock::now();
    bool status;

    while (!stopFlag.load()) {
        auto now = std::chrono::steady_clock::now();

        // Ping command
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - prevPing) >= pingInterval) {
            PingVFeedback pingFeedback;
            status = server.transmitAll(&pingFeedback, sizeof(pingFeedback));
            if (!status)
                server.handleReconnect();
            prevPing = now;
        }

        // Update status 
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - prevUpdate) >= statusUpdateInterval) {
            StatusVFeedback statusFeedback;
            statusFeedback.autopilotActive = VehicleSys::getInstance().isAutopilotActive();
            statusFeedback.braking = VehicleSys::getInstance().isBraking();
            statusFeedback.gear = VehicleSys::getInstance().getGear();
            statusFeedback.headlightsOn = VehicleSys::getInstance().isHeadlightsOn();
            statusFeedback.leftSigOn = VehicleSys::getInstance().isLeftSigOn();
            statusFeedback.rightSigOn = VehicleSys::getInstance().isRightSigOn();
            statusFeedback.speed = 0; // Not implemented yet
            status = server.transmitAll(&statusFeedback, sizeof(statusFeedback));
            if (!status)
                server.handleReconnect();
            prevUpdate = now;
        }

        std::this_thread::sleep_for(waitInterval);
    }
}
