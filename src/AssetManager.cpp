#include <AssetManager.hpp>

AssetManager::AssetManager()
{
    this->read_cache();
}

void AssetManager::populate_assets()
{
    this->add_asset(AssetType::CRYPTO, "BTC");
    this->add_asset(AssetType::STOCK, "IBM");
    this->add_asset(AssetType::STOCK, "BABA");
    this->add_asset(AssetType::STOCK, "YELP");
    this->add_asset(AssetType::STOCK, "ABB");
    this->add_asset(AssetType::STOCK, "NIO");
    this->add_asset(AssetType::STOCK, "NVDA");
    this->add_asset(AssetType::STOCK, "SQ");
    this->add_asset(AssetType::STOCK, "AMD");
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
        if (asset->getCurrency() == name) return asset;
    }
    std::cout << "Couldn't find any asset with that name\n";
    
    return 0;
}

std::vector<std::shared_ptr<Asset>> AssetManager::get_assets() const
{
    return _assets;
}

std::vector<char*> AssetManager::get_raw_info() const
{
    return _raw_info;
}

std::vector<float> AssetManager::get_asset_rates() const
{
    return _asset_rates;
}

void AssetManager::remove_asset(const int& row)
{
    _assets.erase(_assets.begin()+row-1);
}

const char* AssetManager::print_asset_info(const size_t& idx)
{
    std::string name = _assets[idx]->getCurrency();
    std::string rate = std::to_string(_assets[idx]->getRate());
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
        _asset_rates.push_back(asset->getRate());
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
        rate = std::to_string(asset->getRate());
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
    std::string name;
    std::string rate;
    std::string line;
    AssetType t;

    std::ifstream cache("../temp/cache.txt");
    if (cache.is_open())
    {
        while (getline(cache, line))
        {
            std::stringstream ss(line);
            while (ss >> type >> name >> rate)
            {
                std::string comb = name + " " + rate;
                char* output = (char*)calloc(name.size()+rate.size(),sizeof(char)); // Avoid messed up characters in print
                strcpy(output,comb.c_str());
                _raw_info.push_back(output);
                (type == "CRYPTO") ? t = AssetType::CRYPTO : t = AssetType::STOCK;
                add_asset(t, name);
            }
        }
    }
}