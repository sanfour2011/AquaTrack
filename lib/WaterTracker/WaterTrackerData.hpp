#pragma once

class WaterTrackerData
{
public:

    float getDailyConsumption() const { return m_dailyConsumption; }
    void setDailyConsumption(float value) { m_dailyConsumption = value; }

    int getRefillCount() const { return m_refillCount; }
    void setRefillCount(int value) { m_refillCount = value; }

    int getDrinkCount() const { return m_drinkCount; }
    void setDrinkCount(int value) { m_drinkCount = value; }
    void incrementDrinkCount() { m_drinkCount++; }

    float getLastWeight() const { return m_lastWeight; }
    void setLastWeight(float value) { m_lastWeight = value; }

    float getPreviousConsumption() const { return m_previousConsumption; }
    void setPreviousConsumption(float value) { m_previousConsumption = value; }

    float getMaxCapacity() const { return m_maxCapacity; }
    void setMaxCapacity(float value) { m_maxCapacity = value; }

    float getFullWeight() const { return m_fullWeight; }
    void setFullWeight(float value) { m_fullWeight = value; }
    void setContainerRemovedThreshold(float removedThr);
    float getContainerRemovedThreshold();

    void resetDailyConsumption() {m_dailyConsumption = 0.0f;};

    void reset()
    {
        m_dailyConsumption = 0.0f;
        m_refillCount = 0;
        m_drinkCount = 0;
        m_lastWeight = 0.0f;
        m_previousConsumption = 0.0f;
        m_maxCapacity = 0.0f;
        m_fullWeight = 0.0f;
    }

private:
    float m_dailyConsumption = 0.0f;
    int m_refillCount = 0;
    int m_drinkCount = 0;
    float m_lastWeight = 0.0f;
    float m_previousConsumption = 0.0f;
    float m_maxCapacity = 0.0f;
    float m_fullWeight = 0.0f;
};