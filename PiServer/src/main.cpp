// Basic C++ Libraries
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>

#include <cstdlib>
#include <signal.h>

#include "Communication/VehicleServer.h"
#include "Communication/Autopilot.h"
#include "VehicleSys.h"

// Signal handler for clean shutdown
void signal_callback_handler(int signum);

int main() 
{
	// Setup signal handler for graceful shutdown
	signal(SIGINT, signal_callback_handler);

	VehicleServer server;
	Autopilot autopilot;
	VehicleSys& vehicle = VehicleSys::getInstance();

	

	// Initialize vehicle system's IO devices
	if (!vehicle.initIO()) {
		std::cout << "Failed to initialize one or more IO devices. Exiting program." << std::endl;
		return -1;
	}

	// Initialize autopilot's IO devices
	if (!autopilot.initIO()) {
		std::cout << "Failed to initialize one or more IO devices. Exiting program." << std::endl;
		return -1;
	}

	// Begin connection with TCP client
	if (!server.begin()) {
		std::cout << "Failed to establish connection with a client. Exiting program." << std::endl;
		return -1;
	}

	std::thread recvThread(&VehicleServer::runReceive, &server);
	std::thread sendThread(&VehicleServer::runTransmit, &server);
	std::thread clientUpdateThread(&VehicleServer::runRegularUpdate, &server);
	
	std::thread sendAutoThread(&Autopilot::runProcessCommand, &autopilot);
	std::thread recvAutoThread(&Autopilot::runAutopilot, &autopilot);


	// Main control loop
	while (true) {
		// Receive and process a command from user
		auto command = server.tryRecvCmd();
		if (command) {
			switch ((*command).commandID)
			{
				case VehicleCommandID::Disconnected:
					vehicle.handleDisconnect();
					if (vehicle.isAutopilotActive()) {
						autopilot.signalStop();
						vehicle.setAutopilotActive(false);
					}
					break;
				case VehicleCommandID::Drive:
					vehicle.handleDriveInput((*command).drive);
					break;
				case VehicleCommandID::MoveCamera:
					vehicle.handleCameraInput((*command).camera);
					break;
				case VehicleCommandID::SetMaxSpeed:
					vehicle.setMaxSpeed((*command).setMaxSpeed);
					break;
				case VehicleCommandID::ToggleLights:
					vehicle.handleLightsInput((*command).lights);
					break;
				case VehicleCommandID::Autopilot:
					// Forward command to 
					autopilot.forwardCommand((*command).autopilot);
					// Check if setting autopilot active state and set accordingly
					if ((*command).autopilot.autopilotCmd == AutopilotCommandID::Start)
						vehicle.setAutopilotActive(true);
					else if ((*command).autopilot.autopilotCmd == AutopilotCommandID::Stop)
						vehicle.setAutopilotActive(false);
					
				case VehicleCommandID::Ping:
					break;
				case VehicleCommandID::Invalid:
					break;	// Should never happen
				default:
					std::cout << "Unknown command received" << std::endl;
			}
		}

		if (vehicle.isAutopilotActive()) {
			// Right now autopilot only produces drive commands
			auto feedback = autopilot.tryRecvCmd();
			if (feedback) {
				if ((*feedback).feedbackID == AutopilotFeedbackID::Drive)
					vehicle.handleDriveInput((*feedback).drive);
				else
					std::cout << "Only handling drive commands for autopilot" << std::endl;
			}
		}
		
		// Loop delay to prevent CPU overload
		printf("\n");
		usleep(10*1000);	// Delay for 50ms
    }



    return 0;
}

// Signal handler for clean shutdown
void signal_callback_handler(int signum) {
	std::cout << "CTRL+C caught! Terminating..." << signum << std::endl;

	// Exit the program gracefully with the signal code
	exit(signum);
}