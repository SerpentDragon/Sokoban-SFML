#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"
#include "../Managers/TextureManager.hpp"


using namespace sf;

class DropDownList
{
public:

    DropDownList(std::shared_ptr<RenderWindow>);

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

    std::shared_ptr<RenderWindow> window_;

    RectangleShape list_;

    int x_;
    int y_;
    int width_;
    int height_;

    class Item
    {
    public:

        Item(int, int, const int, std::shared_ptr<Texture>, const std::string&);

        bool onItem(int, int) const;

        void highlightItem(bool);

        void swap(Item&);

    public:

        static int itemOutlineThickness;

    public:

        RectangleShape itemRect_;
        std::shared_ptr<Texture> texture_;
        std::string locale_;
    };

    std::vector<Item> items_;
};
