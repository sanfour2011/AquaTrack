#include <gtest/gtest.h>
#include "WaterTracker.hpp"
#include "WaterTrackerEvents.hpp"
#include "ScaleManager.hpp"
#include "EventDispatcher.hpp"
#include "../mocks/mock_hx711.hpp"

class WaterTrackerTest : public ::testing::Test
{
protected:
    MockScaleSensor m_mockScaleSensor;
    EventDispatcher<float> m_eventDispatcher;
    WaterTrackerData m_data;
    ScaleManager m_scaleManager{m_mockScaleSensor};
    WaterTracker m_tracker{m_eventDispatcher};

    void SetUp() override
    {
        m_mockScaleSensor.useRandomData();           // Use random data from a real scale sensor
        m_mockScaleSensor.setWaterLevelRawVal(0.0f); // Set water level to 0 for testing
        m_mockScaleSensor.setEmptyBottleRawVal(EMPTY_BOTTLE_RAW_VAL);
        m_mockScaleSensor.setBottleHolderRawVal(BOTTLE_HOLDER_RAW_VAL);
        m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    }
};

TEST_F(WaterTrackerTest, Measure_Empty_Bottle_Weight)
{
    m_scaleManager.setUnitFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(2);
    EXPECT_NEAR(m_scaleManager.measureInGrams(), 0.0f, 1.0f); // Check if the measured weight is approximately 0 grams +-1g
}

TEST_F(WaterTrackerTest, Detect_Lifted_Empty_Bottle)
{
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);
    float tare = m_scaleManager.getTare();
    m_mockScaleSensor.setMockRawData(tare - EMPTY_BOTTLE_RAW_VAL);

    m_eventDispatcher.addListener(WaterTrackerEvents::ContainerRemoved, [tare](float weight)
                                  {
                                      EXPECT_NEAR(weight, (-EMPTY_BOTTLE_RAW_VAL) * SCALE_GRAM_FACTOR, 1.0f); // Check if the weight is approximately equal to tare - empty bottle weight
                                  });

    m_tracker.interpretWeight(m_scaleManager.measureInGrams()); // Call the method to interpret the weight
}

TEST_F(WaterTrackerTest, Detect_LiftedPartiallyFilledBottle)
{
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);
    float tare = m_scaleManager.getTare();

    m_mockScaleSensor.setMockRawData(tare + 100000.0f); // Simulate a refill
    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    m_mockScaleSensor.setMockRawData(tare - EMPTY_BOTTLE_RAW_VAL);

    bool removedFired = false;
    m_eventDispatcher.addListener(WaterTrackerEvents::ContainerRemoved, [&removedFired](float weight)
                                  { removedFired = true; });

    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    EXPECT_TRUE(removedFired);
}

TEST_F(WaterTrackerTest, RefillCompletelyEmptyBottle)
{
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);

    m_mockScaleSensor.setMockRawData(m_scaleManager.getTare() + (750.0f / SCALE_GRAM_FACTOR));

    bool refillFired = false;
    float receivedWeight = 0.0f;
    m_eventDispatcher.addListener(WaterTrackerEvents::ContainerRefilled, [&refillFired, &receivedWeight](float weight)
                                  {
        refillFired = true;
        receivedWeight = weight; });

    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    EXPECT_TRUE(refillFired);
    EXPECT_NEAR(receivedWeight, 750.0f, 1.0f);
    EXPECT_EQ(m_tracker.getRefillCount(), 1);
}

TEST_F(WaterTrackerTest, RefillPartiallyFilledBottle)
{
    // todo: Unterscheidung von einem Partielles Nachfüllen und einem full Refill unterscheiden.
}

TEST_F(WaterTrackerTest, DrinkUntilBottleIsEmpty)
{
    const float fullBottle = 750.0; // in g
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);
    float tare = m_scaleManager.getTare();

//put a full bottle
    m_mockScaleSensor.setMockRawData(tare + (fullBottle / SCALE_GRAM_FACTOR));
    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    // drinking entire bottle
    bool containerEmptyFired = false;
    bool consumedFired = false;
    m_eventDispatcher.addListener(WaterTrackerEvents::ContainerEmpty, [&containerEmptyFired](float weight)
                                  { containerEmptyFired = true; });
    m_eventDispatcher.addListener(WaterTrackerEvents::ConsumedMl, [&consumedFired](float weight)
                                  { consumedFired = true; });

    m_mockScaleSensor.setMockRawData(tare); // ~0g -> an empty bottle puted back
    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    EXPECT_TRUE(containerEmptyFired);
    EXPECT_FALSE(consumedFired); 
}


TEST_F(WaterTrackerTest, DrinkUntilBottleIsPartiallyFilled)
{
    const float consumedML = 350.0; // in g
    const float fullBottle = 750.0; // in  g
    m_scaleManager.setScaleGramFactor(SCALE_GRAM_FACTOR);
    m_scaleManager.tare(1);
    float tare = m_scaleManager.getTare();

    // putting a full bottle
    m_mockScaleSensor.setMockRawData(tare + (fullBottle / SCALE_GRAM_FACTOR));
    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    // dring some water, left water weight and above empty
    bool consumedFired = false;
    float receivedWeight = 0.0f;
    m_eventDispatcher.addListener(WaterTrackerEvents::ConsumedMl, [&consumedFired, &receivedWeight](float weight)
                                  {
        consumedFired = true;
        receivedWeight = weight; });

    m_mockScaleSensor.setMockRawData(tare + (fullBottle - consumedML) / SCALE_GRAM_FACTOR);
    m_tracker.interpretWeight(m_scaleManager.measureInGrams());

    EXPECT_TRUE(consumedFired);
    EXPECT_NEAR(receivedWeight, consumedML, 1.0f);
    EXPECT_GT(m_tracker.getDailyConsumption(), 0.0f); // es wurde tatsächlich Konsum verbucht
}

TEST_F(WaterTrackerTest, HandleInvalidScaleReadings)
{
    bool errorFired = false;
    m_eventDispatcher.addListener(WaterTrackerEvents::ErrorWaterTracker, [&errorFired](float weight)
                                  { errorFired = true; });

    m_tracker.interpretWeight(-std::numeric_limits<float>::max());

    EXPECT_TRUE(errorFired);
}