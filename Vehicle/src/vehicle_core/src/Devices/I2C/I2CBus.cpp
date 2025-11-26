#include "vehicle_core/Devices/I2C/I2CBus.hpp"

#include <unistd.h>
#include <vector>
#include <cstring>

I2CBus::I2CBus() = default;

I2CBus::~I2CBus() {
    close();
}

bool I2CBus::open(const std::string& path) {
    std::lock_guard<std::mutex> lk(mut_);

    if (fd_ >= 0) { 
        path_ = path; 
        lastError_.clear(); 
        return true; 
    }

    int fd = ::open(path.c_str(), O_RDWR | O_CLOEXEC);
    if (fd < 0) { 
        lastError_ = std::string("open " + path_); 
        return false; 
    }

    fd_ = fd;
    path_ = path;
    addr_.reset();
    lastError_.clear();
    return true;
}

void I2CBus::close() {
    std::lock_guard<std::mutex> lk(mut_);
    if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
    addr_.reset();
}

bool I2CBus::isOpen() const { 
    return fd_ >= 0; 
}

const std::string& I2CBus::path() const { 
    return path_; 
}

const std::string& I2CBus::lastError() const { 
    return lastError_; 
}

bool I2CBus::writeBytes(uint16_t addr7, const uint8_t* data, size_t len) {
    std::lock_guard<std::mutex> lk(mut_);

    if (!ensureOpenLocked_()) return false;
    if (!ensureAddressLocked_(addr7)) return false;

    ssize_t n = ::write(fd_, data, len);
    if (n != static_cast<ssize_t>(len)) { 
        lastError_ = "I2C write"; 
        return false; 
    }
    return true;
}

bool I2CBus::writeReg8(uint16_t addr7, uint8_t reg, const uint8_t* data, size_t len) {
    std::lock_guard<std::mutex> lk(mut_);

    if (!ensureOpenLocked_()) return false;
    if (!ensureAddressLocked_(addr7)) return false;
    
    std::vector<uint8_t> buf(1 + len);
    buf[0] = reg;
    std::memcpy(buf.data() + 1, data, len);

    ssize_t n = ::write(fd_, buf.data(), buf.size());
    if (n != static_cast<ssize_t>(buf.size())) { 
        lastError_ = "I2C writeReg8"; 
        return false; 
    }
    return true;
}

bool I2CBus::readBytes(uint16_t addr7, uint8_t* data, size_t len) {
    std::lock_guard<std::mutex> lk(mut_);

    if (!ensureOpenLocked_()) return false;
    if (!ensureAddressLocked_(addr7)) return false;

    ssize_t n = ::read(fd_, data, len);
    if (n != static_cast<ssize_t>(len)) { 
        lastError_ = "I2C read"; 
        return false; 
    }
    return true;
}

bool I2CBus::readReg8(uint16_t addr7, uint8_t reg, uint8_t* out, size_t len) {
    std::lock_guard<std::mutex> lk(mut_);
    
    if (!ensureOpenLocked_()) return false;
    if (!ensureAddressLocked_(addr7)) return false;

    if (::write(fd_, &reg, 1) != 1) { 
        lastError_ = "I2C reg-select write"; 
        return false; 
    }
    ssize_t n = ::read(fd_, out, len);
    if (n != static_cast<ssize_t>(len)) { 
        lastError_ = "I2C readReg8"; 
        return false; 
    }
    return true;
}

bool I2CBus::ensureOpenLocked_() {
    if (fd_ < 0) { 
        lastError_ = "I2C bus not open"; 
        return false; 
    }
    return true;
}

bool I2CBus::ensureAddressLocked_(uint16_t addr7) {
    if (!addr_.has_value() || addr_.value() != addr7) {
        if (ioctl(fd_, I2C_SLAVE, addr7) < 0) { 
            lastError_ = "I2C_SLAVE ioctl"; 
            return false; 
        }
        addr_ = addr7;
    }
    return true;
}
