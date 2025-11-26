#include "vehicle_core/Devices/LightingSubsys.hpp"

LightingSubsys::LightingSubsys(std::shared_ptr<I2CBus> bus, uint8_t addr)
: I2CDevice("LightingSubsys")
{
  if (!open(bus, addr)) {
    throw std::runtime_error("Failed to open LightingSubsys");
  }
}

bool LightingSubsys::sendCommand(const uint8_t& cmd) {
  return writeBytes(&cmd, sizeof(cmd));
}
