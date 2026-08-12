#include "ESPHttpClient.hpp"

bool ESPHttpClient::connect(const std::string &url)
{
    m_client.begin(url.c_str());
    return true;
}

std::string ESPHttpClient::get(const std::string &path)
{
    return std::string();
}

bool ESPHttpClient::sendPost(const std::string &path, const std::string &data)
{
    return false;
}

void ESPHttpClient::setHeaders(const std::vector<std::pair<std::string, std::string>> &headers)
{
}
