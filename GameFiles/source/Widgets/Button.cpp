#include "Button.hpp"

bool Button::onButton(int x, int y)
{
    return xPos_ <= x && x <= xPos_ + width_ && yPos_ <= y && y <= yPos_ + height_;
}

Button::Button(std::shared_ptr<RenderWindow> window, const Text& text, 
    int x, int y, int width, int height, 
    const Color& color, const Color& colorOn)
    : window_(window), text_(text), xPos_(x), yPos_(y),
    width_(width), height_(height), color_(color), colorOn_(colorOn),
    texture_(nullptr)

{
    button_ = RectangleShape(Vector2f(width_, height_));
    button_.setPosition(x, y);
    button_.setFillColor(color_);

    text_.setPosition(x + (width_ - text_.getGlobalBounds().width) / 2 , 
        y + (height_ - text_.getGlobalBounds().height) / 2 - gl::size / 5);   
}

Button::Button(std::shared_ptr<RenderWindow> window, int x, int y, 
    int width, int height, std::shared_ptr<Texture> texture)
    : window_(window), xPos_(x), yPos_(y), width_(width),
    height_(height)
{
    color_ = colorOn_ = Color(0, 0, 0, 255);
    text_ = Text();
    this->texture_ = texture ? 
        texture : std::shared_ptr<Texture>(new Texture());

    button_ = RectangleShape(Vector2f(width_, height_));
    button_.setPosition(x, y);
    button_.setTexture(this->texture_.get());
}

void Button::drawButton()
{
    window_->draw(button_);
    window_->draw(text_);
}

bool Button::isPressed()
{
    int x = Mouse::getPosition(*window_).x;
    int y = Mouse::getPosition(*window_).y;

    if (onButton(x, y))
    {
        if (!texture_) button_.setFillColor(colorOn_);
        if (Mouse::isButtonPressed(Mouse::Left)) 
        {
            while(true)
            {
                if (!Mouse::isButtonPressed(Mouse::Left)) 
                    break;
            }
            if (onButton(Mouse::getPosition(*window_).x, Mouse::getPosition(*window_).y)) 
                return true;
        }
    }
    else if (!texture_) button_.setFillColor(color_);

    return false;
}

void Button::setText(const std::wstring& text)
{
    text_.setString(text);
    text_.setPosition(xPos_ + (width_ - text_.getGlobalBounds().width) / 2 , 
        yPos_ + (height_ - text_.getGlobalBounds().height) / 2 - gl::size / 5);
}

void Button::setTextColor(const Color& color_)
{
    text_.setFillColor(color_);
}

void Button::setButtonColor(const Color& color_)
{
    this->color_ = color_;
    button_.setFillColor(color_);
}
