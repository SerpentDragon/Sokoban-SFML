#include "DropDownList.hpp"

// DropdownList class

DropDownList::DropDownList(std::shared_ptr<RenderWindow> window)
    : window_(window), list_(Vector2f(gl::size, gl::size)),
    x_(window->getSize().x - gl::size * 1.5), y_(gl::size / 2),
    width_(gl::size), height_(gl::size)
{
    list_.setFillColor(gl::GREEN);
    list_.setPosition(x_, y_);

    createItems();
}

void DropDownList::drawList()
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

std::string DropDownList::isPressed()
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
                    std::string locale = items_[i].locale_;
                    items_[i].swap(items_[0]);
                    return locale;
                }
            }
        }
    }

    return "";
}

bool DropDownList::onList(int x, int y) const
{
    return x_ <= x && x <= x_ + width_ 
        && y_ <= y && y <= y_ + height_;
}

void DropDownList::createItems()
{
    const int itemSize = gl::size - Item::itemOutlineThickness * 2;
    
    items_ = {
        { 0, 0, itemSize, 
            std::make_shared<Texture>(*TextureManager::getManager()->
                getTexture("textures/languages/en_UK")),
            "en_UK" },

        { 0, 0, itemSize, 
            std::make_shared<Texture>(*TextureManager::getManager()->
                getTexture("textures/languages/ru_RU")),
            "ru_RU" }, 

        { 0, 0, itemSize, 
            std::make_shared<Texture>(*TextureManager::getManager()->
                getTexture("textures/languages/de_DE")),
            "de_DE" },

        { 0, 0, itemSize, 
            std::make_shared<Texture>(*TextureManager::getManager()->
                getTexture("textures/languages/fr_FR")),
            "fr_FR" }
    };

    for(size_t i = 0; i < items_.size(); i++)
    {
        items_[i].itemRect_.setPosition(x_ + Item::itemOutlineThickness,
            y_ + gl::size * i + Item::itemOutlineThickness);
    }
}


// Items class

int DropDownList::Item::itemOutlineThickness = gl::Width / 400;

DropDownList::Item::Item(int x, int y, const int size, 
    std::shared_ptr<Texture> texture, const std::string& locale)
    : itemRect_(Vector2f(size, size)), locale_(locale)
{
    texture_ = texture;
    
    itemRect_.setPosition(x, y);
    itemRect_.setTexture(&(*texture));
    itemRect_.setOutlineThickness(Item::itemOutlineThickness);
}

bool DropDownList::Item::onItem(int x, int y) const
{
    auto bounds = itemRect_.getGlobalBounds();

    return bounds.left < x && x < bounds.left + bounds.width &&
        bounds.top < y && y < bounds.top + bounds.height;
}

void DropDownList::Item::highlightItem(bool highlight)
{
    Color outlineColor = highlight ? gl::BLUE : gl::GREEN;
    itemRect_.setOutlineColor(outlineColor);
}

void DropDownList::Item::swap(Item& other)
{
    std::swap(this->locale_, other.locale_);
    std::swap(this->texture_, other.texture_);

    this->itemRect_.setTexture(&(*this->texture_));
    other.itemRect_.setTexture(&(*other.texture_));
}
