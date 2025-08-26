#include "Autopilot.h"

#include <algorithm>
#include <cmath>

#include "Utility.h"

//---TEMPORARY---//
std::vector<GPSPoint> destinationData = {
	// 2D array to hold GPS datapoints [longitude, latitude, course angle]
	{34.11457825, -117.70418549,0},      // point 1
	{34.11465073,-117.70417786,0},       // point 2
	{34.11465454,-117.70425415,0}, 	     // point 3
	{-1,-1,-1}                           // End of GPS waypoints
};

void Autopilot::runAutopilot()
{
	// recieve drive stuff from serial comm
	// place in buffer
	DriveCommand drive;
	drive.gear = GearID::Forward;	// TEMPORARY: Always forward gear

	while (!stopFlag.load())
	{
		if (run.load()) {
			if (destinations.empty()) {
				std::cout << "AUTOPILOT FINISHED!" << std::endl;
				return;
			}

			GPSPoint dest = destinations.front();
			int lidarDist = lidar.runLidar();
			int accelVal = 0;
			int brakeVal = 0;
			int steerVal = 50;

			///////////////////////////////////////////////////////////////////////////////
			// --- Destination Reached Check ---
			if (fabs(currPos.lon - dest.lon) <= destReachedThresh && fabs(currPos.lat - dest.lat) <= destReachedThresh) {
				// Current location is within the threshold of the destination
				std::cout << "Reached destination, moving to next point." << std::endl;
				destinations.pop(); // Move to the next destination

				if (destinations.empty())
					return;
				else
					dest = destinations.front();
			}

			///////////////////////////////////////////////////////////////////////////////
			// Adjust acceleration and braking based on Lidar distance
			// Scale the cruise speed proportionally to the distance from the object
			// The speed decreases non-linearly as the vehicle gets closer to the object
			accelVal = int(accelPropConst * float(lidarDist - minStopDist));
			accelVal = std::clamp(accelVal, 0, 100);
			drive.speed = accelVal;

			///////////////////////////////////////////////////////////////////////////////
			// Determine if braking is required based on Lidar distance
			brakeVal = std::max(0, int(brakePropConst * float(minStopDist - lidarDist)));
			brakeVal = std::clamp(brakeVal, 0, 100);
			drive.brake = brakeVal;

			///////////////////////////////////////////////////////////////////////////////////
			// Adjust steering based on GPS waypoints
			// Note to Developer: The `gps_data` is being sent correctly, but the calculations for the course angle
			// (especially the bearing difference) is not producing the desired results. Further debugging is needed
			// to fix the math logic for accurate steering guidance.
			
			// Convert latitude and longitude from degrees to radians for trigonometric calculations
			double current_lat_rad = deg_2_rad(currPos.lat);
			double current_lon_rad = deg_2_rad(currPos.lon);
			double destination_lat_rad = deg_2_rad(dest.lat);
			double destination_lon_rad = deg_2_rad(dest.lon);

			// Calculate the difference in longitude between the current position and destination
			double delta_lon = destination_lon_rad - current_lon_rad;

			// Calculate the desired bearing angle (in radians) to the destination
			// This uses the haversine formula but may not be accurate
			double y = sin(delta_lon) * cos(destination_lat_rad);
			double x = cos(current_lat_rad) * sin(destination_lat_rad) - sin(current_lat_rad) * cos(destination_lat_rad) * cos(delta_lon);
			double desired_bearing_rad = atan2(y, x);

			// Convert bearing from radians to degrees and normalize it to [0, 360]
			double desired_bearing = fmod(rad_2_deg(desired_bearing_rad), 360.0);

			// Find the difference in desired bearing and current heading in degrees
			double bearing_diff = desired_bearing - currPos.heading;

			steerVal = map(bearing_diff, 360.0, -360.0, 0.0, 100.0);
			// Normalize the bearing difference to the range [-180, 180]
			if (bearing_diff > 180.0) {
				bearing_diff -= 360.0;
			} else if (bearing_diff < -180.0) {
				bearing_diff += 360.0;
			}

			// Map bearing_diff from [-180, 180] to [0, 100] for control
			steerVal = map((bearing_diff), -180.0, 180.0, 0.0, 100.0);
			drive.steer = steerVal;

			// Debugging Information: Outputs the current GPS data, destination, and calculated values
			printf("GPS INFO:    Latitude: %.8f, Longitude: %.8f, Course: %.2f\n", currPos.lat, currPos.lon, currPos.heading);
			printf("DESTINATION: Latitude: %.8f, Longitude: %.8f\n", dest.lat, dest.lon);

			std::cout << "Desired Bearing: " << desired_bearing << "\n";
			std::cout << "Bearing Difference: " << bearing_diff << "\n";
			std::cout << "Mapped Steering Value: " << steerVal << "\n";

			sendQueue.push(makeMessageFrom(drive));
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		} else {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
}

void Autopilot::runProcessCommand()
{
	while (!stopFlag.load())
	{
		Message msg;
		msg = receiveQueue.waitAndPop();

		switch (msg.messageID)
		{
			case MessageID::StartAutopilot:
				start();
				break;
			case MessageID::StopAutopilot:
				stop();
				break;
			case MessageID::Invalid:
				break;
			default:
				std::cout << "Unknown autopilot command. skipping" << std::endl;
		}
	}
}

void Autopilot::runReceive()
{
	// For when we have serial communciation
}

void Autopilot::runTransmit()
{
	// For when we have serial communciation
}

void Autopilot::begin()
{
	stopFlag.store(false);
}

void Autopilot::end()
{
	stopFlag.store(true);
}

void Autopilot::signalStop()
{
	stop();
}

bool Autopilot::initIO()
{
	bool status = true;

    // Initialize I²C for the lidar subsystem
	if (!lidar.initialize())
		status = false;

	// Notify the user if any subsystem initialization failed
	if (status == false) {
        printf("[!!] One or more I/O devices failed to initialize!\n");
        printf("[!!] Try typing 'init pigpiod' before running program!\n");
	}

	return status;
}

void Autopilot::shutdown()
{
	lidar.cleanup();
}

void Autopilot::start()
{
	run.store(true);
	sendQueue.clear();
	findDestinations();
}

void Autopilot::stop()
{
	run.store(false);
	sendQueue.clear();
	clearDestinations();
}

void Autopilot::findDestinations()
{
	for (GPSPoint destination : destinationData)
	{
		destinations.emplace(destination);
	}
}

void Autopilot::clearDestinations()
{
	while (!destinations.empty())
		destinations.pop();
}
