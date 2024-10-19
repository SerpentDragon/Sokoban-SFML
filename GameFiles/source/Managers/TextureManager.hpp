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

    static TextureManager& getManager();

    const sf::Texture* getTexture(const std::string&) const;

    const sf::Texture* loadTextureFromFile(const std::string&);

private:

    TextureManager();

    TextureManager(const TextureManager&) = delete;

    TextureManager(TextureManager&&) noexcept = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager& operator=(TextureManager&&) noexcept = delete;

    ~TextureManager() = default;

    void loadAllTexturesFromDirectory(const std::string&);

private:

    std::string prefix_;

    mutable std::unordered_map<std::string, sf::Texture> textures_;
};
