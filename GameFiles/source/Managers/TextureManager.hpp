#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

class TextureManager
{
public:

    static TextureManager& getManager() noexcept;

    const sf::Texture* getTexture(const std::string&) const noexcept;

    const sf::Texture* loadTextureFromFile(const std::string&) noexcept;

private:

    TextureManager() noexcept;

    TextureManager(const TextureManager&) = delete;

    TextureManager(TextureManager&&) noexcept = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager& operator=(TextureManager&&) noexcept = delete;

    ~TextureManager() noexcept = default;

    void loadAllTexturesFromDirectory(const std::string&) noexcept;

private:

    std::string prefix_;

    mutable std::unordered_map<std::string, sf::Texture> textures_;
};
