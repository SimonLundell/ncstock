#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

#include <dirent.h>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

class Cache
{
    public:
        Cache(std::string directory);
        void open_directory(std::string directory);
        std::pair<std::string, std::string> get_type_and_name();

    private:
        DIR* cache_data_dir{};
        std::string directory;
};

#endif