#pragma once
#include <iostream>

#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int gpsAddr        = 0x15;                    // I2C address for GPS subsystem

struct GPSPoint
{
    double lon, lat, heading;
    void display();
};

// Singleton class for GPS
class GPS
{
public:
    GPSPoint getLocation();

    bool initialize();
    void cleanup();

    GPS() {} 
    ~GPS();
private:
    bool initialized = false;
    int piHandle;
    int gpsHandle;
};