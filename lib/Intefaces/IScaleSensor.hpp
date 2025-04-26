#pragma once

#include <stdint.h>

class IScaleSensor // Interface for Mocking or Real Sensor
{
public:
    virtual ~IScaleSensor() = default; // Add a virtual destructor
    virtual float readRawValue() = 0;
    virtual bool isReady() { return true; } // Provide a default implementation
};