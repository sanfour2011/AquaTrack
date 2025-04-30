#pragma once

#include "ScaleManager.hpp"
#include "IScaleSensor.hpp"
#include "EventDispatcher.hpp"
#include "RTCManager.h"
#include "WaterTrackerData.hpp"

class WaterTracker
{
public:
    WaterTracker( EventDispatcher &dispatcher);
    void begin(); // z. B. lade EEPROM-Werte etc.
    void updateConsumption(float currentWeight);
    // todo: void undoLastAction();
    void interpretWeight(float newWeight);
    float getDailyConsumption() const;
    int getRefillCount() const;
    void resetDailyConsumption();
    void setAveragingCount(uint_fast8_t count);
    uint_fast8_t getAveragingCount() const;
    void setMaxCapacity(float value);
    float getMaxCapacity() const;
    

private:
    uint_fast8_t m_averagingCount = 10;
    WaterTrackerData m_data;
    bool isNewDay();
    bool isRefilled(float currentWeight);
    void detectDrink(float currentWeight);
    EventDispatcher &m_eventDispatcher;
};