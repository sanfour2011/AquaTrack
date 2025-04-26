#pragma once

#include <string>
#include <time.h>  

class RTCManager {
public:
    RTCManager(); 
    std::string getTime(); 
    void setTime(int hour, int minute, int second, int day, int month, int year);  

private:
    void initTime();  // Initialisiert die interne RTC
};
