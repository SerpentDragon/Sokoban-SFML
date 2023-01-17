#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"

using namespace sf;

class Button
{
    RenderWindow* window;
    RectangleShape button;

    // coordinates and dimensions of the button
    int width;
    int height;  
    int xPos;
    int yPos;
    
    Color color; // button color
    Color colorOn; // button color when the cursore is over it
    Text text; // button text
    Texture* texture; // button texture

    template <typename T>
    void Swap(T&& obj) noexcept;

    bool OnButton(const int& x, const int& y);

public:
    Button(RenderWindow *window, const Text& txt, const int& x, const int& y, const int& b_width, const int& b_height, const Color& color, const Color& colorOn);

    Button(RenderWindow *window, const int& x, const int& y, const int& b_width, const int& b_height, const Texture* texture);

    Button (const Button& obj);

    Button(Button&& obj) noexcept;

    Button& operator=(const Button& obj);

    Button& operator=(Button&& obj) noexcept;

    ~Button();

    void drawButton();
    
    bool isPressed();

    void setTextColor(const Color& color);

    void setButtonColor(const Color& color);
};