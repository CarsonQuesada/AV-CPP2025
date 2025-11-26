#include "vehicle_core/Devices/DriveSubsys.hpp"

DriveSubsys::DriveSubsys(std::shared_ptr<I2CBus> bus, uint8_t addr)
: I2CDevice("DriveSubsys")
{
  if (!open(bus, addr)) {
    throw std::runtime_error("Failed to open DriveSubsys");
  }
}

bool DriveSubsys::sendCommand(const DriveCommandWire& cmd) {
  return writeBytes(reinterpret_cast<const uint8_t*>(&cmd), sizeof(cmd));
}

bool DriveSubsys::readStatus(DriveStatusWire& status) {
  return readBytes(reinterpret_cast<uint8_t*>(&status), sizeof(status));
}
