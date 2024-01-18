#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include "../Managers/TextureManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/Localizer.hpp"
#include "../Widgets/Button.hpp"
#include "../Player/Player.hpp"
#include "../Player/settings.h"
#include "../Player/map.h"

using namespace sf;

bool showWarning(RenderWindow*, const String&);

void pollEvents(RenderWindow*);

class Drawing
{
public:

    Drawing(RenderWindow*);

    Drawing(const Drawing&) = delete;
    
    Drawing(Drawing&&) noexcept = delete;

    Drawing& operator=(const Drawing&) = delete;

    Drawing& operator=(Drawing&&) noexcept = delete;

    ~Drawing();

    bool drawWorld(const int);

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

    RenderWindow* window_;

    std::unordered_map<std::string, RectangleShape> world_;

    Button backButton_;
    Button restartButton_;
    Button levelsButton_;

    Text levelText_;
    Text coinsText_;

    RectangleShape background_;

    int coins_; // coins amount you have 
    const int price_ = 10;  // coins amount you need to cancel your move

    Player player_;
};
