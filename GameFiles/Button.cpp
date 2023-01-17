#include "Button.h"

template <typename T>
void Button::Swap(T&& obj) noexcept
{
    window = obj.window;
    button = obj.button;
    width = obj.width;
    height = obj.height;
    xPos = obj.xPos;
    yPos = obj.yPos;
    color = obj.color;
    colorOn = obj.colorOn;
    text = obj.text;
    texture = obj.texture ? new Texture(*obj.texture) : nullptr;
}

bool Button::OnButton(const int& x, const int& y)
{
    return xPos <= x && x <= xPos + width && yPos <= y && y <= yPos + height;
}

Button::Button(RenderWindow *window, const Text& txt, const int& x, const int& y, const int& b_width, const int& b_height, const Color& color, const Color& colorOn)
{
    this->window = window;
    xPos = x;
    yPos = y;
    width = b_width;
    height = b_height;
    this->color = color;
    this->colorOn = colorOn;
    text = txt;
    texture = nullptr;

    button = RectangleShape(Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(color);

    text.setPosition(x + (width - txt.getGlobalBounds().width) / 2 , y + (height - txt.getGlobalBounds().height) / 2 - size / 5);   
}

Button::Button(RenderWindow *window, const int& x, const int& y, const int& b_width, const int& b_height, const Texture* texture)
{
    this->window = window;
    xPos = x;
    yPos = y;
    width = b_width;
    height = b_height;
    color = colorOn = Color(0, 0, 0, 255);
    text = Text();
    this->texture = new Texture(*texture);

    button = RectangleShape(Vector2f(width, height));
    button.setPosition(x, y);
    button.setTexture(this->texture); 
}

Button::Button (const Button& obj)
{
    Swap(obj);
}

Button::Button(Button&& obj) noexcept
{
    Swap(obj);

    obj.window = nullptr;
    obj.width = obj.height = obj.xPos = obj.yPos = 0;
    obj.texture = nullptr;
}

Button& Button::operator=(const Button& obj)
{
    if (this != &obj)
    {
        Swap(obj);
    }
    return *this;
}

Button& Button::operator=(Button&& obj) noexcept
{
    if (this != &obj)
    {
        Swap(obj);

        obj.window = nullptr;
        obj.width = obj.height = obj.xPos = obj.yPos = 0;
        obj.texture = nullptr;
    }
    return *this;
}

Button::~Button()
{
    window = nullptr;
    if (texture) delete texture;
}

void Button::drawButton()
{
    window->draw(button);
    window->draw(text);
}

bool Button::isPressed()
{
    int x = Mouse::getPosition(*window).x;
    int y = Mouse::getPosition(*window).y;

    if (OnButton(x, y))
    {
        if (!texture) button.setFillColor(colorOn);
        if (Mouse::isButtonPressed(Mouse::Left)) 
        {
            while(true)
            {
                if (!Mouse::isButtonPressed(Mouse::Left)) break;
            }
            if (OnButton(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) return true;
        }
    }
    else if (!texture) button.setFillColor(color);

    return false;
}

void Button::setTextColor(const Color& color)
{
    text.setFillColor(color);
}

void Button::setButtonColor(const Color& color)
{
    this->color = color;
    button.setFillColor(color);
}
