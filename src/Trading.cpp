#include "../include/Trading.hpp"

TradingInfo::TradingInfo() : 
    _site("https://www.alphavantage.co/query?"), 
    _apiKey("&apikey=3PC87FQ16E7YV46Q")
{
}

void TradingInfo::callAPI(const std::string &_path)
{
    auto uri = Poco::URI(_path);
    auto path = uri.getPathAndQuery();
    auto _session = Poco::Net::HTTPSClientSession(uri.getHost(),uri.getPort());

    auto asset_info = Poco::Net::HTTPRequest(Poco::Net::HTTPRequest::HTTP_GET, 
                                            path,
                                            Poco::Net::HTTPMessage::HTTP_1_1);
    _session.sendRequest(asset_info);
    Poco::Net::HTTPResponse res;
    //std::cout << res.getStatus() << " " << res.getReason() << "\n";

    std::istream &is = _session.receiveResponse(res);
    Poco::StreamCopier::copyStream(is, std::cout);
}

void TradingInfo::getExchangeRate(const std::string &asset, const std::string &to_currency)
{
    const std::string function = "function=CURRENCY_EXCHANGE_RATE&from_currency=" + asset + "&to_currency=" + to_currency;
    callAPI(_site + function + _apiKey);
}