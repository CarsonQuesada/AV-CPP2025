#pragma once
#include <iostream>

#include "Pigpio.h"

constexpr int adcAddr        = 1000000;

// Singleton class for GPS
class ADC
{
public:
    static ADC& get_instance() {
        static ADC instance; 
        return instance;
    }
    inline int get_steering_feedback() {
        // Sample ADC data for steering feedback
        spi_xfer(piHandle, adcHandle, spi_tx, spi_rx, 3);
        return (spi_rx[1] << 8) | (spi_rx[2] & 0x3FF);
    }
    bool initialize();
    void cleanup();
private:
    bool initialized = false;
    int piHandle;
    int adcHandle;
    // SPI Configuration
	char spi_rx[3];                               // Array to hold received SPI data
    char spi_tx[3]     = {1, 128, 0};             // Command to read channel 0 from MCP3008

    ADC() {}                              // Private constructor to make sure there is only one instance
    ADC(const ADC&) = delete;             // Prevent copy construction
    ADC& operator=(const ADC&) = delete;  // Prevent assignment
    ~ADC();
};