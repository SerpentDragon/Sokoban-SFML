#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include <vector>
#include <tuple>
#include "settings.h"

using namespace sf;

class Player
{
public:

    Player(RenderWindow*, const std::vector<std::vector<int>>&, int speed = size / 7);

    ~Player();

    void movement(int essed_key);

    void alignPlayer(int, int); // player and boxes must be aligned by cells

    std::pair<bool, bool>  drawPlayer();

    void restartLevel();

    bool cancelMove();

private:

    size_t checkPosition(int, int);

    size_t checkPosition(const Vector2i&);
    
    std::pair<int, int>* checkBoxes(int, int);

    std::pair<int, int>* checkBoxes(const Vector2i&);

private:

    RenderWindow* window_;

    std::vector<std::vector<int>> level_; // info about level structure 
    std::vector<std::pair<int, int>> boxes_; // info about boxes locations
    std::vector<std::pair<int, int>> aims_; // info about positions where boxes should be placed 

    std::stack<std::pair<int, int>> playerMoves_;
    std::stack<std::pair<int, int>> boxesMoves_;
    
    // the values by which position of level map was moved relative to the point (0, 0)
    int offset1_; 
    int offset2_;

    std::map<std::string, std::pair<Texture, RectangleShape>> img_; // textures

    // coordinates and speed of player
    int x_;  
    int y_;
    int speed_;
};