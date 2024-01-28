#include "SoundManager.hpp"

SoundManager* SoundManager::manager_ = nullptr;

SoundManager* SoundManager::getManager()
{
    if (manager_ == nullptr) manager_ = new SoundManager();

    return manager_;
}

void SoundManager::playSound(const std::string& name)
{
    sf::Sound sound(sounds_[name]);
    sound.play();
    sf::sleep(sf::milliseconds(700));
}

SoundManager::SoundManager()
{
    loadAllSoundsFromDirectory();
}

void SoundManager::loadAllSoundsFromDirectory()
{
    const std::string dir = "music/";
    for(const auto& entry : fs::directory_iterator(dir))
    {
        if (fs::is_regular_file(entry))
        {
            std::string filename = entry.path().filename();
            std::string sound_name = entry.path().stem();

            sounds_[sound_name].loadFromFile(dir + filename);
        }
    }
}
