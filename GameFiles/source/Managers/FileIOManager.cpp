#include "FileIOManager.hpp"

FileIOManager::FileIOManager() noexcept
    : dir_("app_data/.data/")
{
    coinsPath_ = dir_ + "coins.ltx";
    recordsPath_ = dir_ + "records.ltx";
}

std::pair<int, int> FileIOManager::readDataFromFile() noexcept
{
    if (!fs::exists(dir_)) 
        fs::create_directory(dir_);

    int coins_;
    int record_;    

    std::fstream coinsFile(coinsPath_, ib::in | ib::binary);
    std::fstream recordsFile(recordsPath_, ib::in | ib::binary);

    if (coinsFile.is_open())
    {
        coinsFile >> coins_;

        if (coins_ < 0) coins_ = 0;

        coinsFile.close();
    }
    else coins_ = default_coins_;

    if (recordsFile.is_open())
    {
        recordsFile >> record_;

        if (record_ < 0 || record_ >= levelsMap.size()) record_ = 0;

        recordsFile.close();
    }
    else record_ = 0;

    return { coins_, record_ };
}

void FileIOManager::writeDataToFile(int coins_, int record_) noexcept
{
    std::fstream coinsFile(coinsPath_, ib::out | ib::binary);
    std::fstream recordsFile(recordsPath_, ib::out | ib::binary);

    if (coinsFile.is_open())
    {
        coinsFile << coins_;
        coinsFile.close();
    }
    else std::cerr << "Can not write coins file!\n";

    if (recordsFile.is_open())
    {
        recordsFile << record_;
        recordsFile.close();
    }
    else std::cerr << "Can not write records file!\n";
}
