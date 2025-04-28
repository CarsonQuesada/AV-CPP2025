#pragma once
#include <atomic>
#include <thread>

#include "TCPServer.h"
#include "Shared/VehicleCommand.h"
#include "Shared/VehicleFeedback.h"
#include "ThreadSafeQueue.h"

class VehicleServer
{
public:
    VehicleServer() {}
    ~VehicleServer() {}

    bool begin();
    inline std::optional<VehicleCommand> tryRecvCmd() { return commandQueue.tryPop(); }
    inline VehicleCommand waitRecvCmd() { return commandQueue.waitAndPop(); }
    inline void sendFb(VehicleFeedback fb) { feedbackQueue.push(fb); }
    void stop();

    // Threads to run in main
    void runReceive();
    void runTransmit();
    void runRegularUpdate();
private:
    TCPServer server;
    ThreadSafeQueue<VehicleCommand> commandQueue;
	ThreadSafeQueue<VehicleFeedback> feedbackQueue;

    std::atomic<bool> stopFlag{false};
};