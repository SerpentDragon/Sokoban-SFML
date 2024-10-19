#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"

using namespace sf;

class Button
{
public:

    Button() = default;
    
    Button(std::shared_ptr<RenderWindow>, const Text&, int, int, int, int, const Color&, const Color&);

    Button(std::shared_ptr<RenderWindow>, int, int, int, int, std::shared_ptr<Texture>);

    Button(const Button&) = default;

    Button(Button&&) noexcept = default;

    Button& operator=(const Button&) = default;

    Button& operator=(Button&&) noexcept = default;

    ~Button() = default;

    void drawButton();
    
    bool isPressed();

    void setText(const std::wstring&);

    void setTextColor(const Color&);

    void setButtonColor(const Color&);

private:

    bool onButton(int, int);

private:

    std::shared_ptr<RenderWindow> window_;
    RectangleShape button_;

    // coordinates and dimensions of the button
    int width_;
    int height_;  
    int xPos_;
    int yPos_;
    
    Color color_; // button color
    Color colorOn_; // button color when the cursore is over it
    Text text_; // button text
    std::shared_ptr<Texture> texture_; // button texture
};