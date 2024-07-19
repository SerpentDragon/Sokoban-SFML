#pragma once

#include <memory>
#include <filesystem>
#include <unordered_map>
#include <SFML/Audio.hpp>

namespace fs = std::filesystem;

class SoundManager
{
public:

    static std::shared_ptr<SoundManager> getManager();

    void playSound(const std::string&);

private:

    SoundManager();

    SoundManager(const SoundManager&) = delete;

    SoundManager(SoundManager&&) noexcept = delete;

    SoundManager& operator=(const SoundManager&) = delete;

    SoundManager& operator=(SoundManager&&) noexcept = delete;

    void loadAllSoundsFromDirectory();

private:

    static std::shared_ptr<SoundManager> manager_;

    std::unordered_map<std::string, sf::SoundBuffer> sounds_;
};