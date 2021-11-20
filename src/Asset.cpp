#include "../include/Asset.hpp"

Asset::Asset(AssetType type, const std::string &currency) :
    _assetName(currency),
    _apiKey("&apikey=3PC87FQ16E7YV46Q"),
    _site("https://www.alphavantage.co/query?"), 
    _type(type)
{
    queryExchangeRate();
}

void Asset::queryExchangeRate()
{
    switch(_type)
    {
        case(AssetType::CRYPTO):
        {
            _function = "function=CURRENCY_EXCHANGE_RATE&from_currency=" + _assetName + "&to_currency=" + to_currency;
            break;
        }
        case(AssetType::STOCK):
        {
            _function = "function=TIME_SERIES_INTRADAY&symbol=" + _assetName + "&interval=5min";
            break;
        }
    }

    _uri = Poco::URI(_site + _function + _apiKey);
    _path = _uri.getPathAndQuery();
    
    callAPI();
}

void Asset::callAPI()
{
    auto _session = Poco::Net::HTTPSClientSession(_uri.getHost(),_uri.getPort());

    //if (!_session)
    //{
    //    std::cerr << "Connection couldn't be resolved, exiting\n";
    //    exit(1);
    //}

    auto _asset_info = Poco::Net::HTTPRequest(Poco::Net::HTTPRequest::HTTP_GET, 
                                            _path,
                                            Poco::Net::HTTPMessage::HTTP_1_1);
    _session.sendRequest(_asset_info);
    Poco::Net::HTTPResponse res;
    
    std::string output;
    std::string key;
    std::string value;
    
    std::istream &is = _session.receiveResponse(res);
    Poco::StreamCopier::copyToString(is, output);
    std::istringstream ss(output);
    while (ss >> key >> value)
    {
        switch(_type)
        {
            case(AssetType::CRYPTO):
            {
                if (key == "Rate\":" && value != "{")
                {
                    _rate = std::stof(value.substr(1,value.size()-3));
                }
            }
            case(AssetType::STOCK):
            {
                if (key == "close\":" && value != "{")
                {
                    _rate = std::stof(value.substr(1,value.size()-3));
                }
            }
        }
    }
    if (!_rate || _rate < 0) _rate = 0.0f;
    //    std::cerr << "Failed to retrieve a rate!\n";
    //return;
}


std::string Asset::getCurrency() const
{
    return _assetName;
}

float Asset::getRate() const
{
    return _rate;
}

