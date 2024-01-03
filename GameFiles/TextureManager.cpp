#include "TextureManager.hpp"

TextureManager* TextureManager::manager_ = nullptr;

TextureManager* TextureManager::getManager()
{
    if (manager_ == nullptr) manager_ = new TextureManager();
        
    return manager_;
}

const sf::Texture* TextureManager::getTexture(const std::string& name) const
{
    auto it = textures_.find(name);
    if (it != textures_.end()) return &(it->second);
    else return nullptr;
}

sf::Texture* TextureManager::loadTextureFromFile(const std::string& filename)
{
    sf::Texture texture;
    if (texture.loadFromFile(filename))
    {
        textures_[filename] = texture;
        return &textures_[filename];
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
            std::string texture_name = file.path().stem();
            
            textures_[dir + texture_name].loadFromFile(dir + filename);
        }
    }
}
