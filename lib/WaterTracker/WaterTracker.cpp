#include "WaterTracker.hpp"
#include "waterTrackerEvents.hpp"

WaterTracker::WaterTracker(EventDispatcher &dispatcher)
    :  m_eventDispatcher(dispatcher)
{
    // m_data.reset(); ich glaube hier ein reset zu machen ist nicht sinnvoll sagen wir mal nach einem reboot wird oder muss ja eh neu geladen werden aus einer quelle
}

void WaterTracker::interpretWeight(float newWeight)
{

    if (newWeight < 0) // currentWeight sollte = -tare sein
    {
        // Container removed
        m_eventDispatcher.dispatch(WaterTrackerEvents::ErrorWaterTracker, newWeight);
        return;
    }

    if (m_data.getLastWeight() < newWeight) // Refill
    {
        float addedWater = currentWeight - m_data.getLastWeight();
        // m_data.setFullWeight(currentWeight); // sollte man einmalig machen können? zum beispiel neue Flasche?
        m_eventDispatcher.dispatch("Container_Refilled", newWeight);
        m_data.setLastWeight(newWeight);

        return;
    }

    if (m_data.getLastWeight() > newWeight)//Water Consumed
    {   m_eventDispatcher.dispatch("Water_Consumed", newWeight);
        updateConsumption(newWeight);
        return;
    }
}

void WaterTracker::updateConsumption(float currentWeight)
{
    if (isNewDay())
        m_data.reset();

    float ml_Consumed = m_data.getPreviousConsumption() - m_scaleManager.measureQuantity();
    float remainingMl = m_data.getFullWeight() - ml_Consumed;

    m_data.setLastWeight(currentWeight);
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

bool WaterTracker::isRefilled(float currentWeight)
{
    if (currentWeight > m_data.getLastWeight())
    {
        m_data.setRefillCount(m_data.getRefillCount() + 1);
        m_data.setFullWeight(currentWeight);
        m_eventDispatcher.dispatch("Refill", currentWeight);
        return true;
    }
    return false;
}
