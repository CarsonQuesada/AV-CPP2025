#include "ADC.h"

//#include <spidev.h>

bool ADC::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::get_instance().get_handle();
        adcHandle = spi_open(piHandle, 0, adcAddr, 0);

        if (adcHandle < 0) {
            printf("[!] Failed to init ADC!\n");
        } else {
            printf("> ADC \t\t\t\tINIT OK\n");
            initialized = true;
        }
    } else {
        printf("ADC already initialized\n");
    }
    return initialized;
}

void ADC::cleanup()
{
    if (initialized)
    {
        initialized = false;
        spi_close(piHandle, adcHandle);
    }
    else
        printf("WARNING: Tried closing ADC I2C connection without initialization\n");
}

ADC::~ADC()
{
    if (initialized)
        spi_close(piHandle, adcHandle);
}
