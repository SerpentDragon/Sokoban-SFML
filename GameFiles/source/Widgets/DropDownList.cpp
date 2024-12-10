#include "DropDownList.hpp"

// DropdownList class

DropDownList::DropDownList(std::shared_ptr<RenderWindow> window) noexcept
    : window_(window), 
    list_(Vector2f(IN::dropDownListWidth, IN::dropDownListHeight)),
    x_(IN::dropDownListXPos), y_(IN::dropDownListYPos)
{
    width_ = list_.getSize().x;
    height_ = list_.getSize().y;

    list_.setFillColor(gl::GREEN);
    list_.setPosition(x_, y_);

    createItems();
}

void DropDownList::drawList() noexcept
{
    int x = Mouse::getPosition(*window_).x;
    int y = Mouse::getPosition(*window_).y;

    height_ = onList(x, y) ? gl::size * items_.size() : gl::size;

    list_.setSize(Vector2f(width_, height_));

    window_->draw(list_);

    for(auto& item : items_)
    {
        item.highlightItem(item.onItem(x, y));
    }

    if (height_ > gl::size)
        for(auto& item : items_) window_->draw(item.itemRect_);
    else
        window_->draw(items_[0].itemRect_);
}

std::string_view DropDownList::isPressed() noexcept
{
    int x = Mouse::getPosition(*window_).x;
    int y = Mouse::getPosition(*window_).y;

    if (onList(x, y))
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            while(true)
            {
                if (!Mouse::isButtonPressed(Mouse::Left)) 
                    break;
            }

            x = Mouse::getPosition(*window_).x;
            y = Mouse::getPosition(*window_).y;

            for(size_t i = 1; i < items_.size(); i++)
            {
                if (items_[i].onItem(x, y))
                {
                    std::string_view locale = items_[i].locale_;
                    items_[i].swap(items_[0]);
                    return locale;
                }
            }
        }
    }

    return "";
}

bool DropDownList::onList(int x, int y) const noexcept
{
    return x_ <= x && x <= x_ + width_ 
        && y_ <= y && y <= y_ + height_;
}

void DropDownList::createItems() noexcept
{
    const int itemSize = gl::size - Item::itemOutlineThickness * 2;
    
    items_ = {
        { 0, 0, itemSize, 
            TextureManager::getManager().getTexture("textures/languages/en_UK"),
            "en_UK" },

        { 0, 0, itemSize, 
            TextureManager::getManager().getTexture("textures/languages/ru_RU"),
            "ru_RU" },

        { 0, 0, itemSize, 
            TextureManager::getManager().getTexture("textures/languages/de_DE"),
            "de_DE" },

        { 0, 0, itemSize, 
            TextureManager::getManager().getTexture("textures/languages/fr_FR"),
            "fr_FR" }
    };

    for(size_t i = 0; i < items_.size(); i++)
    {
        items_[i].itemRect_.setPosition(x_ + Item::itemOutlineThickness,
            y_ + gl::size * i + Item::itemOutlineThickness);
    }
}


// Items class

int DropDownList::Item::itemOutlineThickness = gl::GameScreenWidth / 400;

DropDownList::Item::Item(int x, int y, const int size, 
    std::shared_ptr<Texture> texture, std::string_view locale) noexcept
    : itemRect_(Vector2f(size, size)), locale_(locale), texture_(texture)
{   
    itemRect_.setPosition(x, y);
    itemRect_.setTexture(texture_.get());
    itemRect_.setOutlineThickness(Item::itemOutlineThickness);
}

bool DropDownList::Item::onItem(int x, int y) const noexcept
{
    auto bounds = itemRect_.getGlobalBounds();

    return bounds.left < x && x < bounds.left + bounds.width &&
        bounds.top < y && y < bounds.top + bounds.height;
}

void DropDownList::Item::highlightItem(bool highlight) noexcept
{
    Color outlineColor = highlight ? gl::BLUE : gl::GREEN;
    itemRect_.setOutlineColor(outlineColor);
}

void DropDownList::Item::swap(Item& other) noexcept
{
    std::swap(this->locale_, other.locale_);
    std::swap(this->texture_, other.texture_);

    this->itemRect_.setTexture(this->texture_.get());
    other.itemRect_.setTexture(other.texture_.get());
}
