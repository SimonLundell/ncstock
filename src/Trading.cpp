#include "../include/Trading.hpp"

void TradingInfo::callAPI(const std::string asset)
{
    auto asset_info = Poco::Net::HTTPRequest("https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=4PC87FQ16E7YV46Q");
    std::cout << asset_info.size() << "\n";   
    assets.emplace("Bitcoin",45000);
}
std::string TradingInfo::getBTC()
{
    auto it = assets.find("Bitcoin");
    std::string ret = it->first + std::to_string(it->second);

    return ret;
}
[[maybe_unused]]std::string TradingInfo::getAFRY()
{
    
}