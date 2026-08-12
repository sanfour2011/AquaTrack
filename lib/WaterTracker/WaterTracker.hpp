#pragma once


#include "RTCManager.h"
#include "WaterTrackerData.hpp"
#include <cstdint>
#include "EventDispatcher.hpp"
class WaterTracker
{
public:
    WaterTracker( EventDispatcher<float> &dispatcher);
    void begin(); // z. B. lade EEPROM-Werte etc. Daten sollte nach Power-Off noch vorhanden sein
    
    // todo: void undoLastAction();
    void interpretWeight(float newWeight);
    float getDailyConsumption() const;
    int getRefillCount() const;
    void resetDailyConsumption();
    uint_fast8_t getAveragingCount() const;
    void setAveragingCount(uint_fast8_t count);
    void setMaxCapacity(float value);
    float getMaxCapacity() const;
    void setImplausibleWeightThreshold(float implaWeight);
    float getImplausibleWeightThreshold();
    
    
    private:
    uint_fast8_t m_averagingCount = 10;
    float m_implausibleWeightThreshold = 5000.0; // max that the scale is rated for in g
    WaterTrackerData m_data;
    void updateConsumption(float currentWeight);
    bool isNewDay();
    bool isRefilled(float currentWeight);
    void detectDrink(float currentWeight);
    EventDispatcher<float> &m_eventDispatcher;    
};