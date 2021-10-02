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
        void callAPI(const std::string asset);
        std::string getBTC();
        [[maybe_unused]]std::string getAFRY();
    private:
        std::unordered_map<std::string, int> assets;
        const std::string BTC = "{'Realtime Currency Exchange Rate': {'1. From_Currency Code': 'BTC', '2. From_Currency Name': 'Bitcoin', '3. To_Currency Code': 'USD', '4. To_Currency Name': 'United States Dollar', '5. Exchange Rate': '45703.08000000', '6. Last Refreshed': '2021-08-15 17:06:02', '7. Time Zone': 'UTC', '8. Bid Price': '45703.07000000', '9. Ask Price': '45703.08000000'}}"; 

        Poco::URI* _uri;
        std::string _path;
};
#endif