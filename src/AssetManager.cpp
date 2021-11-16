#include <AssetManager.hpp>

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