#pragma once
#include <vector>
#include <queue>
#include <atomic>
#include <thread>

#include "IO/GPS.h"
#include "IO/LidarSP.h"
#include "Shared/AutopilotFeedback.h"
#include "Shared/AutopilotCommand.h"
#include "ThreadSafeQueue.h"

constexpr int minStopDist = 50;
constexpr float accelPropConst = 1.0 / 4.5;
constexpr float brakePropConst = 10.0 / 3.0;
constexpr double destReachedThresh = 0.00005;

class Autopilot
{
public:
    void runAutopilot();
    void runProcessCommand();
    void runReceive();  // Unimplemented
    void runTransmit(); // Unimplemented

    void begin();
    inline std::optional<AutopilotFeedback> tryRecvCmd() { return feedbackQueue.tryPop(); }
    inline AutopilotFeedback waitRecvCmd() { return feedbackQueue.waitAndPop(); }
    void forwardCommand(AutopilotVCommand cmd);
    void signalStop();
    void end(); // TEMPORARY: Should be stop but 

    bool initIO();
    void shutdown();

    Autopilot() {}
    ~Autopilot() {}
private:
    ThreadSafeQueue<AutopilotFeedback> feedbackQueue;
    ThreadSafeQueue<AutopilotCommand> commandQueue;
    std::queue<GPSPoint> destinations;

    std::atomic<bool> stopFlag{false};
    std::atomic<bool> run{false};

    // IO instances
    GPS gps;
    LidarSP lidar;

    void start();
    void stop();
    void findDestinations();
    void clearDestinations();
};