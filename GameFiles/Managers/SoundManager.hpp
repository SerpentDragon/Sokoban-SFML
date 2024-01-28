#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>
#include "absolute_path.h"

namespace fs = std::filesystem;

class SoundManager
{
public:

    static SoundManager* getManager();

    void playSound(const std::string&);

private:

    SoundManager();

    SoundManager(const SoundManager&) = delete;

    SoundManager& operator=(const SoundManager&) = delete;

    void loadAllSoundsFromDirectory();

private:

    static SoundManager* manager_;

    std::unordered_map<std::string, sf::SoundBuffer> sounds_;
};