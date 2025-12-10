#pragma once
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>
#include <vector>
#include <optional>
#include <chrono>
#include <thread>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <utility>

class GtU7Gps {
public:
    enum class DynModel : uint8_t {
        PORTABLE   = 0,
        STATIONARY = 2,
        PEDESTRIAN = 3,
        AUTOMOTIVE = 4,
        SEA        = 5,
        AIRBORNE1g = 6,
        AIRBORNE2g = 7,
        AIRBORNE4g = 8
    };
    enum class Mode : uint8_t {
        GPS_10HZ,     // Best performance for GPS-only (u-blox 7 supports 10 Hz)
        GPS_GLO_5HZ   // If GLONASS is enabled on your unit, 5 Hz is recommended
    };

    struct Fix {
        std::optional<double> lat_deg, lon_deg, alt_m;
        std::optional<int>    fix_quality;   // 0=no, 1=GPS, 2=DGPS/SBAS
        std::optional<int>    sats;
        std::optional<double> hdop;
        std::optional<double> sog_knots, cog_deg;
        std::optional<double> vdop;        // from GSA
        std::optional<double> sdev_lat_m;  // from GST (field 7)
        std::optional<double> sdev_lon_m;  // from GST (field 8)
        std::optional<double> sdev_alt_m;  // from GST (field 9)
        bool valid = false;                 // RMC status A/V
        std::string time_utc;              // hhmmss.sss
    };

    struct NmeaMuteGuard {
        GtU7Gps* s; 
        bool active{false};
        explicit NmeaMuteGuard(GtU7Gps* self);
        void dismiss();
        ~NmeaMuteGuard();
    };

    // ---- Lifecycle ----
    GtU7Gps();
    ~GtU7Gps();

    // Open the serial port (8N1). Call before configureForKart().
    bool open(const std::string& device="/dev/ttyS0", int baud=9600);

    // Non-blocking-ish: assemble a GGA+RMC snapshot within timeout_ms.
    std::optional<Fix> readFix(int timeout_ms=300);

    bool cfgBaudRate(int target_baud);
    bool cfgRateHz(int hz);
    bool cfgSBAS();
    bool cfgNavModel(DynModel dyn);
    bool cfgNmeaRates(int fast_hz);
    bool cfgNmeaNoFilter();
    bool sendPUBX(const std::string& body_no_dollar);
    bool cfgNmeaRatesPubx40(int fast_hz);
    void saveToBBR();
    int pollEffectiveRateHz();

    // Optional: adjust dynamic model later if your vehicle behavior changes
    bool setDynamicModel(DynModel m);

private:
    // ===== Serial =====
    static speed_t toSpeedT(int baud);
    bool setSpeed(int baud);             // change speed without closing fd
    bool cfgPortProtocols(bool ubx_out, bool nmea_out); // keep current baud, tweak protocols
    bool openPort(int baud);
    bool reopen(int baud);

    // ===== UBX helpers =====
    bool sendUBX(uint8_t cls, uint8_t id, const std::vector<uint8_t>& payload);
    bool readUBX(uint8_t cls, uint8_t id, std::vector<uint8_t>& out, int timeout_ms=400);
    bool waitACK(uint8_t cls, uint8_t id, int timeout_ms=800);
    static std::pair<uint8_t,uint8_t> checksum(size_t len, const uint8_t* data);

    // ===== UBX config steps (u-blox 7 safe set) =====
    bool cfgPort(int new_baud);

    // ===== NMEA parsing =====
    static bool startsWith(const std::string& s, const char* pfx);
    static double nmeaToDegrees(const std::string& ddmm, const std::string& hemi);
    static std::vector<std::string> splitCSV(const std::string& s);
    static void parseGGA(const std::string& line, Fix& fx);
    static void parseRMC(const std::string& line, Fix& fx);
    static void parseGSA(const std::string& line, Fix& fx);
    static void parseGST(const std::string& line, Fix& fx);

    bool readLine(std::string& out, int poll_ms);

    // --- NMEA PUBX,41 helper ---
    bool sendPUBX41(int baud, uint16_t inMask=0x0003, uint16_t outMask=0x0003);

    // --- Simple probe: do we see NMEA soon? ---
    bool seeNmeaOrUbx(int timeout_ms=500);

    // --- Deterministic two-try baud detect (9600 / 115200) ---
    int detectBaud();

    static int64_t nowMs();

    // ---- members ----
    std::string dev_;
    int fd_;
    int baud_;
};
