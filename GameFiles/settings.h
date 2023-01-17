#pragma once

using namespace sf;

// parameters
static int ScreenWidth = VideoMode::getDesktopMode().width;
static int ScreenHeight = VideoMode::getDesktopMode().height;
static int Width = 0.625 * ScreenWidth; // game window width
static int Height = 0.74075 * ScreenHeight; // game window height
static int size = Width / 24; // size of cells

//colors
static Color WHITE(255, 255, 255);
static Color GREEN(0, 128, 0);
static Color BLUE(66, 170, 255);
static Color DARK_BLUE(0, 39, 174);
static Color GREY(128, 128, 128);
