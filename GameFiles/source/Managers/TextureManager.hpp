#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class TextureManager
{
public:

    static TextureManager* getManager();

    const sf::Texture* getTexture(const std::string&) const;

    sf::Texture* loadTextureFromFile(const std::string&);

private:

    TextureManager();

    TextureManager(const TextureManager&) = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    void loadAllTexturesFromDirectory(const std::string&);

private:

    static TextureManager* manager_;

    std::string prefix_;

    mutable std::unordered_map<std::string, sf::Texture> textures_;
};
