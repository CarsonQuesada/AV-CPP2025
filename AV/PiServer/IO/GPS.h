#pragma once
#include <iostream>

//#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int gpsAddr        = 0x15;                    // I2C address for GPS subsystem

struct GPSPoint
{
    double lon, lat, heading;
    inline void display();
};

// Singleton class for GPS
class GPS
{
public:
    static GPS& get_instance() {
        static GPS instance; 
        return instance;    
    }
    GPSPoint get_location();
    bool initialize();
    void cleanup();
private:
    bool initialized = false;
    int piHandle;
    int gpsHandle;
    char buffer[24];

    GPS() {}                              // Private constructor to make sure there is only one instance
    GPS(const GPS&) = delete;             // Prevent copy construction
    GPS& operator=(const GPS&) = delete;  // Prevent assignment
    ~GPS();
};