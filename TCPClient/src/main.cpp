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
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VehicleState.h"
#include "VehicleController.h"
#include "Communication/VehicleClient.h"
#include "UI/UI.h"

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

// Error callback for GLFW
void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
	// Set GLFW error callback
    glfwSetErrorCallback(glfw_error_callback);

	// Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

	// Setup OpenGL context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui + OpenGL + GLFW", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

	// Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

	// Scope for lifetime control
	{
		VehicleClient client;
		VehicleController controller(window);
		UI ui(window, client, controller);

		std::optional<Message> received;

		// Main Loop
		while (!glfwWindowShouldClose(window)) {
			// Updates that should be done first
			glfwPollEvents();
			ui.onUpdate();

			// User Input
			controller.pollKeyboardInput();
			std::vector<Message> msgs = controller.generateCommands(
				client.getConnectionState() == ClientConnectionState::Connected, 
				(VehicleState::getInstance().stateMode.mode == 3)
			);

			for (const auto& msg : msgs) {
					client.sendMsg(msg);
			}

			// Render UI
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			ui.render();

			glfwSwapBuffers(window);

			// Handle Feedback
			while(received = client.tryRecvMsg()) {
				Message recievedMsg = *received;
				switch (recievedMsg.messageID)
				{
					case MessageID::GeneralStatus:
						VehicleState::getInstance().genStatus = extractPayload<GeneralStatus>(recievedMsg);
						break;
					case MessageID::LightsStatus:
						VehicleState::getInstance().lightStatus = extractPayload<LightsStatus>(recievedMsg);
						break;
					case MessageID::DriveStatus:
						VehicleState::getInstance().driveStatus = extractPayload<DriveStatus>(recievedMsg);
						break;
					case MessageID::StateMode:
						VehicleState::getInstance().stateMode = extractPayload<StateMode>(recievedMsg);
						break;
					case MessageID::Ping:
						// Ping is handled by VehicleServer currently
						break;
					case MessageID::Invalid:
						break;
					case MessageID::Disconnected:
						break;
				}
			}
		}
	}

	glfwDestroyWindow(window);
    glfwTerminate();
	system("pause");	// Keeps console window open after program closes (for debugging)
	return 0;
}