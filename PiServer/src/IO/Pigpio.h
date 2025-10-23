#pragma once
#include <iostream>

#include <pigpiod_if2.h>

class Pigpio
{
public:
    static inline Pigpio& getInstance() 
    {
        static Pigpio pigpioInstance;
        return pigpioInstance;
    }

    bool initialize();
    void cleanup();
    inline int const getHandle() { return piHandle; }
private:
    bool initialized = false; 
    int piHandle;

    Pigpio() {}                                   // private constructor to prevent more than one instance
    Pigpio(const Pigpio&) = delete;               // Prevent copy construction
    Pigpio& operator=(const Pigpio&) = delete;    // Prevent assignment
    ~Pigpio();
};