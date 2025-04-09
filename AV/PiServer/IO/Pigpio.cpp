#include "Pigpio.h"

bool Pigpio::initialize()
{
    if (!initialized)
    {
        piHandle = pigpio_start(NULL, NULL);
	    if (piHandle < 0) {
		    printf("[!] Failed to connect to pigpio daemon! Attempted to connect to localhost:8888\n");
	    } else {
            printf("> pigpio on localhost:8888 \tINIT OK\n");
            initialized = true;
	    }
    }
    return initialized;
}

void Pigpio::cleanup()
{
    if (initialized) {
        initialized = false;
        pigpio_stop(piHandle);
    }
    else
        printf("WARNING: Tried closing Pigpio I2C connection without initialization\n");
}

Pigpio::~Pigpio()
{
    if (initialized)
        pigpio_stop(piHandle);
}
