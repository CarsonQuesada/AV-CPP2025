#include "VehicleClient.h"

#include <thread>

bool VehicleClient::begin()
{
    while (!client.tryConnect()) {
        // Timeout reached
        std::cout << "Press enter to try again" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    stopFlag.store(false);
    return true;
}

void VehicleClient::stop()
{
    stopFlag.store(true);
    client.disconnect();
}

void VehicleClient::runReceive()
{
    VehicleFeedback feedback;
    int status;

    while (!stopFlag.load()) 
    {
        status = client.receiveAll(&feedback, sizeof(VehicleFeedback));
        if (status == 0) {
            // Byte read limit excceded
            feedback.feedbackID = VehicleFeedbackID::Invalid;
        } else if (status < 0) {
            // Client disconnected from server
            feedback.feedbackID = VehicleFeedbackID::Disconnected;
            feedbackQueue.push(feedback);
            client.handleReconnect();
            continue;
        }
        
        if (feedback.feedbackID != VehicleFeedbackID::Invalid) {
            feedbackQueue.push(feedback);
        }
    }
}

void VehicleClient::runTransmit()
{
    VehicleCommand command;
    bool status;

    while (!stopFlag.load())
    {
        command = commandQueue.waitAndPop();

        size_t size = getCommandSize(command);
        if (size == 0)
        {
            std::cerr << "Invalid or unsupported CommandID. Skipping." << std::endl;
            continue;
        }

        status = client.transmitAll(&command, size);
        if (!status)
            client.handleReconnect();
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
            PingVCommand pingCommand;
            pingCommand.commandID = VehicleCommandID::Ping;

            status = client.transmitAll(&pingCommand, sizeof(PingVCommand));
            if (!status)
                client.handleReconnect();
        }
    }
}
