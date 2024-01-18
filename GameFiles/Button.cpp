#include "Button.hpp"

void Button::swap(const Button& other) noexcept
{
    window_ = other.window_;
    button_ = other.button_;
    width_ = other.width_;
    height_ = other.height_;
    xPos_ = other.xPos_;
    yPos_ = other.yPos_;
    color_ = other.color_;
    colorOn_ = other.colorOn_;
    text_ = other.text_;
    texture_ = other.texture_ ? new Texture(*other.texture_) : nullptr;
}

bool Button::onButton(int x, int y)
{
    return xPos_ <= x && x <= xPos_ + width_ && yPos_ <= y && y <= yPos_ + height_;
}

Button::Button(RenderWindow *window, const Text& text, 
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
        y + (height_ - text_.getGlobalBounds().height) / 2 - size / 5);   
}

Button::Button(RenderWindow *window, int x, int y, 
    int width, int height, const Texture* texture)
    : window_(window), xPos_(x), yPos_(y), width_(width),
    height_(height)
{
    color_ = colorOn_ = Color(0, 0, 0, 255);
    text_ = Text();
    this->texture_ = texture ? new Texture(*texture) : new Texture();

    button_ = RectangleShape(Vector2f(width_, height_));
    button_.setPosition(x, y);
    button_.setTexture(this->texture_); 
}

Button::Button(const Button& other)
{
    swap(other);
}

Button::Button(Button&& other) noexcept
{
    swap(other);

    other.window_ = nullptr;
    other.width_ = other.height_ = other.xPos_ = other.yPos_ = 0;
    other.texture_ = nullptr;
}

Button& Button::operator=(const Button& other)
{
    if (this != &other)
    {
        swap(other);
    }
    return *this;
}

Button& Button::operator=(Button&& other) noexcept
{
    if (this != &other)
    {
        swap(other);

        other.window_ = nullptr;
        other.width_ = other.height_ = other.xPos_ = other.yPos_ = 0;
        other.texture_ = nullptr;
    }
    return *this;
}

Button::~Button()
{
    window_ = nullptr;
    if (texture_) delete texture_;
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
