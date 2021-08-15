#include "../include/Trading.hpp"

void TradingInfo::callAPI(const std::string asset)
{
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