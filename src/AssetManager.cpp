#include <AssetManager.hpp>

AssetManager::AssetManager()
{
    this->add_asset(std::make_shared<Asset>(AssetType::CRYPTO, "BTC"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "IBM"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "BABA"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "YELP"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "ABB"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "NIO"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "NVDA"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "SQ"));
    this->add_asset(std::make_shared<Asset>(AssetType::STOCK, "AMD"));
}

void AssetManager::add_asset(std::shared_ptr<Asset> asset)
{
    assets.emplace_back(asset);
    std::sort(assets.begin(), assets.end(), [](std::shared_ptr<Asset> &ass1, std::shared_ptr<Asset> &ass2){return ass1->getCurrency() < ass2->getCurrency();});
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

    char* output = (char*)calloc(name.size()+rate.size()+4,sizeof(char)); // Avoid messed up characters in print
    strcpy(output,comb.c_str());

    return output;  
}