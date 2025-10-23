#pragma once

#include <iostream>
#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int lidarSPAddr    = 0x20;    // I2C address for Lidar subsystem

class LidarSP
{
public:
    int runLidar(); // Returns retrieved distance (in cm)
    
    bool initialize();
    void cleanup();

    LidarSP() {} 
    ~LidarSP();
private:
    bool initialized = false;
    int piHandle;
    int lidarSPHandle;
};