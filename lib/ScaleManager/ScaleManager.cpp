#include "ScaleManager.hpp"
#include <limits>

float ScaleManager::measureRawAverage(uint_fast8_t times)
{
    float sum = 0.0f;
    for (uint_fast8_t i = 0; i < times; ++i)
    {
        sum += m_sensor.readRawValue();
    }
    return sum / times;
}

float ScaleManager::measureRawNoTare(uint_fast8_t times)
{
    float average = 0.0f;
    for (uint_fast8_t i = 0; i < times; ++i)
    {
        average += m_sensor.readRawValue()/times;
    }
    return average;
}

bool ScaleManager::isSensorReady()
{
    return m_sensor.isReady();
}   

float ScaleManager::measureInGrams(uint_fast8_t times)
{
    float average = 0.0f;
    for(uint_fast8_t i = 0; i < times; ++i)
    {
        average += ((m_sensor.readRawValue() - m_tare) * m_scaleGramFactor) / times; 
    }
    return average;
}

float ScaleManager::measureQuantity(uint_fast8_t times)
{
    float average = 0.0f;
    for(uint_fast8_t i = 0; i < times; ++i)
    {
        average += ((m_sensor.readRawValue() - m_tare) * m_unitFactor) / times; 
    }
    return average;
}

void ScaleManager::tare(uint_fast8_t times)
{  
    m_tare = measureRawNoTare(times); //No Tare to "ReTare" the scale
}

void ScaleManager::setTare(float tare)
{
    m_tare = tare;
}

float ScaleManager::getTare()
{
    return m_tare;
}
void ScaleManager::setUnitFactor(float factor)
{
    m_unitFactor = factor;
}

void ScaleManager::setScaleGramFactor(float factor)
{
    m_scaleGramFactor = factor;
}

float ScaleManager::getScaleGramFactor()
{
    return m_scaleGramFactor;
}
