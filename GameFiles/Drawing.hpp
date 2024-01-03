#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include "TextureManager.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "settings.h"
#include "map.h"

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

private:

    RenderWindow* window_;

    std::unordered_map<std::string, RectangleShape> world_;

    Button backButton_;
    Button restartButton_;
    Button levelsButton_;

    Text levelText_;
    Text coinsText_;

    RectangleShape background_;

    int coins_;

    Player player;
};
