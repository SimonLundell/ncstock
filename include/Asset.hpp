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

class Asset 
{
    public:
        Asset(const std::string &currency);
        void callAPI();
        float getExchangeRate(const std::string &to_currency);
        std::string getCurrency();
        
    private:
        const std::string _currency;
        const std::string _apiKey; 
        const std::string _site;

        Poco::URI _uri;
        std::string _path;

        std::string _function;
        float _rate;
};
#endif