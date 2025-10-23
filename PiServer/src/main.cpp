// Basic C++ Libraries
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <signal.h>
#include <atomic>

#include "Communication/VehicleServer.h"
#include "Communication/Autopilot.h"
#include "VehicleSys.h"

// Signal handler for clean shutdown
void signal_callback_handler(int signum);
std::atomic_bool shutdownRequested(false);

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
	vehicle.statusUpdate();
	auto lastStatusTime = std::chrono::steady_clock::now();

	// Initialize autopilot's IO devices
	if (!autopilot.initIO()) {
		std::cout << "Failed to initialize one or more IO devices. Exiting program." << std::endl;
		return -1;
	}
	
	// Begin connection with TCP client
	if (!server.start(shutdownRequested)) {
		std::cout << "Failed to establish connection with a client. Exiting program." << std::endl;
		return -1;
	}

	std::thread sendAutoThread(&Autopilot::runProcessCommand, &autopilot);
	std::thread recvAutoThread(&Autopilot::runAutopilot, &autopilot);

	vehicle.enableVehicle();
	// Main control loop
	while (!shutdownRequested) {
		// Receive and process a command from user
		auto msg = server.tryRecvMsg();
		if (msg) {
			Message message = msg.value();
			switch (message.messageID)
			{
				case MessageID::Disconnected:
					vehicle.handleDisconnect();
					if (vehicle.isAutopilotActive()) {
						autopilot.signalStop();
						vehicle.setAutopilotActive(false);
					}
					break;
				case MessageID::Drive:
					vehicle.handleDriveInput(extractPayload<DriveCommand>(message));
					break;
				case MessageID::MoveCamera:
					vehicle.handleCameraInput(extractPayload<CameraCommand>(message));
					break;
				case MessageID::SetMaxSpeed:
					vehicle.setMaxSpeed(extractPayload<SetMaxSpeedCommand>(message));
					break;
				case MessageID::ToggleLights:
					vehicle.handleLightsInput(extractPayload<LightsCommand>(message));
					break;
				case MessageID::StartAutopilot:
					// Forward command to 
					autopilot.sendMsg(message);
					vehicle.setAutopilotActive(true);	// Temporary
					break;
				case MessageID::StopAutopilot:
					autopilot.sendMsg(message);
					vehicle.setAutopilotActive(false);	// Temporary
					break;
				case MessageID::Ping:
					// Should send ping back
					break;
				case MessageID::Invalid:
					break;	// Should never happen
				default:
					std::cout << "Unknown command received" << std::endl;
			}
		}

		if (vehicle.isAutopilotActive()) {
			// Right now autopilot only produces drive commands
			auto msg = autopilot.tryRecvMsg();
			if (msg) {
				Message message = msg.value();
				if (message.messageID == MessageID::Drive)
					vehicle.handleDriveInput(extractPayload<DriveCommand>(message));
				else
					std::cout << "Only handling drive commands for autopilot" << std::endl;
			}
		}

		// Run status update every 1000 ms
		auto now = std::chrono::steady_clock::now();
		if (now - lastStatusTime >= std::chrono::milliseconds(1000)) {
			vehicle.statusUpdate();
			lastStatusTime = now;
		}

		// Loop delay to prevent CPU overload
		printf("\n");
		usleep(50*1000);	// Delay for 50ms
    }

	server.disconnect();
    return 0;
}

// Signal handler for clean shutdown
void signal_callback_handler(int signum) {
	std::cout << "CTRL+C caught! Terminating..." << signum << std::endl;
	shutdownRequested.store(true);
}