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
    for (const auto& asset : assets)
    {
        if (asset->getCurrency().find(name) != std::string::npos)
        {
            return;
        }
    }
    assets.emplace_back(std::make_shared<Asset>(type, name));
    std::sort(assets.begin(), assets.end(), 
    [](std::shared_ptr<Asset> &ass1, std::shared_ptr<Asset> &ass2)
    {
        return ass1->getCurrency() < ass2->getCurrency();
    });

    save_cache();
}

std::shared_ptr<Asset> AssetManager::get_asset(const std::string& name)
{
    for (const auto& asset : assets)
    {
        if (asset->getCurrency() == name) return asset;
    }
    std::cout << "Couldn't find any asset with that name\n";
    
    return 0;
}

void AssetManager::remove_asset(const int& row)
{
    assets.erase(assets.begin()+row-1);
}

const char* AssetManager::print_asset_info(const size_t& idx)
{
    std::string name = assets[idx]->getCurrency();
    std::string rate = std::to_string(assets[idx]->getRate());
    std::string comb = name + " " + rate + "\n";

    char* output = (char*)calloc(name.size()+rate.size(),sizeof(char)); // Avoid messed up characters in print
    strcpy(output,comb.c_str());

    return output;  
}

// Should update the rate of all assets in the list
void AssetManager::update_assets()
{
    for (const auto& asset : assets)
    {
        asset->queryExchangeRate();
    }
}

void AssetManager::save_cache()
{
    std::ofstream data;
    std::string line;
    data.open("../temp/cache.txt");
    for (size_t idx = 0; idx < assets.size(); idx++)
    {
        std::string name = assets[idx]->getCurrency();
        std::string rate = std::to_string(assets[idx]->getRate());
        std::string comb = name + " " + rate + "\n";

        data << comb;
    }
}

// TODO: DOESNT READ THE ASSET ON NEW START OF PROGRAM
void AssetManager::read_cache()
{
    std::string name;
    std::string rate;
    std::string line;

    std::ifstream cache("../temp/cache.txt");
    if (cache.is_open())
    {
        while (getline(cache, line))
        {
            std::stringstream ss(line);
            while (ss >> name >> rate)
            {
                std::string comb = name + " " + rate;
                char* output = (char*)calloc(name.size()+rate.size(),sizeof(char)); // Avoid messed up characters in print
                strcpy(output,comb.c_str());
                raw_info.push_back(output);
            }
        }
    }
}