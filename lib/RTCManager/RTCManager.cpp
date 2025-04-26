#include "RTCManager.h"

#if defined(ARDUINO)
    #include <Arduino.h>
    void RTCManager::initTime() {
        // Setze die Zeit von der Kompilierzeit des Mikrokontrollers (nur beim ersten Start)
        configTime(0, 0, "pool.ntp.org");  // Beispiel: Zeit von einem NTP-Server setzen
    }
    
    std::string RTCManager::getTime() {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
            return "Fehler bei der Zeitabfrage!";
        }
    
        // Formatiere die Zeit zu einem lesbaren String
        char buffer[30];
        strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%Y", &timeinfo);
        
        return std::string(buffer);
    }
    
    void RTCManager::setTime(int hour, int minute, int second, int day, int month, int year) {
        struct tm timeinfo = {0};
        
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        timeinfo.tm_sec = second;
        timeinfo.tm_mday = day;
        timeinfo.tm_mon = month - 1;  // Monate beginnen bei 0
        timeinfo.tm_year = year - 1900;  // Jahre ab 1900
        
        // Setze die Zeit
        time_t rawtime = mktime(&timeinfo);
        struct timeval tv = { rawtime, 0 };
        settimeofday(&tv, NULL);
    }
    

#endif // ARDUINO
RTCManager::RTCManager() {
    // Initialisiere die interne RTC, wenn der Mikrocontroller gestartet wird
    initTime();
}


