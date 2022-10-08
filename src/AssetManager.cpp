#include <AssetManager.hpp>

AssetManager::AssetManager()
{
    read_cache(cache_path);
}

void AssetManager::populate_assets()
{
    return;
}

void AssetManager::add_asset(AssetType type, const std::string& name)
{
    for (const auto& asset : _assets)
    {
        if (asset->getAssetName() == name)
        {
            return;
        }
    }

    _assets.emplace_back(std::make_shared<Asset>(type, name));

    sort_assets();
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

void AssetManager::remove_asset(const int& row)
{
    remove_cache(row);
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
    for (auto& asset : _assets)
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

void AssetManager::read_cache(const std::string& directory)
{
    DIR* dir;
    try
    {
        dir = opendir(directory.c_str());
        
        // If no directory found, write error
        if (dir == nullptr) 
        {
            throw std::invalid_argument("No valid directory given");
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    struct dirent* file;
    while ((file = readdir(dir)) != nullptr) 
    {
        std::string filename = file->d_name;
        if (filename == "." || filename == "..")
        {
            continue;
        }

        size_t delimiter = filename.find("_");
        size_t stop_delimiter = filename.find(".");

        AssetType type = string_to_AssetType(filename.substr(0, delimiter));
        std::string name = filename.substr(delimiter+1,(stop_delimiter-delimiter)-1);

        std::stringstream buffer;

        std::ifstream json_cache(directory+filename);
        std::string json_data;
        if (json_cache.is_open())
        {
            buffer << json_cache.rdbuf();
            json_data = buffer.str();
        }
        _assets.emplace_back(std::make_shared<Asset>(type, name, json_data));
        
    }

    if ((closedir(dir)) == -1)
        std::cerr << "Failed to close " << directory << "\n";
}

void AssetManager::remove_cache(const int& row)
{
    std::string name = _assets[row-1]->getAssetName();
    std::string t = AssetType_to_string(_assets[row-1]->getType()) + "_";

    int remove = std::remove((cache_path + t + name + ".json").c_str());
    if (remove != 0)
        std::cerr << "Failed to remove cache for " << name << " , check privilegies\n";
}

AssetType AssetManager::string_to_AssetType(std::string type)
{
    for (auto & c : type) c = std::tolower(c);
    return (type.find("crypto") != std::string::npos) ? AssetType::CRYPTO : AssetType::STOCK;
}
std::string AssetManager::AssetType_to_string(const AssetType& type)
{
    return (type == AssetType::CRYPTO) ? "crypto" : "stock";
}

void AssetManager::sort_assets()
{
    std::sort(_assets.begin(), _assets.end(), 
    [](std::shared_ptr<Asset> &ass1, std::shared_ptr<Asset> &ass2)
    {
        return ass1->getAssetName() < ass2->getAssetName();
    });
}