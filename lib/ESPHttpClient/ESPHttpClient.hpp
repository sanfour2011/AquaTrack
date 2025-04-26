#pragma once
#include "IHttpClient.hpp"
#include <WiFi.h>
#include <HTTPClient.h>

class ESPHtttpClient : public IHttpClient
{
public:
    bool connect(const std::string &url) override;

private:
    HTTPClient m_client;
};