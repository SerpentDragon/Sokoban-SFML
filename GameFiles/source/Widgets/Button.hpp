#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"
#include "../Managers/TextureManager.hpp"

using namespace sf;

class Button
{
public:

    Button() noexcept = default;
    
    Button(std::shared_ptr<RenderWindow>, const Text&, int, int, int, int, const Color&, const Color&) noexcept;

    Button(std::shared_ptr<RenderWindow>, int, int, int, int, std::shared_ptr<Texture>) noexcept;

    Button(const Button&) noexcept = default;

    Button(Button&&) noexcept = default;

    Button& operator=(const Button&) noexcept = default;

    Button& operator=(Button&&) noexcept = default;

    ~Button() noexcept = default;

    void drawButton() noexcept;
    
    bool isPressed() noexcept;

    void setText(const std::wstring&) noexcept;

    void setTextColor(const Color&) noexcept;

    void setButtonColor(const Color&) noexcept;

private:

    bool onButton(int, int) noexcept;

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