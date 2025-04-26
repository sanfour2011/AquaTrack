#pragma once
#include "IScaleSensor.hpp"

class ScaleManager
{

public:
    ScaleManager(IScaleSensor &sensor) : m_sensor(sensor) {}; // Use an initialization list because references must be initialized directly and cannot be assigned later.

    float measureRawAverage(uint_fast8_t times);
    float measureRawNoTare(uint_fast8_t times=1);      // Returns raw weight data from the sensor
    float measureInGrams(uint_fast8_t times=1);  // Converts raw data to grams based on sensor calibration
    float measureQuantity(uint_fast8_t times=1); // Returns converted units (e.g., ml, pieces)
    void tare(uint_fast8_t times=1);
    void setTare(float tare);
    float getTare();
    void setUnitFactor(float factor);
    void setScaleGramFactor(float factor); // Sets the scale factor for grams
    float getScaleGramFactor(); // Returns the scale factor for grams (not in grams!!)
    bool isSensorReady();

private:
    float m_tare = 0.0f;
    float m_unitFactor = 1.0f;
    float m_scaleGramFactor = 1.0f; // Sets the scaling factor for unit conversion
    IScaleSensor &m_sensor; // Use a reference to ensure it cannot be changed and to avoid the need for nullptr checks.

};
