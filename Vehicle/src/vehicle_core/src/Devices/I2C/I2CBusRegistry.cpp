#include "vehicle_core/Devices/I2C/I2CBusRegistry.hpp"

I2CBusRegistry& I2CBusRegistry::getInstance() {
    static I2CBusRegistry instance;
    return instance;
}

std::shared_ptr<I2CBus> I2CBusRegistry::getOrOpen(const std::string& path,
                                                  std::string* err)
{
    std::lock_guard<std::mutex> lk(mut_);

    // Find bus if it already exists
    auto it = buses_.find(path);
    if (it != buses_.end()) {
        if (auto bus = it->second.lock()) {
            return bus;
        }
    }

    // Create and open new bus
    auto bus = std::make_shared<I2CBus>();
    if (!bus->open(path)) {
        if (err) *err = bus->lastError();
        return nullptr;
    }

    // Store and return
    buses_[path] = bus;
    return bus;
}
