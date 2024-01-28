#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "../Managers/TextureManager.hpp"
#include "../Player/settings.h"

using namespace sf;

class DropDownList
{
public:

    DropDownList(RenderWindow*);

    ~DropDownList();

    void drawList();

    std::string isPressed();

private:

    bool onList(int, int) const;

    void createItems();

    DropDownList(const DropDownList&) = delete;

    DropDownList(DropDownList&&) = delete;

    DropDownList& operator=(const DropDownList&) = delete;

    DropDownList& operator=(DropDownList&&) = delete;

private:

    RenderWindow* window_;

    RectangleShape list_;

    int x_;
    int y_;
    int width_;
    int height_;

    class Item
    {
    public:

        Item(int, int, const int, const Texture*, const std::string&);

        bool onItem(int, int) const;

        void highlightItem(bool);

        void swap(Item&);

    public:

        constexpr static int itemOutlineThickness = 3;

    public:

        RectangleShape itemRect_;
        std::string locale_;
    };

    std::vector<Item> items_;
};
