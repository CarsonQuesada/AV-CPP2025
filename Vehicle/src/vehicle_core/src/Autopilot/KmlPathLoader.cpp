#include "vehicle_core/Autopilot/KmlPathLoader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <GeographicLib/UTMUPS.hpp>

// ------------------------------------------------------
// Parse KML and extract GPS points
// ------------------------------------------------------
std::vector<GpsPoint> KmlPathLoader::loadGps(const std::string &filename)
{
    // Read entire file into string
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open KML file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Find <coordinates> ... </coordinates>
    const std::string tag_start = "<coordinates>";
    const std::string tag_end   = "</coordinates>";

    auto start = content.find(tag_start);
    auto end   = content.find(tag_end);

    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("No <coordinates> block found in KML file");
    }

    start += tag_start.length();
    std::string coord_block = content.substr(start, end - start);

    // Split block into lines
    std::stringstream ss(coord_block);
    std::string line;

    std::vector<GpsPoint> points;

    while (std::getline(ss, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue;

        // Format: lon,lat,alt
        double lon, lat;
        char comma1, comma2;

        std::stringstream ls(line);
        if (!(ls >> lon >> comma1 >> lat >> comma2)) {
            // Skip malformed lines
            continue;
        }

        points.push_back(GpsPoint{lat, lon});
    }

    return points;
}

// ------------------------------------------------------
// Convert lat/lon degrees → UTM x,y meters
// ------------------------------------------------------
Waypoint KmlPathLoader::gpsToXY(double lat_deg, double lon_deg)
{
    double x, y;
    int zone;
    bool northp;

    GeographicLib::UTMUPS::Forward(lat_deg, lon_deg, zone, northp, x, y);

    // x = Easting (meters)
    // y = Northing (meters)
    return Waypoint{x, y};
}

// ------------------------------------------------------
// Load GPS and convert entire path to UTM x,y
// ------------------------------------------------------
std::vector<Waypoint> KmlPathLoader::loadXY(const std::string &filename)
{
    auto gps_points = loadGps(filename);

    std::vector<Waypoint> xy;
    xy.reserve(gps_points.size());

    for (auto &p : gps_points) {
        xy.push_back(gpsToXY(p.lat, p.lon));
    }

    return xy;
}
