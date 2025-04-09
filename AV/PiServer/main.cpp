// Basic C++ Libraries
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
 
// Libraries for TCP Configuration
// #include <sys/types.h>
// #include <sys/socket.h>
#include <unistd.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <errno.h>

#include <pigpiod_if2.h>
#include <cstdlib>
#include <signal.h>

#include "TCPServer/TCPServer.h"
#include "Autopilot/Autopilot.h"
#include "VehicleSys.h"
#include "Debug/Logger.h"

int main() 
{
	bool prevToggleAV = false;

	UserInput userInput;
	AutopilotOutput avOutput;

	TCPServer tcpClient;
	Autopilot autopilot;
	VehicleSys vehicle;

	// Initialize hardware subsystems
	if(!vehicle.init_io())
		return -1;

	// User and network configuration
	{
		int maxAccel = tcpClient.get_user_configurations();
		vehicle.set_max_accel(maxAccel);
	}

	// Call TCP server setup function
	tcpClient.setup_TCP_server();

	// Main control loop
	while (true) {
		// --- RECEIVE AND PARSE SOCKET DATA --- ////////////////////////////////////////
		// Attempt to receive data from the TCP socket in non-blocking mode
		if (!tcpClient.retrieve_client_control(userInput)) {
			std::cerr << "There was a connection issue. Waiting for reconnection..." << std::endl;
			vehicle.enable_vehicle(false); // Disable vehicle for safety
			tcpClient.setup_TCP_server(); // Reattempt connection
			vehicle.enable_vehicle(true); // Enable vehicle again
			continue;
		}
		
		// --- HANDLE USER INPUT --- ////////////////////////////////////////////////////
		// Handle other input first because it handles the toggling of autopilot
		if (prevToggleAV != userInput.toggleAV) {
			if (userInput.toggleAV) {
				autopilot.toggle_autopilot();
			}

			vehicle.enable_av_led(userInput.toggleAV);
			prevToggleAV = userInput.toggleAV;
		}

		// Handle vehicle movement
		if (autopilot.is_active()) {
			// Get driving instructions from autopilot and use it
			std::cout << "Running Autopilot!" << std::endl;
			avOutput = autopilot.run_autopilot();
			vehicle.steer(avOutput.steerValue);						
			vehicle.brake(avOutput.brakeValue); 						
			vehicle.accelerate(avOutput.accelValue, avOutput.gear);
		} else {
			// Use user input to control vehicle
			std::cout << "Acceleration: " << userInput.accelValue << std::endl;
			vehicle.steer(userInput.steerValue);						
			vehicle.brake(userInput.brakeValue); 						
			vehicle.accelerate(userInput.accelValue, userInput.gear);
		}

		// Handle Camera movement
		vehicle.handle_camera_input(userInput.cameraCommand);

		// Handle misc input
		vehicle.handle_other_input(userInput.otherInput);

		// Loop delay to prevent CPU overload
		printf("\n");
		usleep(50*1000);	// Delay for 50ms
    }
    return 0;
}