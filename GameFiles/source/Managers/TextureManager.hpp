#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

using TexturePtr = std::shared_ptr<sf::Texture>;

class TextureManager
{
public:

    static TextureManager& getManager() noexcept;

    TexturePtr getTexture(const std::string&) const noexcept;

    TexturePtr loadTextureFromFile(const std::string&) noexcept;

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

    mutable std::unordered_map<std::string, TexturePtr> textures_;
};
