#pragma once
#include <atomic>

#include "TCPClient.h"
#include "Shared/VehicleCommand.h"
#include "Shared/VehicleFeedback.h"
#include "ThreadSafeQueue.h"

class VehicleClient
{
public:
    VehicleClient() {}
    ~VehicleClient() {}

    bool begin();
    inline std::optional<VehicleFeedback> tryRecvFb() { return feedbackQueue.tryPop(); }
    inline VehicleFeedback waitRecvFb() { return feedbackQueue.waitAndPop(); }
    inline void sendCmd(VehicleCommand fb) { commandQueue.push(fb); }
    void stop();

    // Threads to run in main
    void runReceive();
    void runTransmit();
    void runRegularUpdate();
private:
    TCPClient client;
    ThreadSafeQueue<VehicleCommand> commandQueue;
	ThreadSafeQueue<VehicleFeedback> feedbackQueue;

    std::atomic<bool> stopFlag;
};