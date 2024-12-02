#pragma once

#include <memory>
#include <filesystem>
#include <unordered_map>
#include <SFML/Audio.hpp>

namespace fs = std::filesystem;

class SoundManager
{
public:

    static SoundManager& getManager() noexcept;

    void playSound(const std::string&) noexcept;

private:

    SoundManager() noexcept;

    SoundManager(const SoundManager&) = delete;

    SoundManager(SoundManager&&) noexcept = delete;

    SoundManager& operator=(const SoundManager&) = delete;

    SoundManager& operator=(SoundManager&&) noexcept = delete;

    ~SoundManager() noexcept = default;

    void loadAllSoundsFromDirectory() noexcept;

private:

    std::unordered_map<std::string, sf::SoundBuffer> sounds_;
};