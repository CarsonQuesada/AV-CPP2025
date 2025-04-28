#include <WS2tcpip.h>
#include <string>
#include <windows.h>
#include <basetsd.h>
#include <dinput.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <thread>

#include "Communication/VehicleClient.h"
#include "VehicleControl.h"

/*
Arrow left = left
Arrow right = right
Arrow up = forward
Arrow down = reverse
Space = brake
Q = camera left
W = camera center
E = camera right

Z = signal left
X = signal right
H = headlights
T = cv control
C = toggle cruise control
V = toggle autopilot
*/

const int accelVal = 100;

int main() {
	VehicleClient client;
	VehicleControl controller;

	std::optional<VehicleFeedback> feedback;
	std::optional<VehicleCommand> command;

	if (!client.begin()) {
		std::cout << "[!!] FAILED TCP SETUP\n";
		return -1;
	}

	std::thread recvThread(&VehicleClient::runReceive, &client);
	std::thread sendThread(&VehicleClient::runTransmit, &client);

	while (true) {
		command = controller.genDriveCommand();
		if (command)
			client.sendCmd(*command);
			
		command = controller.genCameraCommand();
		if (command)
			client.sendCmd(*command);

		command = controller.genLightsCommand();
		if (command)
			client.sendCmd(*command);

		command = controller.genAutopilotCommand();
		if (command)
			client.sendCmd(*command);

		if (controller.isDown(setMaxSpeedKey)) {
			command = controller.genStopCommand();
			if (command)
				client.sendCmd(*command);
			command = controller.genMaxSpeedCommand();
			if (command)
				client.sendCmd(*command);
		}

		while(feedback = client.tryRecvFb()) {
			switch ((*feedback).feedbackID)
			{
				case VehicleFeedbackID::BatteryInfo:
					break;
				case VehicleFeedbackID::VehicleStatus:
					
					break;
				case VehicleFeedbackID::Ping:
					break;
				case VehicleFeedbackID::Invalid:
					break;
				case VehicleFeedbackID::Disconnected:
					// Wait until connected again
					break;
			}
		}

		Sleep(50);
	}
}