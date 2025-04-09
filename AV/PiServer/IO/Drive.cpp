#include "Drive.h"

#include "Utility.h"

void Drive::initialize()
{
    // Configure GPIO for steering motor enable
	set_mode(piHandle, steering_EN, PI_OUTPUT);
	gpio_write(piHandle, steering_EN, 1);

    enable_motors(true);
    relax_brakes();
}

void Drive::brake(int brakeVal)
{
	if (brakeVal > 0) 
	{
		if (!braking) 
		{
			braking = true;
			gpio_write(piHandle, drive_FEN, 0); 					// Disable forward
			gpio_write(piHandle, drive_REN, 0); 					// Disable reverse
			set_PWM_dutycycle(piHandle, drive_FPWM, 0);				// Set forward PWM to 0
			set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
		}
		set_servo_pulsewidth(piHandle, brakeServoPin, map(brakeVal, 0, 100, relaxedBrakeVal, fullBrakeVal));  // Control braking
		lighting.enable_brake_lights(brakeVal > brakeLightThresh ? true : false);
	} 
	else 
	{
		braking = false;
		relax_brakes();  // Control braking
		lighting.enable_brake_lights(false);
	}
}

void Drive::accelerate(int accelValue, Gear gear)
{
	// if braking no acceleration
	if (braking) {
		gpio_write(piHandle, drive_FEN, 0); 					// Disable forward
		gpio_write(piHandle, drive_REN, 0); 					// Disable reverse
		set_PWM_dutycycle(piHandle, drive_FPWM, 0);				// Set forward PWM to 0
		set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
		return;
		std::cout << "Currently Braking no accel" << accelValue << std::endl;
	}

	// --- Calculate Acceleration ---
	// map acceleration to acceptable PWM value
	accelValue = map(accelValue, 0, 100, 0, 255);

	// --- Handle Drive Motor States ---
	switch (gear)
	{
		case Gear::Coast:	// Acceleration is inactive (coasting mode)
			std::cout << "Coast!" << std::endl;
			gpio_write(piHandle, drive_FEN, 0); 					// Disable forward
			gpio_write(piHandle, drive_REN, 0); 					// Disable reverse
			set_PWM_dutycycle(piHandle, drive_FPWM, 0);				// Set forward PWM to 0
			set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
			break;
		case Gear::Forward:	// Forward gear
			std::cout << "Forward! Acceleration: " << accelValue << std::endl;
			gpio_write(piHandle, drive_FEN, 1); 					// Enable forward
			gpio_write(piHandle, drive_REN, 1); 					// Disable reverse
			set_PWM_dutycycle(piHandle, drive_FPWM, accelValue);	// Set forward PWM to match acceleration
			set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
			break;
		case Gear::Reverse:	// Reverse gear
			std::cout << "Reverse! Acceleration: " << accelValue << std::endl;
			gpio_write(piHandle, drive_FEN, 1); 					// Enable forward
			gpio_write(piHandle, drive_REN, 1); 					// Disable reverse
			set_PWM_dutycycle(piHandle, drive_FPWM, accelValue);	// Set forward PWM to match acceleration
			set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
			break;
		default:
			gpio_write(piHandle, drive_FEN, 0); 					// Disable forward
			gpio_write(piHandle, drive_REN, 0); 					// Disable reverse
			set_PWM_dutycycle(piHandle, drive_FPWM, 0);				// Set forward PWM to 0
			set_PWM_dutycycle(piHandle, drive_RPWM, 0);				// Set reverse PWM to 0
			break;
	}
}

void Drive::steer(int targetPos, int currPos)
{
	// --- Initialize Steering Parameters ---
	int steeringDutyCycle = 255; // Maximum PWM duty cycle (0-255)
	// Note: High duty cycles may cause oscillations; 180 is suitable for most cases.

	// Map the target position from a 0-100 range to a PWM-compatible range
	targetPos = map(targetPos, 0, 100, 90, 417);

	// --- Steering Control Logic ---
	// Check if the current position is within the acceptable deadband around the target
	if ((currPos <= targetPos + deadband) && (currPos >= targetPos - deadband)) {
		// Centered position: No adjustments required
		printf("Steering: CENTERED\n");
		set_PWM_dutycycle(piHandle, steering_RPWM, 0); 
		set_PWM_dutycycle(piHandle, steering_LPWM, 0);
    }
	// Check if the current position is to the right of the target (needs left turn)
	else if (currPos > targetPos + deadband) {
		printf("Steering: TURNING RIGHT\n");
		set_PWM_dutycycle(piHandle, steering_LPWM, 0); 			// Disable left-turn motor
		set_PWM_dutycycle(piHandle, steering_RPWM, steeringDutyCycle);	// Engage right-turn motor
	}
	// Check if the current position is to the left of the target (needs right turn)
	else if (currPos < targetPos - deadband) {
		printf("Steering: TURNING LEFT\n");
		set_PWM_dutycycle(piHandle, steering_RPWM, 0);			// Disable right-turn motor
		set_PWM_dutycycle(piHandle, steering_LPWM, steeringDutyCycle);	// Engage left-turn motor
	}
}

void Drive::cleanup()
{
	if (initialized) {
		initialized = false;
		relax_brakes();
		enable_motors(false);
		set_PWM_dutycycle(piHandle, drive_FPWM, 0);	// Set forward PWM to match acceleration
		set_PWM_dutycycle(piHandle, drive_RPWM, 0);	
	}
}

Drive::~Drive()
{
	cleanup();
}

void Drive::relax_brakes()
{
    set_servo_pulsewidth(piHandle, brakeServoPin, relaxedBrakeVal); // Relax brake servo
}
