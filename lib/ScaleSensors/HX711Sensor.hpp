#pragma once

#include "IScaleSensor.hpp"
#include <HX711.h>
#define RETRIES 100
#define DELAY_MS 10

class HX711Sensor : public IScaleSensor
{
public:
    HX711Sensor(int dataPin, int clockPin);
    float readRawValue() override;
    bool isReady() override;
    void setGain(byte gain);

    //bool calibrate(float knownWeight) override;

private:
    HX711 m_hx711;
    float m_tareValue = 0.0f;
    float m_scaleFactor = 1.0f;
};