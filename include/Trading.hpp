#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

class TradingInfo
{
    public:
        TradingInfo();
        void callAPI(const std::string &asset);
        void getExchangeRate(const std::string &asset, const std::string &to_currency);
        
    private:
        std::unordered_map<std::string, int> assets;

        const std::string _apiKey; 
        const std::string _site;
};
#endif