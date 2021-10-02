#include "../include/Trading.hpp"

TradingInfo::TradingInfo()
{
}

void TradingInfo::callAPI(const std::string asset)
{
    _path = "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=4PC87FQ16E7YV46Q";
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
std::string TradingInfo::getBTC()
{
    //auto it = assets.find("Bitcoin");
    //std::string ret = it->first + std::to_string(it->second);

    return "Bitcoin";
}
[[maybe_unused]]std::string TradingInfo::getAFRY()
{
    
}