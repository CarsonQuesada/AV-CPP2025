#include "vehicle_core/Devices/I2C/I2CDevice.hpp"

I2CDevice::I2CDevice() = default;

I2CDevice::I2CDevice(std::string tag)
: tag_(std::move(tag))
{}

bool I2CDevice::open(std::shared_ptr<I2CBus> bus, uint16_t addr) {
    if (!bus || !bus->isOpen()) {
        lastError_ = prefix() + "open failed: invalid bus";
        return false;
    }

    bus_ = std::move(bus);
    address_ = addr;
    lastError_.clear();
    return true;
}

bool I2CDevice::isOpen() const {
    return (bool)bus_;
}

uint16_t I2CDevice::address() const {
    return address_;
}

std::string I2CDevice::busPath() const {
    return bus_ ? bus_->path() : "";
}

const std::string& I2CDevice::getTag() const {
    return tag_;
}

void I2CDevice::setTag(std::string t) {
    tag_ = std::move(t);
}

const std::string& I2CDevice::getLastError() const {
    return lastError_;
}

std::string I2CDevice::prefix() const {
    return "[" + tag_ + " @ " + (bus_ ? bus_->path() : "") +
           " 0x" + to_hex(address_) + "] ";
}

std::string I2CDevice::to_hex(uint8_t v) {
    char b[5];
    std::snprintf(b, sizeof(b), "%02X", v);
    return b;
}

bool I2CDevice::readReg8(uint8_t reg, uint8_t* out, size_t len) {
    if (!bus_) { lastError_ = prefix() + "bus not open"; return false; }
    if (!bus_->readReg8(address_, reg, out, len)) {
        lastError_ = prefix() + bus_->lastError();
        return false;
    }
    return true;
}

bool I2CDevice::writeReg8(uint8_t reg, const uint8_t* data, size_t len) {
    if (!bus_) { lastError_ = prefix() + "bus not open"; return false; }
    if (!bus_->writeReg8(address_, reg, data, len)) {
        lastError_ = prefix() + bus_->lastError();
        return false;
    }
    return true;
}

bool I2CDevice::readBytes(uint8_t* data, size_t len) {
    if (!bus_) { lastError_ = prefix() + "bus not open"; return false; }
    if (!bus_->readBytes(address_, data, len)) {
        lastError_ = prefix() + bus_->lastError();
        return false;
    }
    return true;
}

bool I2CDevice::writeBytes(const uint8_t* data, size_t len) {
    if (!bus_) { lastError_ = prefix() + "bus not open"; return false; }
    if (!bus_->writeBytes(address_, data, len)) {
        lastError_ = prefix() + bus_->lastError();
        return false;
    }
    return true;
}
