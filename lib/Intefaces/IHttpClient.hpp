#pragma once
#include <string>
#include <vector>

class IHttpClient{
    public:
    virtual bool connect(const std::string& url)=0;
    virtual std::string get(const std::string& path)=0; 
    virtual bool sendPost(const std::string& path, const std::string& data)=0;
    virtual void setHeaders(const std::vector<std::pair<std::string, std::string>>& headers)=0;
    virtual ~IHttpClient() = default;

};