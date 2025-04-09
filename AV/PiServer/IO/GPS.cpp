#include "GPS.h"

#include <cstring>

void GPSPoint::display()
{
    printf("Latitude: %.8f, Longitude: %.8f, Course: %.2f\n", lat, lon, heading);
}

GPSPoint GPS::get_location()
{
    GPSPoint currentLocation;
    // --- Read GPS Data from I2C ---
	// Attempt to read 24 bytes from the GPS I2C device
	int bytesRead = i2c_read_device(piHandle, gpsHandle, buffer, sizeof(buffer));

	if (bytesRead == sizeof(buffer)) {
        std::memcpy(&currentLocation.lon, &buffer[0], 8);
        std::memcpy(&currentLocation.lat, &buffer[8], 8);
        std::memcpy(&currentLocation.heading, &buffer[16], 8);
        currentLocation.heading /= 100.0; // Scale heading back to degrees
        // currentLocation.display();
    } else {
		// --- Handle Read Errors ---
        // If the number of bytes read is incorrect, log an error
        fprintf(stderr, "Error: Expected 24 bytes, but got %d\n", bytesRead);

		// Reinitialize the GPS I2C handle to attempt recovery
		std::cout << "GPS failed. Reinitializing I2C handle...\n";
		i2c_close(piHandle, gpsAddr);
		gpsHandle = i2c_open(piHandle, 1, gpsAddr, 0);
    }
    return currentLocation;
}

bool GPS::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::get_instance().get_handle();
        gpsHandle = i2c_open(piHandle, 1, gpsAddr, 0);

        if (gpsHandle < 0) {
            printf("[!] Failed to init GPS (Telementary)!\n");
        } else {
            printf("> GPS (Telementary) subsystem \tINIT OK\n");
            initialized = true;
        }
    } else {
        printf("GPS already initialized\n");
    }
    return initialized;
}

void GPS::cleanup()
{
    if (initialized)
    {
        initialized = false;
        i2c_close(piHandle, gpsHandle);
    }
    else
        printf("WARNING: Tried closing GPS I2C connection without initialization\n");
}

GPS::~GPS()
{
    if (initialized)
        i2c_close(piHandle, gpsHandle);
}
