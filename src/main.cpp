#if defined(ARDUINO)
#include <Arduino.h>
#include "EventDispatcher.hpp"
#include "HX711Sensor.hpp"
#include "ScaleManager.hpp"
#include "WaterTracker.hpp"
//#include "GarminUploader.hpp"
//#include "DataLogger.hpp"
//#include "CommandProcessor.hpp"



#undef LED_BUILTIN
#define LED_BUILTIN 8

#include "HX711.h"
#define SCALE_AVGERAGE 64
#define DOUT 1
#define CLK 0

EventDispatcher eventDispatcher;
void OnRawValue(float rawValue);
void OnWeight(float weight);

HX711Sensor hx711(DOUT, CLK);
ScaleManager scaleManager(hx711);
WaterTracker waterTracker(scaleManager, eventDispatcher);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    delay(2000); // wait for serial monitor to open
    scaleManager.tare(SCALE_AVGERAGE); 
    Serial.print("Tare: ");
    Serial.println(scaleManager.getTare());
    scaleManager.setScaleGramFactor(0.00228429031253);
    Serial.print("ScaleFactor: ");
    Serial.println(scaleManager.getScaleGramFactor(),10);
    
    eventDispatcher.addListener("Raw_Value", OnRawValue);
    eventDispatcher.addListener("weight", OnWeight);
    

    pinMode(LED_BUILTIN, OUTPUT);
}
float filteredWeight = 0.0f; 
float filteredRawValue = 0.0f; 
void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    float rawValue = scaleManager.measureRawAverage(1);
    float weight = 0;
    weight = scaleManager.measureInGrams(10); // toDo the average should be done in the scaleManager

    eventDispatcher.dispatch("Raw_Value", rawValue);
    eventDispatcher.dispatch("weight", weight);
    digitalWrite(LED_BUILTIN, LOW);
    //delay(100);
}

void OnRawValue(float rawValue)
{
    Serial.print(">Raw_Value: ");
    Serial.println(rawValue);
    filteredRawValue = 0.8f * filteredRawValue + 0.2f * rawValue;  // Filterung
    Serial.print(">Filtered_Raw_Value: ");
    Serial.println(filteredRawValue);
}

void OnWeight(float weight)
{
    Serial.print(">Weight: ");
    Serial.println(weight);
    waterTracker.updateConsumption(weight);

    filteredWeight = 0.8f * filteredWeight + 0.2f * weight;  // Filterung
    Serial.print(">Filtered_Weight: ");
    Serial.println(filteredWeight);
}


#else

int main()
{
    return 0;
}

#endif