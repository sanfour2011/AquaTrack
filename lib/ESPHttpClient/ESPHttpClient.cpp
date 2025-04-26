#include "ESPHttpClient.hpp"

bool ESPHtttpClient::connect(const std::string &url)
{
    m_client.begin(url.c_str());
    return true;
}