#pragma once
#include <vector>
#include <queue>
#include <atomic>
#include <thread>

#include "IO/Telemetry.h"
#include "IO/LidarSP.h"
#include "Shared/Message.h"
#include "ThreadSafeQueue.h"

// Notes:
// Currently does not receive telemetry info from pi server

struct GPSPoint
{
    float lon, lat, heading;
};

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
    inline std::optional<Message> tryRecvMsg() { return receiveQueue.tryPop(); }
    inline Message waitRecvMsg() { return receiveQueue.waitAndPop(); }
    inline void sendMsg(Message msg) { sendQueue.push(msg); }
    void signalStop();
    void end(); // TEMPORARY: Should be stop

    bool initIO();
    void shutdown();

    Autopilot() {}
    ~Autopilot() {}
private:
    GPSPoint currPos;

    ThreadSafeQueue<Message> receiveQueue;
    ThreadSafeQueue<Message> sendQueue;
    std::queue<GPSPoint> destinations;

    std::atomic<bool> stopFlag{false};
    std::atomic<bool> run{false};

    // IO instances
    LidarSP lidar;

    void start();
    void stop();
    void findDestinations();
    void clearDestinations();
};