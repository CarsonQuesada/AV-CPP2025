#include "I2CInterface.h"

#include <Wire.h>
#include <string.h>
#include <util/atomic.h>

// Define the static instance_ pointer
I2CInterface* I2CInterface::instance_ = nullptr;

I2CInterface::I2CInterface(uint8_t address)
  : address_(address) {}

void I2CInterface::begin() {
  instance_ = this;        // register this object for ISR callbacks

  Wire.begin(address_);
  Wire.onReceive(I2CInterface::onReceiveISR);
  Wire.onRequest(I2CInterface::onRequestISR);
}

// ---- Public API ----

DriveCommand I2CInterface::getNewDriveCommand() {
  DriveCommand cmd = lastDriveCommand_;  // default to last valid

  if (!newCommand_) {
    // No new data: just return previous command
    return cmd;
  }

  // Copy buffer into local struct atomically
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    if (rxBufferLen_ == sizeof(DriveCommand)) {
      memcpy(&cmd, rxBuffer_, sizeof(DriveCommand));
      lastDriveCommand_ = cmd;
      newCommand_ = false;
    } else {
      // Bad length: ignore, keep lastDriveCommand_ unchanged
      newCommand_ = false;
    }
  }

  return cmd;
}

void I2CInterface::setDriveStatus(const DriveStatus& status) {
  // Update status snapshot atomically to avoid the master reading half-updated data
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    currDriveStatus_ = status;
  }
}

// ---- Static ISR trampolines ----

void I2CInterface::onReceiveISR(int count) {
  if (instance_) {
    instance_->handleReceive(count);
  } else {
    // Drain bytes if no instance registered
    while (Wire.available()) {
      Wire.read();
    }
  }
}

void I2CInterface::onRequestISR() {
  if (instance_) {
    instance_->handleRequest();
  } else {
    // Nothing to send
  }
}

// ---- Instance handlers ----

void I2CInterface::handleReceive(int count) {
  if (count <= 0 || count > I2C_CMD_MAX) {
    // Invalid: clear buffer
    while (Wire.available()) {
      Wire.read();
    }
    return;
  }

  uint8_t n = 0;
  while (Wire.available() && n < count) {
    rxBuffer_[n++] = Wire.read();
  }

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    rxBufferLen_ = n;
    newCommand_  = true;
  }
}

void I2CInterface::handleRequest() {
  DriveStatus snapshot;

  // Take a snapshot atomically
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    snapshot = currDriveStatus_;
  }

  Wire.write(reinterpret_cast<uint8_t*>(&snapshot), sizeof(snapshot));
}
