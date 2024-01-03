#include "TextureManager.hpp"

TextureManager* TextureManager::manager = nullptr;

TextureManager* TextureManager::getManager()
{
    if (manager == nullptr) manager = new TextureManager();
        
    return manager;
}

const sf::Texture* TextureManager::getTexture(const std::string& name) const
{
    auto it = textures.find(name);
    if (it != textures.end()) return &(it->second);
    else return nullptr;
}

sf::Texture* TextureManager::loadTextureFromFile(const std::string& filename)
{
    sf::Texture texture;
    if (texture.loadFromFile(filename))
    {
        textures[filename] = texture;
        return &textures[filename];
    }
    else return nullptr;
}

TextureManager::TextureManager()
{
    loadAllTexturesFromDirectory("textures/buttons/");
    loadAllTexturesFromDirectory("textures/cell/");
    loadAllTexturesFromDirectory("textures/interface/");
    loadAllTexturesFromDirectory("textures/player/");
}

void TextureManager::loadAllTexturesFromDirectory(const std::string& dir)
{
    for(const auto& file : fs::directory_iterator(dir))
    {
        if (fs::is_regular_file(file))
        {
            std::string filename = file.path().filename();
            std::string texture_name = filename.substr(0, filename.find("."));

            textures[dir + texture_name].loadFromFile(dir + filename);
        }
    }
}
