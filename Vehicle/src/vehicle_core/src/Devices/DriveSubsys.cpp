#include "vehicle_core/Devices/DriveSubsys.hpp"

DriveSubsys::DriveSubsys(std::shared_ptr<I2CBus> bus, uint8_t addr)
: I2CDevice("DriveSubsys")
{
  if (!open(bus, addr)) {
    throw std::runtime_error("Failed to open DriveSubsys");
  }
}

bool DriveSubsys::sendCommand(const DriveCommandWire& cmd) {
  bool ok = writeBytes(reinterpret_cast<const uint8_t*>(&cmd), sizeof(cmd));
  if (ok) {
    lastCmd_ = cmd;
    haveCmd_ = true;
  }
  return ok;
}

bool DriveSubsys::readStatus(DriveStatusWire& status) {
  bool ok = readBytes(reinterpret_cast<uint8_t*>(&status), sizeof(status));
  if (ok) {
    logSample(status);
  }
  return ok;
}

// ---------- Logging ----------

void DriveSubsys::startLogging(const std::string& path) {
  if (logFile_.is_open()) {
    logFile_.close();
  }

  logFile_.open(path, std::ios::out | std::ios::trunc);
  if (!logFile_) {
    throw std::runtime_error("Failed to open log file: " + path);
  }

  logFile_ << "t_sec,"
           << "target_speed_mmps,"
           << "measured_speed_mmps,"
           << "brake_percent,"
           << "flags,"
           << "fault_bits,"
           << "target_steer_millirad,"
           << "measured_steer_millirad"
           << "\n";

  logFile_.flush();
  t0_ = std::chrono::steady_clock::now();   // <-- changed
}

void DriveSubsys::stopLogging() {
  if (logFile_.is_open()) {
    logFile_.flush();
    logFile_.close();
  }
}

void DriveSubsys::logSample(const DriveStatusWire& status) {
  if (!logFile_.is_open() || !haveCmd_) {
    return;
  }

  using std::chrono::duration_cast;
  using std::chrono::duration;

  auto now  = std::chrono::steady_clock::now();  // <-- changed
  double t  = duration_cast<duration<double>>(now - t0_).count();

  logFile_
    << t << ","
    << lastCmd_.target_speed_mmps << ","
    << status.measured_speed_mmps << ","
    << static_cast<int>(lastCmd_.brake_percent) << ","
    << static_cast<int>(lastCmd_.flags) << ","
    << status.fault_bits << ","
    << lastCmd_.target_steer_millirad << ","
    << status.measured_steer_millirad
    << "\n";
}
