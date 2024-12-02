#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../Player/map.h"

using ib = std::ios_base;
namespace fs = std::filesystem;

class FileIOManager
{
public:

    FileIOManager() noexcept;

    FileIOManager(const FileIOManager&) = delete;

    FileIOManager(FileIOManager&&) noexcept = delete;

    FileIOManager& operator=(const FileIOManager&) = delete;

    FileIOManager& operator=(FileIOManager&&) noexcept = delete;

    std::pair<int, int> readDataFromFile() noexcept;

    void writeDataToFile(int, int) noexcept;

private:

    std::string coinsPath_;
    std::string recordsPath_;
    std::string dir_;

    const int default_coins_ = 50;
    const int default_record_ = 0;
};
