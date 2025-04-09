#pragma once
#include <vector>
#include <queue>

#include "IO/GPS.h"
#include "IO/LidarSP.h"
#include "IO/Drive.h"
#include "IO/ADC.h"

constexpr int minStopDist = 50;
constexpr float accelPropConst = 1.0 / 4.5;
constexpr float brakePropConst = 10.0 / 3.0;
constexpr double destReachedThresh = 0.00005;

struct AutopilotOutput 
{
    Gear gear = Gear::Forward;  // TEMPORARY: always goes forward
    int accelValue; // Value from 0-100
    int brakeValue; // Value from 0-100
    int steerValue; // Value from 0-100
};

class Autopilot
{
public:
    Autopilot();

    void toggle_autopilot();
    inline bool is_active() { return active; };
    AutopilotOutput run_autopilot();
private:
    bool active = false;

    std::queue<GPSPoint> destinations;

    // IO instances
    GPS& gps;
    LidarSP& lidar;
    Drive& drive;
    ADC& adc;
    Lighting& lighting;

    void start();
    void end();
    void find_destinations();
    void clear_destinations();
};