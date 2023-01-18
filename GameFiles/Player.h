#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"

using namespace sf;

class Player
{
    RenderWindow *window;

    std::vector<std::vector<int>> level; // info about level structure 
    std::vector<std::pair<int, int>> boxes; // info about boxes locations
    std::vector<std::pair<int, int>> aims; // info about positions where boxes should be placed 
    
    // the values by which position of level map was moved relative to the point (0, 0)
    int offset1; 
    int offset2;

    std::map<std::string, std::pair<Texture, RectangleShape>> img; // textures

    // coordinates and speed of player
    int x;  
    int y;
    int speed;

    template<typename T>
    void Swap(T&& obj) noexcept;

public:
    Player(RenderWindow* window, const std::vector<std::vector<int>> level, const int& speed = size / 7);

    Player(const Player& obj);

    Player(Player&& obj) noexcept;

    Player& operator=(const Player& obj);

    Player& operator=(Player&& obj) noexcept;

    ~Player();

    size_t checkPosition(const int& xPos, const int& yPos);

    size_t checkPosition(const Vector2i& vec);
    
    std::pair<int, int>* checkBoxes(const int& first, const int& second);

    std::pair<int, int>* checkBoxes(const Vector2i& vec);

    void movement(const int& pressed_key);

    void alignPlayer(const int& released_key, const int& param); // player and boxes must be aligned by cells

    bool drawPlayer();

    void restartLevel();
};
