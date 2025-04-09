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

#pragma comment (lib, "ws2_32.lib")

#include "Shared/UserInputTypes.h"

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

F-000-000-000-0-0
F-%3d-%3d-%3d-%1d-%1d

snprintf(simData, simDataLen, "F-%3d-%3d-%3d-%1d-%1d", newTempSteer, newTempAccel, newTempBraking, tempBtns1, tempBtns2);
*/
using namespace std;

constexpr int txBuffLen = 20;

Gear gear = Gear::Coast;
int steering = 0;
int accel = 0;
int brake = 0;
CameraCommand cameraCommand = CameraCommand::NoInput;
bool toggleAV = false;
OtherInput otherInput = OtherInput::NoInput;

const int accelVal = 100;
char gearChar;

char txBuff[txBuffLen];

void get_network_options(std::string& ipAddr, int& port) {
	int source = 0;
connectionInput:
	cout << "What address are you connecting to? 1 for local, 2 for VPN, 3 for custom: ";
	cin >> source;
	switch (source)
	{
	case 1:
		ipAddr = "192.168.5.132";
		port = 54000;
		break;
	case 2:
		ipAddr = "10.8.0.2";
		port = 54000;
		break;
	case 3:
		cout << "Enter IP: ";
		cin >> ipAddr;
		cout << "\nEnter Port: ";
		cin >> port;
		break;
	default:
		cout << "Invalid input!" << endl;
		goto connectionInput;
	}
}

int main() {
	// Startup WinSock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		printf("Can't Start WinSock %d", wsOk);
		return 0;
	}

	// Type in Ip Address and Port
	std::string ipAddr;
	int port = 0;
	get_network_options(ipAddr, port);
	cout << "Accepted values: IP = " << ipAddr << " Port = " << port << endl;
	system("PAUSE");

	//Create a hint structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	//server.sin_port = htons(10000);
	//inet_pton(AF_INET, "", &server.sin_addr); for use without VPN
	inet_pton(AF_INET, ipAddr.c_str(), &server.sin_addr); // 192.168.5.132 10.8.0.2
	//inet_pton(AF_INET, "::1", &server.sin_addr);

	//Socket Creation
	SOCKET stream_out = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);// SOCK_STREAM is TCP

	while (1) {
		system("CLS");
		// STEERING KEYS
		if (GetKeyState(VK_LEFT) & 0x8000)
			steering = 100;		// left
		else if (GetKeyState(VK_RIGHT) & 0x8000)
			steering = 0;		// right
		else
			steering = 50;		// center

		//	THROTTLE Keys
		if (GetKeyState(VK_DOWN) & 0x8000) {
			gear = Gear::Reverse;
			accel = accelVal;
		} else if (GetKeyState(VK_UP) & 0x8000) {
			gear = Gear::Forward;
			accel = accelVal;
		} else {
			gear = Gear::Coast;
			accel = 0;
		}

		// BRAKE KEYS
		if (GetKeyState(VK_SPACE) & 0x8000)
			brake = 100;
		else
			brake = 0;

		// OTHER CONTROL KEYS
		if (GetKeyState('Q') & 0x8000) // pan camera left
			cameraCommand = CameraCommand::PanCameraLeft;
		else if (GetKeyState('E') & 0x8000) // pan camera right
			cameraCommand = CameraCommand::PanCameraRight;
		else if (GetKeyState('W') & 0x8000) // camera center
			cameraCommand = CameraCommand::CenterCamera;
		else
			cameraCommand = CameraCommand::NoInput;

		toggleAV = (GetKeyState('V') & 0x8000); // autopilot

		if (GetKeyState('X') & 0x8000) // signal right
			otherInput = OtherInput::RightTurnSig;
		else if (GetKeyState('Z') & 0x8000) // signal left
			otherInput = OtherInput::LeftTurnSig;
		else if (GetKeyState('H') & 0x8000) // headlights
			otherInput = OtherInput::Headlights;
		else if (GetKeyState('S') & 0x8000)	// Reset Max Speed
			otherInput = OtherInput::ResetMaxSpeed;
		else
			otherInput = OtherInput::NoInput;

		switch (gear)
		{
			case Gear::Coast:
				gearChar = 'C';
				break;
			case Gear::Forward:
				gearChar = 'F';
				break;
			case Gear::Reverse:
				gearChar = 'R';
				break;
		}

		printf("steering: %d ", steering);
		printf("gear: %c ", gearChar);
		printf("accel: %d ", accel);
		printf("brake: %d ", brake);
		printf("Camera Command: %i\n", static_cast<int>(cameraCommand));
		if (toggleAV)
			printf("Toggle autopilot key is being pressed");
		printf("Other control input: %i\n", static_cast<int>(otherInput));
		
		// String format "%1c-%3d-%3d-%3d-%1d-%1d-%1d", gear, steer, accel, brake, cam, avTog, other (20 bytes)
		snprintf(txBuff, txBuffLen, "%1c-%3d-%3d-%3d-%1d-%1d-%1d", gearChar, steering, accel, brake, static_cast<int>(cameraCommand), toggleAV ? 1 : 0, static_cast<int>(otherInput));
		printf("String sent: %s", txBuff);

		connect(stream_out, (SOCKADDR*)&server, sizeof(server));

		send(stream_out, txBuff, txBuffLen, 0);

		Sleep(50);
	}
}