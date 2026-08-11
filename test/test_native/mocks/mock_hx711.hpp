#pragma once

// Other mocking method if gtest is not used!
#include "IScaleSensor.hpp"
#include <random>
#include <vector>
#include <random>

constexpr float EMPTY_BOTTLE_RAW_VAL = 245108.08f;
constexpr float BOTTLE_HOLDER_RAW_VAL = 14102.0f;
constexpr float SCALE_GRAM_FACTOR = 0.00228429031253f; // Value from real physical sensor with holder

class MockScaleSensor : public IScaleSensor
{
public:
    bool UseFixedValue = false;

    MockScaleSensor() : rng(std::random_device{}()) {}

    ~MockScaleSensor() override = default;
    
    void useRandomData()
    {
        UseFixedValue = false;
    }

    float readRawValue() override
    {
        if (UseFixedValue)
        {
            return m_fixedValue;
        }
        else
        {
            uint_fast32_t randomIndex = rng() % dataset.size();
            return dataset[randomIndex]+m_bottleHolder+m_emptyBottle+m_waterWeight;
        }
    }

    bool isReady() override
    {
        // Simulate a random readiness state for testing purposes like real hadware (I ran into issues because of this).
        return rng() % 2 == 0;
    }

    void setMockRawData(float rawData)
    {
        m_fixedValue = rawData;
        UseFixedValue = true;
    }

    void setWaterLevelRawVal(float waterLevel)
    {
        m_waterWeight = waterLevel;
    }

    void setWaterWeight(float waterWeight)
    {
        m_waterWeight = waterWeight;
    }
    void setEmptyBottleRawVal(float emptyBottleWeight)
    {
        m_emptyBottle = emptyBottleWeight;
    }
    void setBottleHolderRawVal(float bottleHolderWeight)
    {
        m_bottleHolder = bottleHolderWeight;
    }

private:
    float m_fixedValue = 1000.0f;
    float m_mockScaleFactor = 1.0f;
    float m_bottleHolder = 14102.0f; // the value change wehne the bottle holder plate mountet on the load cell
    float m_emptyBottle = 245108.08f; // the value change when the empty bottle is putted on the plate. (it was an 0,75L Glass Ensiger Sport classic bottle)
    float m_waterWeight = 0.0f; // the value change when the water is putted in the bottle.
    
    std::mt19937 rng;
    // Predefined dataset of float values to simulate the sensor data. Just empty sensor (only load cell) nothing an top
    const std::vector<float> dataset = {
        -38371, -38355, -38354, -38352, -38349, -38348, -38346, -38345, -38343, -38342,
        -38341, -38338, -38337, -38336, -38335, -38334, -38333, -38332, -38331, -38330,
        -38329, -38328, -38327, -38326, -38325, -38324, -38323, -38322, -38321, -38320,
        -38319, -38318, -38317, -38316, -38315, -38314, -38313, -38312, -38311, -38310,
        -38309, -38308, -38307, -38306, -38305, -38304, -38303, -38302, -38301, -38300,
        -38299, -38298, -38297, -38296, -38295, -38294, -38293, -38292, -38291, -38290,
        -38289, -38288, -38287, -38286, -38285, -38284, -38283, -38282, -38281, -38280,
        -38279, -38278, -38277, -38276, -38275, -38274, -38273, -38272, -38271, -38270,
        -38269, -38268, -38267, -38266, -38265, -38264, -38263, -38262, -38261, -38260,
        -38259, -38258, -38257, -38256, -38255, -38254, -38253, -38252, -38251, -38250,
        -38249, -38248, -38247, -38246, -38244, -38243, -38242, -38241, -38240, -38239,
        -38238, -38237, -38236, -38235, -38234, -38231, -38230, -38229, -38228, -38227,
        -38221, -38218, -38216, -38213, -38212, -38210, -38209, -38205, -38200};
};