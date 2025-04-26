#pragma once

#include "ScaleManager.hpp"
#include "IScaleSensor.hpp"
#include "EventDispatcher.hpp"
#include "RTCManager.h"
#include "WaterTrackerData.hpp"

class WaterTracker
{
public:
    WaterTracker(ScaleManager &scale, EventDispatcher &dispatcher);
    void updateConsumption(float currentWeight);
    // todo: void undoLastAction();
    void onWeightChanged();
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
    ScaleManager &m_scaleManager;
    EventDispatcher &m_eventDispatcher;
};