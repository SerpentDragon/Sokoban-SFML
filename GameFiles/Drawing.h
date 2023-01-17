#pragma once 

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Button.h"
#include "Player.h"
#include "settings.h"
#include "map.h"

using namespace sf;

bool showWarning(RenderWindow *window, const String& str);

void pollEvents(RenderWindow *window);

class Drawing
{
    RenderWindow* window;

    std::map<std::string, std::pair<Texture, RectangleShape>> world;

public: 
    Drawing(RenderWindow* window);

    Drawing(const Drawing& obj);
    
    Drawing(Drawing&& obj) noexcept;

    Drawing& operator=(const Drawing& obj);

    Drawing& operator=(Drawing&& obj) noexcept;

    ~Drawing();

    bool drawWorld(const int& level_num);
};
