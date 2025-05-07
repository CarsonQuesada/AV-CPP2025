#include <Wire.h>

#define I2C_SLAVE_ADDRESS 6 // Set the Arduino's I2C address

// This enum is also used in PiServer/IO/Lighting.h
// Any change to this one should be made to the other and vice versa
enum class LightingCommand : uint8_t
{
  Unkown = 0, 
  HeadlightsOn,   HeadlightsOff, 
  LeftSigOn,      LeftSigOff,
  RightSigOn,     RightSigOff,
  HazardsOn,      HazardsOff,
  BrakeLightsOn,  BrakeLightsOff, 
  StopConnecting, Connected,      Reconnecting
};

// Define pins for controlling the lights
const int headlightsPin = 2;
const int leftTurnSignalPin = 3;
const int rightTurnSignalPin = 4;
const int brakeLightsPin = 5;
const int connectLEDPin = 6;

LightingCommand receivedAction = LightingCommand::Unkown; // Variable to store the received action
bool blinkLeftSignal = false;
bool blinkRightSignal = false;
bool activateHazards = false;
bool connected = false;
bool connecting = true;
bool stoppedConnecting = false;

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 0;
bool connectLEDState = false; // Off
bool hazardState = false; // Off
bool leftState = false;
bool rightState = false;

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  // Initialize pins as outputs
  pinMode(headlightsPin, OUTPUT);
  pinMode(leftTurnSignalPin, OUTPUT);
  pinMode(rightTurnSignalPin, OUTPUT);
  pinMode(brakeLightsPin, OUTPUT);
  pinMode(connectLEDPin, OUTPUT);

  // Turn off all lights initially
  turnOffLights();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = currentMillis;

    if (activateHazards) {
      hazardState = !hazardState;
      digitalWrite(leftTurnSignalPin, hazardState);
      digitalWrite(rightTurnSignalPin, hazardState);
    } else {
      if (blinkLeftSignal) {
        leftState = !leftState;
        digitalWrite(leftTurnSignalPin, leftState);
      } else {
        digitalWrite(leftTurnSignalPin, LOW);
      }

      if (blinkRightSignal) {
        rightState = !rightState;
        digitalWrite(rightTurnSignalPin, rightState);
      } else {
        digitalWrite(rightTurnSignalPin, LOW);
      }
    }

    if (connecting) {
      connectLEDState = !connectLEDState;
      digitalWrite(connectLEDPin, connectLEDState);
    } else {
      digitalWrite(connectLEDPin, connected ? HIGH : LOW);
    }
  }
}

void receiveEvent(int byteCount) {
  if (byteCount == 1) {  // Expecting a single byte for the action
      int receivedValue = Wire.read();

    if (receivedValue < static_cast<int>(LightingCommand::Unkown) || receivedValue > static_cast<int>(LightingCommand::Reconnecting)) {
      receivedAction = LightingCommand::Unkown;  // Handle invalid input
    } else {
      receivedAction = static_cast<LightingCommand>(receivedValue);
    }

    // Process the received action
    switch (receivedAction) {
      case LightingCommand::HeadlightsOn:  // Turn on headlights
        digitalWrite(headlightsPin, HIGH);
        break;
      case LightingCommand::HeadlightsOff:  // Turn off headlights
        digitalWrite(headlightsPin, LOW);
        break;
      case LightingCommand::LeftSigOn:  // Turn left turn signal on
        blinkLeftSignal = true;
        break;
      case LightingCommand::LeftSigOff:  // Turn left turn signal on
        blinkLeftSignal = false;
        break;
      case LightingCommand::RightSigOn:  // toggle right turn signal
        blinkRightSignal = true;
        break;
      case LightingCommand::RightSigOff:  // toggle right turn signal
        blinkRightSignal = false;
        break;
      case LightingCommand::HazardsOn:  // Toggle hazard lights
        activateHazards = true;
        break;
      case LightingCommand::HazardsOff:  // Toggle hazard lights
        activateHazards = false;
        break;
      case LightingCommand::BrakeLightsOn:  // Apply brake lights
        digitalWrite(brakeLightsPin, HIGH);
        break;
      case LightingCommand::BrakeLightsOff:  // Release brake lights
        digitalWrite(brakeLightsPin, LOW);
        break;
      case LightingCommand::StopConnecting:  // Turn off Connection LED
        connected = false;
        connecting = false;
        stoppedConnecting = true;
        digitalWrite(connectLEDPin, LOW);
        break;
      case LightingCommand::Connected:  // Turn on Connection LED
        connected = true;
        connecting = false;
        stoppedConnecting = false;
        digitalWrite(connectLEDPin, HIGH);
        break;
      case LightingCommand::Reconnecting:  // blink Connection LED
        connected = false;
        connecting = true;
        stoppedConnecting = false;
        break;
      default:
        // Handle unknown action or add custom cases as needed
        break;
    }
  }
}

void turnOffLights() {
  digitalWrite(headlightsPin, LOW);
  digitalWrite(leftTurnSignalPin, LOW);
  digitalWrite(rightTurnSignalPin, LOW);
  digitalWrite(brakeLightsPin, LOW);
  digitalWrite(connectLEDPin, LOW);
}
