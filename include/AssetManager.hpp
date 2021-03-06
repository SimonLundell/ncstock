#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <memory>
#include <fstream>

#include <Asset.hpp>


class AssetManager
{
    public:
        // Constructor, populates assets
        AssetManager();
        ~AssetManager() = default;

        std::shared_ptr<Asset> get_asset(const std::string& name);
        std::vector<std::shared_ptr<Asset>> get_assets() const;
        std::vector<char*> get_raw_info() const;
        void populate_assets(); // Not being called, only populated from cache.txt
        void add_asset(AssetType type, const std::string& name);
        void remove_asset(const int& row);
        void update_assets();
        void save_cache();
        void read_cache();

        const char* print_asset_info(const size_t& idx);



    private:
        std::vector<std::shared_ptr<Asset>> _assets;
        std::vector<char*> _raw_info;
};

#endif