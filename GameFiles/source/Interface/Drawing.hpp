#pragma once 

#include <string>
#include <memory>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "../Player/map.h"
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"
#include "../Player/Player.hpp"
#include "../Widgets/Button.hpp"
#include "../Managers/Localizer.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/TextureManager.hpp"

using namespace sf;

bool showWarning(std::shared_ptr<RenderWindow>, const String&);

void pollEvents(std::shared_ptr<RenderWindow>);

class Drawing
{
public:

    Drawing(std::shared_ptr<RenderWindow>);

    Drawing(const Drawing&) = delete;
    
    Drawing(Drawing&&) noexcept = delete;

    Drawing& operator=(const Drawing&) = delete;

    Drawing& operator=(Drawing&&) noexcept = delete;

    ~Drawing() = default;

    void setLevel(const int);

    int getLevel() const;

    bool drawWorld();

    void setCoins(int);

    const int getCoins() const;

private:

    void loadTextures();

    void createButtons();

    void updateLevelText(int);

    void updateCoinsText();

    void updateBackground(int);

    void drawMap(size_t, size_t, 
        const std::vector<std::vector<int>>&, int, int);

private:

    std::shared_ptr<RenderWindow> window_;

    std::unordered_map<std::string, RectangleShape> world_;

    Button backButton_;
    Button restartButton_;
    Button levelsButton_;

    unsigned int level_;

    Text levelText_;
    Text coinsText_;

    RectangleShape background_;

    int coins_; // coins amount you have 
    const int price_ = 10;  // coins amount you need to cancel your move

    Player player_;
};
