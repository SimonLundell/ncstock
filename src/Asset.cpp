#include "../include/Asset.hpp"

Asset::Asset(const std::string &currency) :
    _currency(currency),
    _site("https://www.alphavantage.co/query?"), 
    _apiKey("&apikey=3PC87FQ16E7YV46Q")
{
}

void Asset::callAPI()
{
    auto _session = Poco::Net::HTTPSClientSession(_uri.getHost(),_uri.getPort());
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
        if (key == "Rate\":" && value != "{")
        {
            _rate = std::stof(value.substr(1,value.size()-3));
        }
    }
}

float Asset::getExchangeRate(const std::string &to_currency)
{
    _function = "function=CURRENCY_EXCHANGE_RATE&from_currency=" + _currency + "&to_currency=" + to_currency;
    _uri = Poco::URI(_site + _function + _apiKey);
    _path = _uri.getPathAndQuery();
    
    callAPI();

    return _rate;
}

std::string Asset::getCurrency()
{
    return _currency;
}

