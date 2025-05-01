#pragma once


// Avoid using std::string here as it allocates memory on the heap, 
// which can be expensive and inefficient on some microcontrollers.
namespace WaterTrackerEvents {
    constexpr const char* ContainerRemoved     = "Container_Removed";
    constexpr const char* ContainerRefilled    = "Container_Refilled";
    constexpr const char* WaterConsumed        = "Water_Consumed";
    constexpr const char* ConsumedMl           = "Consumed_ml";
    constexpr const char* Remaining            = "Remaining";
    constexpr const char* DailyConsumption     = "Daily_Consumption";
    constexpr const char* DrinkCount           = "Drink_Count";
    constexpr const char* RefillDetected       = "Refill";
    constexpr const char* ErrorWaterTracker    = "Water_Tracker_Error";
}
