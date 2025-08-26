#pragma once
#include <iostream>
#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int adcAddr        = 1000000;

class ADC
{
public:
    inline int getSteeringFeedback()
    {
        // Sample ADC data for steering feedback
        spi_xfer(piHandle, adcHandle, spi_tx, spi_rx, 3);
        int value = ((spi_rx[1] & 0x03) << 8) | spi_rx[2];

        return value;
    }

    bool initialize();
    void cleanup();

    ADC() {}
    ~ADC();
private:
    bool initialized = false;
    int piHandle;
    int adcHandle;
    // SPI Configuration
    char spi_tx[3]     = {1, 128, 0}; // Command to read channel 0 from MCP3008
	char spi_rx[3];                               // Array to hold received SPI data
};