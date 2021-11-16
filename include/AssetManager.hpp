#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <memory>

#include <Asset.hpp>

class AssetManager
{
    public:
        AssetManager() = default;

        void add_asset(std::shared_ptr<Asset> asset);
        std::shared_ptr<Asset> get_asset(const std::string& name);

        std::vector<std::shared_ptr<Asset>> assets;
};

#endif