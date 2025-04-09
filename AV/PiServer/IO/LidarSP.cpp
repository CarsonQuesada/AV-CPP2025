#include "LidarSP.h"


int LidarSP::run_lidar()
{
    // --- Initialize Variables for Lidar Data ---
	uint16_t distance;	// Variable to hold the calculated Lidar distance
    char data[2];  		// Buffer to store the 2 bytes of raw distance data

    // --- Read Data from Lidar Sensor ---
    int bytesRead = i2c_read_device(piHandle, lidarSPHandle, data, 2);
    if (bytesRead == 2) {
        // Parse the distance from the 2-byte data buffer
        distance = (data[1] << 8) | data[0]; // Combine the two bytes into a 16-bit distance value
        std::cout << "Lidar Distance: " << distance << " cm" << std::endl;
    }
    else {
        // --- Handle Lidar Read Errors ---
        // Log an error message and attempt to reinitialize the Lidar I²C handle
        std::cout << "Lidar failed. Reinitializing I2C handle...\n";
        i2c_close(piHandle, lidarSPHandle); // Close the existing Lidar handle
        lidarSPHandle = i2c_open(piHandle, 1, lidarSPAddr, 0); // Reopen the I²C handle for the Lidar
        return -1; // Return -1 to indicate an error occurred
    }

    return distance;  // Return the calculated Lidar distance (in cm)
}

bool LidarSP::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::get_instance().get_handle();
        lidarSPHandle = i2c_open(piHandle, 1, lidarSPAddr, 0);

        if (lidarSPHandle < 0) {
            printf("[!] Failed to init single point lidar!\n");
        } else {
            printf("> Single point lidar subsystem \t\tINIT OK\n");
            initialized = true;
        }
    } else {
        printf("lidar (Single Point) already initialized\n");
    }
    return initialized;
}

void LidarSP::cleanup()
{
    if (initialized) {
        initialized = false;
        i2c_close(piHandle, lidarSPHandle);
    }
    else
        printf("WARNING: Tried closing lidar (Single Point) I2C connection without initialization\n");
}

LidarSP::~LidarSP()
{
    if (initialized)
        i2c_close(piHandle, lidarSPHandle);
}
