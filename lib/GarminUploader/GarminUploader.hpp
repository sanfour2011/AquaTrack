#pragma once
#include "IHttpClient.hpp"


  // ToDo: Garmin hat keine öffentliche API für normale Nuzer, nur für Fimen :(
    // aktuell nur über Web-Scraping möglich, aber dieser ab dieser ab und zu 
    // Captcha/Bot-Checker blockiert das noch. Leider bis dies gelöst ist -> Werte manuell in der Garmin App eintragen
class GarminUploader{
    public:
    GarminUploader(IHttpClient& client):m_client(client){};
    bool uploadData(const std::string& data);

    private:
    IHttpClient& m_client;
};


