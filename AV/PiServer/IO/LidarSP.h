#pragma once
#include <iostream>

//#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int lidarSPAddr    = 0x20;                  // I2C address for Lidar subsystem

// Singleton class for Lidar (Single Point)
class LidarSP
{
public:
    static LidarSP& get_instance() {
        static LidarSP instance; 
        return instance;
    }
    int run_lidar();                    // Returns retrieved distance (in cm)
    bool initialize();
    void cleanup();
private:
    bool initialized = false;
    int piHandle;
    int lidarSPHandle;

    LidarSP() {}                                  // Private constructor to make sure there is only one instance
    LidarSP(const LidarSP&) = delete;             // Prevent copy construction
    LidarSP& operator=(const LidarSP&) = delete;  // Prevent assignment
    ~LidarSP();
};