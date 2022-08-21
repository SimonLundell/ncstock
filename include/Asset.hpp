#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <future>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>



enum AssetType
{
    CRYPTO,
    STOCK
};

class Asset 
{
    public:
        // Constructor
        Asset(AssetType type, const std::string &asset_name);

        // Member functions
        void establishSession();
        void queryExchangeRate();
        void callAPI();
        void parseResponse(const std::string& response_string);

        // Getters, without new API call
        std::string getCurrency() const;
        std::string getCloseRate() const;
        std::string getOpenRate() const;
        std::string getHighRate() const;
        std::string getLowRate() const;
        std::string getVolume() const;
        std::string getAssetName() const;
        std::string getTime() const;
        AssetType getType() const;

    private:
        // API call
        const std::string _assetName;
        const std::string _apiKey; 
        const std::string _site;
        const AssetType _type;
        
        // API response
        std::string _query_time;
        std::string _open_rate;
        std::string _high_rate;
        std::string _low_rate;
        std::string _close_rate;
        std::string _volume;
        
        // Defined or dynamic
        const std::string _to_currency = "USD";
        Poco::URI _uri;
        std::string _path;
        std::string _function;
};
#endif