#include <AssetManager.hpp>

AssetManager::AssetManager()
{
    _cache = std::make_unique<Cache>("../temp/");
}

void AssetManager::populate_assets()
{
    _cache->get_type_and_name();
    return;
}

void AssetManager::add_asset(AssetType type, const std::string& name)
{
    for (const auto& asset : _assets)
    {
        if (asset->getCurrency().find(name) != std::string::npos)
        {
            return;
        }
    }
    _assets.emplace_back(std::make_shared<Asset>(type, name));
    std::sort(_assets.begin(), _assets.end(), 
    [](std::shared_ptr<Asset> &ass1, std::shared_ptr<Asset> &ass2)
    {
        return ass1->getCurrency() < ass2->getCurrency();
    });
}

std::shared_ptr<Asset> AssetManager::get_asset(const std::string& name)
{
    for (const auto& asset : _assets)
    {
        if (asset->getCurrency() == name) 
            return asset;
    }
    std::cout << "Couldn't find any asset with that name\n";
    
    return 0;
}

std::vector<std::shared_ptr<Asset>> AssetManager::get_assets() const
{
    return _assets;
}

std::vector<std::string> AssetManager::get_raw_info() const
{
    return _raw_info;
}

std::vector<std::string> AssetManager::get_asset_rates() const
{
    return _asset_rates;
}

void AssetManager::get_temp_data() const
{
}


void AssetManager::remove_asset(const int& row)
{
    _assets.erase(_assets.begin()+row-1);
}

const char* AssetManager::print_asset_info(const size_t& idx)
{
    std::string name = _assets[idx]->getCurrency();
    std::string rate = _assets[idx]->getCloseRate();
    std::string comb = name + " " + rate + "\n";

    char* output = (char*)calloc(name.size()+rate.size(),sizeof(char)); // Avoid messed up characters in print
    strcpy(output,comb.c_str());

    return output;  
}

// Should update the rate of all assets in the list
void AssetManager::update_assets()
{
    this->save_rates();
    for (const auto& asset : _assets)
    {
        asset->queryExchangeRate();
    }
}

void AssetManager::save_rates()
{
    for (const auto& asset : _assets)
    {
        _asset_rates.push_back(asset->getCloseRate());
    }
}

void AssetManager::save_cache()
{
    std::string asset_name;
    std::string rate;
    std::string type;

    AssetType asset_type;

    std::ofstream data;
    std::string line;

    data.open("../temp/cache.txt");
    if (!data.is_open())
    {
        std::cerr << "Failed to open cache.txt, check your privilegies\n";
        exit(0);
    }
    data.clear();

    for (const auto& asset : _assets)
    {
        asset_name = asset->getCurrency();
        rate = asset->getCloseRate();
        asset_type = asset->getType();

        (asset_type == AssetType::CRYPTO) ? type = "CRYPTO" : type = "STOCK";
        
        std::string comb = type + " " + asset_name + " " + rate + "\n";

        if (data.is_open())
        {
            data << comb;
        }
    }
}

void AssetManager::read_cache()
{
    std::string type;
    std::string json_obj;
    std::stringstream buffer;
    AssetType t;

    std::ifstream cache("../temp/response_dump.json");
    if (cache.is_open())
    {
        buffer << cache.rdbuf();
        json_obj = buffer.str();
        
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(json_obj);
        Poco::JSON::Object::Ptr pObject = result.extract<Poco::JSON::Object::Ptr>();
        Poco::JSON::Object::NameList names = pObject->getNames();
            // (type == "CRYPTO") ? t = AssetType::CRYPTO : t = AssetType::STOCK;
            // add_asset(t, name);
        std::cout << "Hi";
    }
}