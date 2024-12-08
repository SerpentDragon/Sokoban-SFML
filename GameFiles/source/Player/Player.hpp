#pragma once

#include "map.h"
#include <tuple>
#include <stack>
#include <vector>
#include <string_view>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../settings/settings.h"
#include "../Managers/TextureManager.hpp"

using namespace sf;

using COORDINATE = std::pair<int, int>;

class Player
{
public:

    Player(std::shared_ptr<RenderWindow>, int speed = gl::size / 7) noexcept;

    Player(const Player&) noexcept = default;

    Player(Player&&) noexcept = default;

    Player& operator=(const Player&) noexcept = default;

    Player& operator=(Player&&) noexcept = default;

    ~Player() noexcept = default;

    void setLevel(const std::vector<std::vector<int>>&) noexcept;

    void movement(int) noexcept;

    void alignPlayer(int, int) noexcept; // player and boxes must be aligned by cells

    std::vector<COORDINATE> getBoxes() const noexcept;

    std::pair<bool, bool> drawPlayer() noexcept;

    void restartLevel() noexcept;

    bool cancelMove() noexcept;

private:

    size_t checkPosition(int, int) noexcept;

    size_t checkPosition(const Vector2i&) noexcept;
    
    COORDINATE* checkBoxes(int, int) noexcept;

    COORDINATE* checkBoxes(const Vector2i&) noexcept;

private:

    std::shared_ptr<RenderWindow> window_;

    std::map<std::string_view, RectangleShape> img_; // textures

    std::vector<std::vector<int>> level_; // info about level structure 
    std::vector<COORDINATE> boxes_; // info about boxes locations
    std::vector<COORDINATE> aims_; // info about positions where boxes should be placed 

    std::stack<COORDINATE> playerMoves_;
    std::stack<COORDINATE> boxesMoves_;
    
    // the values by which position of level map was moved relative to the point (0, 0)
    int offset1_; 
    int offset2_;

    // coordinates and speed of player
    int x_;  
    int y_;
    int speed_;
};
