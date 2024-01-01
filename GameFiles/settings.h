#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

// parameters
extern int ScreenWidth; // screen dimensions
extern int ScreenHeight;
extern int Width; // game window width
extern int Height; // game window height
extern int size; // size of cells

// colors
extern Color WHITE;
extern Color GREEN;
extern Color BLUE;
extern Color DARK_BLUE;
extern Color GREY;
extern Color GOLD;

// fonts
extern Font font;

// field cells
enum FIELD : unsigned int { NO_FIELD = 0, WALL, GRASS, AIM, BOX, PLAYER };
