#pragma once
#include "IHttpClient.hpp"
#include <WiFi.h>
#include <HTTPClient.h>

class ESPHttpClient : public IHttpClient
{
public:
    bool connect(const std::string &url) override;
     std::string get(const std::string& path) override; 
     bool sendPost(const std::string& path, const std::string& data) override;
     void setHeaders(const std::vector<std::pair<std::string, std::string>>& headers) override;

private:
    HTTPClient m_client;
};