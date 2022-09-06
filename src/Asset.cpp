#include "../include/Asset.hpp"

Asset::Asset(AssetType type, const std::string &asset_name) :
    _assetName(asset_name),
    _apiKey("&apikey=3PC87FQ16E7YV46Q"),
    _site("https://www.alphavantage.co/query?"), 
    _type(type),
    _query_time(""),
    _open_rate(""),
    _high_rate(""),
    _low_rate(""),
    _close_rate(""),
    _volume("")
{
    queryExchangeRate();
}

Asset::Asset(AssetType type, const std::string &asset_name,  const std::string data) : 
    _assetName(asset_name),
    _apiKey("&apikey=3PC87FQ16E7YV46Q"),
    _site("https://www.alphavantage.co/query?"), 
    _type(type),
    _query_time(""),
    _open_rate(""),
    _high_rate(""),
    _low_rate(""),
    _close_rate(""),
    _volume("")
{
    parseResponse(data);
}

void Asset::establishSession()
{
    Poco::Net::HTTPResponse res;
    std::string output;

    _session = std::make_shared<Poco::Net::HTTPSClientSession>(_uri.getHost(),_uri.getPort());
    // _session = std::move(session);
}

void Asset::queryExchangeRate()
{
    switch(_type)
    {
        case(AssetType::CRYPTO):
        {
            _function = "function=CRYPTO_INTRADAY&symbol=" + _assetName + "&market=" + _to_currency + "&interval=5min";
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
    
    establishSession();
    callAPI();
}

void Asset::callAPI()
{
    Poco::Net::HTTPResponse res;
    std::string output;

    // auto _session = Poco::Net::HTTPSClientSession(_uri.getHost(),_uri.getPort());


    auto _asset_info = Poco::Net::HTTPRequest(Poco::Net::HTTPRequest::HTTP_GET, 
                                            _path,
                                            Poco::Net::HTTPMessage::HTTP_1_1);
    _session->sendRequest(_asset_info);
    
    std::istream &is = _session->receiveResponse(res);
    if (res.getStatus() == 400)
    {
        std::cerr << "Connection couldn't be resolved, exiting\n";
        exit(1);
    }
    Poco::StreamCopier::copyToString(is, output);
    std::istringstream ss(output);

    parseResponse(output);
    cache_dump(output);
}

void Asset::parseResponse(const std::string& response_string)
{
    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(response_string);
    Poco::JSON::Object::Ptr pObject = result.extract<Poco::JSON::Object::Ptr>();
    Poco::JSON::Object::NameList names = pObject->getNames();
    
    if (names[0] == "Error Message") 
        exit(-1);

    auto time_series_5min = pObject->getObject(names[1]);
    auto ts5_names = time_series_5min->getNames();
    auto latest_ts5_obj = time_series_5min->getObject(ts5_names[ts5_names.size()-1]);
    auto ts5_obj_names = latest_ts5_obj->getNames();

    std::string ts5_open_rate = latest_ts5_obj->getValue<std::string>(ts5_obj_names[0]);
    std::string ts5_high_rate = latest_ts5_obj->getValue<std::string>(ts5_obj_names[1]);
    std::string ts5_low_rate = latest_ts5_obj->getValue<std::string>(ts5_obj_names[2]);
    std::string ts5_close_rate = latest_ts5_obj->getValue<std::string>(ts5_obj_names[3]);
    std::string ts5_volume = latest_ts5_obj->getValue<std::string>(ts5_obj_names[4]);

    try
    {
        _query_time = ts5_names[ts5_names.size()-1];
        _open_rate = ts5_open_rate;
        _high_rate = ts5_high_rate;
        _low_rate = ts5_low_rate;
        _close_rate = ts5_close_rate;
        _volume = ts5_volume;
    }
    catch(...) {}

    if (_close_rate.empty()) 
        _close_rate = "0.0";
    
}

void Asset::cache_dump(const std::string& response_string)
{
    std::ofstream data;
    std::string line;
    std::string type;
    std::string name = getAssetName();

    (getType() == AssetType::CRYPTO) ? type = "crypto" : type = "stock";

    data.open("../temp/" + type + "_" + name + ".json");
    if (!data.is_open())
    {
        std::cerr << "Failed to open response_dump.json, check your privilegies\n";
        exit(0);
    }

    data << response_string;
}

std::string Asset::getCurrency() const
{
    return _to_currency;
}

std::string Asset::getCloseRate() const
{
    return _close_rate;
}

std::string Asset::getOpenRate() const
{
    return _open_rate;
}

std::string Asset::getHighRate() const
{
    return _high_rate;
}

std::string Asset::getLowRate() const
{
    return _low_rate;
}

std::string Asset::getVolume() const
{
    return _volume;
}

AssetType Asset::getType() const
{
    return _type;
}

std::string Asset::getAssetName() const
{
    return _assetName;
}

std::string Asset::getTime() const
{
    return _query_time;
}