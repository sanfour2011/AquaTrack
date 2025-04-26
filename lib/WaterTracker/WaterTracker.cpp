#include "WaterTracker.hpp"

WaterTracker::WaterTracker(ScaleManager &scale, EventDispatcher &dispatcher)
    : m_scaleManager(scale), m_eventDispatcher(dispatcher)
{
    // m_data.reset(); ich glaube hier ein reset zu machen ist nicht sinnvoll sagen wir mal nach einem reboot wird oder muss ja eh neu geladen werden aus einer quelle
}

void WaterTracker::onWeightChanged()
{
    float currentWeight = m_scaleManager.measureRawAverage(m_averagingCount);

    if (currentWeight < 0) // currentWeight sollte = -tare sein
    {
        // Container removed
        m_eventDispatcher.dispatch("ContainerRemoved", currentWeight);
        return;
    }

    if (m_data.getLastWeight() < currentWeight) // Refill
    {
        float addedWater = currentWeight - m_data.getLastWeight();
        // m_data.setFullWeight(currentWeight); // sollte man einmalig machen können? zum beispiel neue Flasche?
        m_eventDispatcher.dispatch("ContainerRefilled", currentWeight);
        m_data.setLastWeight(currentWeight);

        return;
    }

    if (m_data.getLastWeight() > currentWeight)//Water Consumed
    {   m_eventDispatcher.dispatch("WaterConsumed", currentWeight);
        updateConsumption(currentWeight);
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
    m_eventDispatcher.dispatch("DailyConsumption", m_data.getDailyConsumption());
    m_eventDispatcher.dispatch("DrinkCount", m_data.getDrinkCount());
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
