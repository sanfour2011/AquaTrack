#pragma once
#include "IHttpClient.hpp"

class GarminUploader{
    public:
    GarminUploader(IHttpClient& client):m_client(client){};
    bool uploadData(const std::string& data);

    private:
    IHttpClient& m_client;
};


