#include <CacheManager.hpp>

Cache::Cache(std::string directory) : directory(directory)
{
    try
    {
       open_directory(directory.c_str()); 
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
}

void Cache::open_directory(std::string directory)
{
    DIR* dir = opendir(directory.c_str());
    
    // If no directory found, write error
    if (dir == nullptr) 
    {
        throw std::invalid_argument("No valid directory given");
    }

    cache_data_dir = std::move(dir);
}

std::pair<std::string, std::string> Cache::get_type_and_name()
{
    struct dirent* file;
    while ((file = readdir(cache_data_dir)) != nullptr) 
    {
        std::string filename = file->d_name;
        size_t delimiter = filename.find("_");
        size_t stop_delimiter = filename.find(".");
        std::string type = filename.substr(0, delimiter);
        std::string name = filename.substr(delimiter+1,(stop_delimiter-delimiter)-1);

        std::string json_obj;
        std::stringstream buffer;

        std::ifstream cache(filename);
        if (cache.is_open())
        {
            buffer << cache.rdbuf();
            json_obj = buffer.str();
        }
    }

    if ((closedir(cache_data_dir)) == -1)
        std::cerr << "Failed to close " << directory << "\n";

    return std::make_pair("Hello", "Compile");
}