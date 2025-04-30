#include <gtest/gtest.h>
#include "WaterTracker.hpp"
#include "ScaleManager.hpp"
#include "EventDispatcher.hpp"
#include "../mocks/mock_hx711.hpp"

class WaterTrackerTest : public ::testing::Test
{
protected:
    MockScaleSensor m_mockScaleSensor;
    EventDispatcher m_eventDispatcher;
    WaterTrackerData m_data;
    ScaleManager m_scaleManager{m_mockScaleSensor};
    WaterTracker m_tracker{m_scaleManager, m_eventDispatcher};

    void SetUp() override
    {
        m_mockScaleSensor.useRandomData();           // Use random data from a real scale sensor
        m_mockScaleSensor.setWaterLevelRawVal(0.0f); // Set water level to 0 for testing
        m_mockScaleSensor.setEmptyBottleRawVal(EMPTY_BOTTLE_RAW_VAL);
        m_mockScaleSensor.setBottleHolderRawVal(BOTTLE_HOLDER_RAW_VAL);        
        m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
        
    }
};

TEST_F(WaterTrackerTest, MeasureEmptyBottleWeight)
{
    m_scaleManager.setUnitFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(2);
    EXPECT_NEAR(m_scaleManager.measureInGrams(), 0.0f, 1.0f); // Check if the measured weight is approximately 0 grams +-1g
}

TEST_F(WaterTrackerTest, DetectLiftedEmptyBottle)
{
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);
    float tare = m_scaleManager.getTare();
    m_mockScaleSensor.setMockRawData(tare - EMPTY_BOTTLE_RAW_VAL); 

    m_tracker.updateConsumption(m_scaleManager.measureInGrams());
    
}

TEST_F(WaterTrackerTest, DetectLiftedPartiallyFilledBottle)
{

}

TEST_F(WaterTrackerTest, RefillCompletelyEmptyBottle)
{
}

TEST_F(WaterTrackerTest, RefillPartiallyFilledBottle)
{
}

TEST_F(WaterTrackerTest, DrinkUntilBottleIsEmpty)
{
}

TEST_F(WaterTrackerTest, DrinkUntilBottleIsPartiallyFilled)
{
}
TEST_F(WaterTrackerTest, HandleInvalidScaleReadings)
{
    m_mockScaleSensor.setWaterLevelRawVal(-1.0f); // Simulate invalid scale reading
    EXPECT_THROW(m_scaleManager.measureInGrams(), std::runtime_error); // Expect an exception for invalid readings
}