#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
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

    bool drawWorld(int);

    void setCoins(int);

    const int getCoins() const;

private:
    RenderWindow* window_;

    std::map<std::string, std::pair<Texture, RectangleShape>> world_;

    int coins_;
};
