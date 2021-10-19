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
#include <sstream>

enum AssetType
{
    CRYPTO,
    STOCK
};

class Asset 
{
    public:
        Asset(AssetType type, const std::string &currency);
        void callAPI();
        float getExchangeRate();
        std::string getCurrency();
        
    private:
        const std::string _currency;
        const std::string _apiKey; 
        const std::string _site;
        const AssetType _type;
        const std::string to_currency = "USD";

        Poco::URI _uri;
        std::string _path;
        std::string _function;
        float _rate;
};
#endif