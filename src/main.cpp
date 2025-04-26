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
#define SCALE_AVGERAGE 32
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
    scaleManager.setScaleGramFactor(1.0f);
    eventDispatcher.addListener("Raw_Value", OnRawValue);
    eventDispatcher.addListener("weight", OnWeight);
    

    pinMode(LED_BUILTIN, OUTPUT);
}
float filteredWeight = 0.0f; // Startwert = 0.0 (leere Waage)

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    float rawValue = scaleManager.measureRawNoTare();
    float weight = 0;
    weight = scaleManager.measureQuantity(); // toDo the average should be done in the scaleManager
    filteredWeight = 0.9f * filteredWeight + 0.1f * weight;  // Filterung
    Serial.print(">Filtered_Weight: ");
    Serial.println(filteredWeight);
    eventDispatcher.dispatch("Raw_Value", rawValue);
    eventDispatcher.dispatch("weight", weight);

    digitalWrite(LED_BUILTIN, LOW);
    //delay(100);
}

void OnRawValue(float rawValue)
{
    Serial.print(">Raw Value: ");
    Serial.println(rawValue);
}

void OnWeight(float weight)
{
    Serial.print(">Weight: ");
    Serial.println(weight);
    waterTracker.updateConsumption(weight);
}
#else

int main()
{
    return 0;
}

#endif