#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <memory>

#include <Asset.hpp>


class AssetManager
{
    public:
        // Constructor, populates assets
        AssetManager();

        std::shared_ptr<Asset> get_asset(const std::string& name);
        void add_asset(AssetType type, const std::string& name);
        void remove_asset(const int& row);
        void update_assets();

        const char* print_asset_info(const size_t& idx);



        std::vector<std::shared_ptr<Asset>> assets;
};

#endif