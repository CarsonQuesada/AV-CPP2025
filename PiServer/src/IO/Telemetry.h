#pragma once
#include <iostream>
#include <pigpiod_if2.h>

#include "Pigpio.h"
#include "Shared/Message.h"

constexpr int telemetryAddr        = 0x15;                    // I2C address for GPS subsystem

// Singleton class for GPS
class Telemetry
{
public:
    TelemetryData getData();

    bool initialize();
    void cleanup();

    Telemetry() {} 
    ~Telemetry();
private:
    bool initialized = false;
    int piHandle;
    int telemetryHandle;
};