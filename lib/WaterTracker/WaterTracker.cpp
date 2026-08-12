#include "WaterTracker.hpp"
#include "WaterTrackerEvents.hpp"
#include <ctime>

WaterTracker::WaterTracker(EventDispatcher<float> &dispatcher)
    : m_eventDispatcher(dispatcher)
{
    // m_data.reset(); ich glaube hier ein reset zu machen ist nicht sinnvoll sagen wir mal nach einem reboot wird oder muss ja eh neu geladen werden aus einer quelle
}

void WaterTracker::begin()
{
    // Hier könnten EEPROM-Werte geladen werden
    // Beispiel: m_data = loadFromEEPROM();
}

void WaterTracker::interpretWeight(float newWeight)
{

    if (newWeight < 5.0f) // Gewicht ~0g -> Flasche wurde von der Waage genommen
    {
        m_eventDispatcher.dispatch(WaterTrackerEvents::ContainerRemoved, newWeight);
        return;
    }

    if (newWeight > m_data.getLastWeight())
    {
        m_data.setRefillCount(m_data.getRefillCount() + 1);
        m_data.setFullWeight(newWeight);
        m_data.setLastWeight(newWeight);
        m_eventDispatcher.dispatch(WaterTrackerEvents::ContainerRefilled, newWeight);
        return;
    }

    if (m_data.getLastWeight() > newWeight) // Water Consumed
    {
        m_eventDispatcher.dispatch(WaterTrackerEvents::ConsumedMl, newWeight);
        updateConsumption(newWeight);
        return;
    }
}

void WaterTracker::updateConsumption(float newWeight)
{
    if (isNewDay())
        m_data.reset();

    float ml_Consumed = m_data.getPreviousConsumption() - newWeight;
    float remainingMl = m_data.getFullWeight() - ml_Consumed;

    m_data.setLastWeight(newWeight);
    m_data.incrementDrinkCount();
    m_data.setPreviousConsumption(ml_Consumed);
    m_data.setDailyConsumption(m_data.getDailyConsumption() + ml_Consumed);

    m_eventDispatcher.dispatch("Consumed_ml", ml_Consumed);
    m_eventDispatcher.dispatch("Remaining", remainingMl);
    m_eventDispatcher.dispatch("Daily_Consumption", m_data.getDailyConsumption());
    m_eventDispatcher.dispatch("Drink_Count", m_data.getDrinkCount());
}

bool WaterTracker::isNewDay()
{
    return false;
}

float WaterTracker::getDailyConsumption() const
{
    return m_data.getDailyConsumption();
}

int WaterTracker::getRefillCount() const
{
    return m_data.getRefillCount();
}

void WaterTracker::resetDailyConsumption()
{
    m_data.resetDailyConsumption();
}

void WaterTracker::setAveragingCount(uint_fast8_t count)
{
    m_averagingCount = count;
}

uint_fast8_t WaterTracker::getAveragingCount() const
{
    return m_averagingCount;
}

void WaterTracker::setMaxCapacity(float maxCapacity)
{
    m_data.setMaxCapacity(maxCapacity);
}

float WaterTracker::getMaxCapacity() const
{
    return m_data.getMaxCapacity();
}
