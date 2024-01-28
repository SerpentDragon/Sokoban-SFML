#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "../Player/map.h"
#include "absolute_path.h"

using ib = std::ios_base;
namespace fs = std::filesystem;

class FileIOManager
{
public:

    FileIOManager();

    FileIOManager(const FileIOManager&) = delete;

    FileIOManager(FileIOManager&&) noexcept = delete;

    FileIOManager& operator=(const FileIOManager&) = delete;

    FileIOManager& operator=(FileIOManager&&) noexcept = delete;

    std::pair<int, int> readDataFromFile();

    void writeDataToFile(int, int);

private:

    std::string coinsPath_;
    std::string recordsPath_;

    const int default_coins_ = 50;
    const int default_record_ = 0;
};
