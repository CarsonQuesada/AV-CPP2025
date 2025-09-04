// NOTES
// encoderTicks variable does note reset. Overflow is probably not a concern though

#include <NMEAGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define ENCODER_PPR 600
#define WHEEL_DIAMETER_M 0.065 // TODO: get more accurate measurements
#define I2C_ADDRESS 0x15

#pragma pack(push, 1)
struct TelemetryData {
    uint8_t gpsOnline;    // 1 = true, 0 = false
    float lat;            // degrees
    float lon;            // degrees
    float heading;        // degrees
    float speed;          // m/s
    float distanceDelta;  // m
};
#pragma pack(pop)

const int RXPin = 5, TXPin = 4;
const int encoderPinA = 2; // Interrupt-capable
const int encoderPinB = 3; // Interrupt-capable
const uint32_t GPSBaud = 9600;

// Variables for encoder
volatile long encoderTicks = 0;
volatile int8_t lastEncoded = 0;

unsigned long lastSpeedCalcTime = 0;
long lastTickCount = 0;
float wheelSpeed = 0.0; // meters per second

SoftwareSerial gpsSerial(RXPin, TXPin);
NMEAGPS gps;
gps_fix currentFix;
float lastFixLat = 0.0;
float lastFixLon = 0.0;
double lastHeading = 0.0;
bool firstFixReceived = false;

double distance_threshold_meters = 1.5;
double distance_threshold_degrees = distance_threshold_meters / 111000.0; // ~8.06e-6 degrees
double threshold_squared = distance_threshold_degrees * distance_threshold_degrees; // ~6.5e-11

volatile TelemetryData g_last;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  Wire.begin(I2C_ADDRESS); // Set this Arduino as I2C slave at address 0x15
  Wire.onRequest(sendTelemetryData);

  setUpEncoder();
  Serial.println("Initializing GPS + Encoder");
}

void loop() {
  TelemetryData s;
  s.gpsOnline = currentFix.valid.location ? 1 : 0;
  s.lat       = currentFix.valid.location ? currentFix.latitude()  : 0.0f;
  s.lon       = currentFix.valid.location ? currentFix.longitude() : 0.0f;
  s.heading   = (float) lastHeading;
  s.speed     = wheelSpeed;

  noInterrupts();
  long dt = encoderTicks; encoderTicks = 0;  // atomically grab ticks
  interrupts();

  float rev = (float)dt / ENCODER_PPR;
  s.distanceDelta = rev * (PI * WHEEL_DIAMETER_M);

  // publish snapshot
  noInterrupts();
  g_last = s;
  interrupts();

  if (gps.available(gpsSerial)) {
    currentFix = gps.read();

    if (currentFix.valid.location) {
      double lat = currentFix.latitude();
      double lon = currentFix.longitude();

      if (firstFixReceived) {
        if (hasMovedEnough(lastFixLat, lastFixLon, lat, lon)) {
          double newHeading = calculateBearing(lastFixLat, lastFixLon, lat, lon);
          lastHeading = 0.2 * newHeading + 0.8 * lastHeading;
          lastFixLat = lat;
          lastFixLon = lon;
        }
      } else {
        lastFixLat = lat;
        lastFixLon = lon;
        firstFixReceived = true;
      }

      Serial.print(F("Location: "));
      Serial.print(lat, 6);
      Serial.print(F(", "));
      Serial.print(lon, 6);
      Serial.print(F(", Heading: "));
      Serial.print(lastHeading, 2);
    }
  }

  calculateSpeed(); // update speed regularly
}

void sendTelemetryData() {
  Wire.write((const uint8_t*)&g_last, sizeof(g_last));
}


bool hasMovedEnough(double lat1, double lon1, double lat2, double lon2) {
  double deltaLat = lat2 - lat1;
  double deltaLon = lon2 - lon1;
  double distanceSquared = deltaLat * deltaLat + deltaLon * deltaLon;
  return distanceSquared > threshold_squared;
}

double calculateBearing(double lat1, double lon1, double lat2, double lon2) {
  double dLon = radians(lon2 - lon1);
  double y = sin(dLon) * cos(radians(lat2));
  double x = cos(radians(lat1)) * sin(radians(lat2)) -
             sin(radians(lat1)) * cos(radians(lat2)) * cos(dLon);
  double bearing = atan2(y, x);
  bearing = degrees(bearing);
  if (bearing < 0) bearing += 360.0;
  return bearing;
}

void setUpEncoder() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  int encoded = (digitalRead(encoderPinA) << 1) | digitalRead(encoderPinB);
  lastEncoded = encoded;

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
}

void updateEncoder() {
  int MSB = digitalRead(encoderPinA);
  int LSB = digitalRead(encoderPinB);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderTicks++;
  else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderTicks--;

  lastEncoded = encoded;
}

void calculateSpeed() {
  unsigned long now = millis();
  if (now - lastSpeedCalcTime >= 200) { // every 200ms
    long ticksNow = encoderTicks;
    long deltaTicks = ticksNow - lastTickCount;
    lastTickCount = ticksNow;

    float revolutions = (float)deltaTicks / ENCODER_PPR;
    float distance = revolutions * (PI * WHEEL_DIAMETER_M);
    wheelSpeed = distance / ((now - lastSpeedCalcTime) / 1000.0); // m/s

    lastSpeedCalcTime = now;
    Serial.print("Ticks: "); Serial.print(encoderTicks);
    Serial.print(", Speed (m/s): "); Serial.println(wheelSpeed, 3);
  }
}

