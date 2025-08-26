#include <NMEAGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

struct GPSPoint {
  double lat, lon;
};

SoftwareSerial gpsSerial(RXPin, TXPin);
NMEAGPS gps;
gps_fix currentFix;
GPSPoint lastFix;
double lastHeading = 0.0;
bool firstFixReceived = false;

double distance_threshold_meters = 1.5;
double distance_threshold_degrees = distance_threshold_meters / 111000.0; // ~8.06e-6 degrees
double threshold_squared = distance_threshold_degrees * distance_threshold_degrees; // ~6.5e-11

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  Wire.begin(0x15); // Set this Arduino as I2C slave at address 0x15
  Wire.onRequest(sendGPSData);

  Serial.println("Initializing GPS...");
}

void loop() {
  if (gps.available(gpsSerial)) {
    currentFix = gps.read();
    
    if (currentFix.valid.location) {
      double lat = currentFix.latitude();
      double lon = currentFix.longitude();

      if (firstFixReceived) {
        if (hasMovedEnough(lastFix.lat, lastFix.lon, lat, lon)) {
          double newHeading = calculateBearing(lastFix.lat, lastFix.lon, lat, lon);
          lastHeading = 0.2 * newHeading + 0.8 * lastHeading;
          lastFix = { lat, lon };
        }
      } else {
        lastFix = { lat, lon };
        firstFixReceived = true;
      }

      Serial.print(F("Location: "));
      Serial.print(lat, 6);
      Serial.print(F(", "));
      Serial.print(lon, 6);
      Serial.print(F(", Heading: "));
      Serial.println(lastHeading, 2);
    }
  }
}

void sendGPSData() {
  if (currentFix.valid.location) {
    int32_t lat_scaled = (int32_t)(currentFix.latitude() * 1e6);
    int32_t lon_scaled = (int32_t)(currentFix.longitude() * 1e6);
    uint16_t heading_scaled = (uint16_t)(lastHeading * 100);

    Wire.write((byte*)&lat_scaled, sizeof(lat_scaled));
    Wire.write((byte*)&lon_scaled, sizeof(lon_scaled));
    Wire.write((byte*)&heading_scaled, sizeof(heading_scaled));
  }
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
