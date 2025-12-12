#pragma once

// KmlPathLoader.hpp
// Purpose: Load waypoints from a .kml file for use in path following.

#include <string>
#include <vector>

#include "PurePursuit.hpp"


struct GpsPoint {
    double lat;   // degrees
    double lon;   // degrees
};

class KmlPathLoader
{
public:
    // Loads raw GPS points (lat/lon degrees) from a .kml file.
    // Throws std::runtime_error on failure.
    std::vector<GpsPoint> loadGps(const std::string &filename);

    // Loads GPS and converts to UTM x,y in meters.
    std::vector<Waypoint> loadXY(const std::string &filename);

private:
    // Helper: convert one lat/lon (deg) to UTM x,y (meters)
    Waypoint gpsToXY(double lat_deg, double lon_deg);
};
