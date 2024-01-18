#pragma once

#include <SFML/Graphics.hpp>
#include "../Player/settings.h"

using namespace sf;

class Button
{
public:

    Button() = default;
    
    Button(RenderWindow*, const Text&, int, int, int, int, const Color&, const Color&);

    Button(RenderWindow*, int, int, int, int, const Texture*);

    Button (const Button&);

    Button(Button&&) noexcept;

    Button& operator=(const Button&);

    Button& operator=(Button&&) noexcept;

    ~Button();

    void drawButton();
    
    bool isPressed();

    void setText(const std::wstring&);

    void setTextColor(const Color&);

    void setButtonColor(const Color&);

private:

    void swap(const Button&) noexcept;

    bool onButton(int, int);

private:

    RenderWindow* window_;
    RectangleShape button_;

    // coordinates and dimensions of the button
    int width_;
    int height_;  
    int xPos_;
    int yPos_;
    
    Color color_; // button color
    Color colorOn_; // button color when the cursore is over it
    Text text_; // button text
    Texture* texture_; // button texture
};