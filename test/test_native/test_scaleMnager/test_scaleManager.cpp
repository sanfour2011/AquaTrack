#include <gtest/gtest.h>
#include "ScaleManager.hpp"
#include "../mocks/mock_hx711.hpp"


class ScaleManagerTest : public ::testing::Test
{
protected:
    MockScaleSensor m_mockScaleSensor;

    ScaleManager m_scaleManager{m_mockScaleSensor};

    void SetUp() override{
        m_mockScaleSensor.useRandomData(); // Use random data from a real scale sensor
        m_mockScaleSensor.setWaterLevelRawVal(0.0f); // Set water level to 0 for testing
        m_mockScaleSensor.setEmptyBottleRawVal(0.0f); 
        m_mockScaleSensor.setBottleHolderRawVal(0.0f);
        // m_mockScaleSensor.setEmptyBottleRawVal(EMPTY_BOTTLE_RAW_VAL);
        // m_mockScaleSensor.setBottleHolderRawVal(EmptyBottleHolderRawVal);
    }
    
};

TEST_F(ScaleManagerTest, Measure_Weight_in_Grams)
{
    float rawValue500mlWater = 6542.1f; // Simulate a weight of 500 grams of water (only the water weight, no bottle).
    float deltaGrams = 500.0f;
    float tareRaw = EMPTY_BOTTLE_RAW_VAL + BOTTLE_HOLDER_RAW_VAL; // Simulate the tare value (weight of the empty bottle).
   
    float scaleFactor =   deltaGrams/rawValue500mlWater;
     m_scaleManager.setTare(tareRaw); 
    m_scaleManager.setScaleGramFactor(scaleFactor);

    m_mockScaleSensor.setMockRawData(tareRaw + rawValue500mlWater); // Simulate the sensor reading with the weight of 500 grams of water.
    EXPECT_NEAR(m_scaleManager.measureInGrams(), deltaGrams, 1.0f); // Check if the measured weight is approximately 500 grams +-1g
}

TEST_F(ScaleManagerTest, Measure_Quantity)
{
    float tareRaw = EMPTY_BOTTLE_RAW_VAL + BOTTLE_HOLDER_RAW_VAL;
    float rawValue500mlWater = 6542.1f; // Simulate a weight of 500 ml (≈ 500 grams)of water (only the water weight, no bottle).
    float deltaMilliliters = 500.0f;   
    
    m_scaleManager.setTare(tareRaw);
    float unitFactor = deltaMilliliters/rawValue500mlWater;
    m_scaleManager.setUnitFactor(unitFactor);
    
    m_mockScaleSensor.setMockRawData( tareRaw + rawValue500mlWater); // Simulate a weight of 500 ml of water. Sould be > than tareRaw since a bottle with water is heavier than an empty one.
    EXPECT_NEAR(m_scaleManager.measureQuantity(), deltaMilliliters, 1.0f); // Check if the measured weight is approximately 500 ml +-1ml
}

TEST_F(ScaleManagerTest, Measure_In_Grams)
{
    float rawValue = 9890.0f; // Should be somthing around 11g with the SCALE_GRAM_FACTOR = 0.00228429031253f; 
    float scaleFactor = SCALE_GRAM_FACTOR;
    m_mockScaleSensor.setMockRawData(rawValue);
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    EXPECT_EQ(m_scaleManager.measureInGrams(), rawValue * scaleFactor);
}

TEST_F(ScaleManagerTest, Tare_Test)
{
    m_mockScaleSensor.useRandomData();
    float tareValue = m_scaleManager.measureRawNoTare();
    m_mockScaleSensor.setMockRawData(tareValue);//Disables also the usage of random data
    m_scaleManager.tare(10);
    // EXPECT_EQ(m_scaleManager.getTare(), tareValue);
    EXPECT_FLOAT_EQ(m_scaleManager.getTare(), tareValue);
    EXPECT_EQ(m_scaleManager.measureRawNoTare(), tareValue);
}

TEST_F(ScaleManagerTest, Negative_Weight_Detection){
    m_mockScaleSensor.setMockRawData(-500.0f);//Simulate a lifted weight for example a bottle
    EXPECT_EQ(m_scaleManager.measureInGrams(), -500.0f * m_scaleManager.getScaleGramFactor());
}