// test/Hardware/test_scaleMnager.cpp
#include <gtest/gtest.h>
#include <Arduino.h>
#include "HX711Sensor.hpp"

#define dataPin 1
#define clkPin 0

class HX711SensorTest : public ::testing::Test
{
protected:
    HX711Sensor m_hx711Sensor = HX711Sensor(dataPin, clkPin);
};

TEST_F(HX711SensorTest, Reading_RawValue)
{
    float rawValue = m_hx711Sensor.readRawValue();  
    Serial.print("[DEBUG] Raw Value: ");  // Nur sichtbar im Serial Monitor!
    Serial.println(rawValue);

    // Serial.print("Raw Value: ");
    // Serial.println(rawValue);
    EXPECT_NE(rawValue, std::numeric_limits<float>::min());
};

TEST_F(HX711SensorTest, IS_Sensor_Ready){
    delay(500);
    EXPECT_TRUE(m_hx711Sensor.isReady());
};

// TEST_F(HX711SensorTest, HX711DummySensorTest)
// {
//     EXPECT_EQ(1, 1);
// };