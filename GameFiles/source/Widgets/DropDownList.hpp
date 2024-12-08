#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../settings/settings.h"
#include "../Managers/TextureManager.hpp"


using namespace sf;

class DropDownList
{
public:

    DropDownList(std::shared_ptr<RenderWindow>) noexcept;

    void drawList() noexcept;

    std::string_view isPressed() noexcept;

private:

    bool onList(int, int) const noexcept;

    void createItems() noexcept;

    DropDownList(const DropDownList&) noexcept = delete;

    DropDownList(DropDownList&&) noexcept = delete;

    DropDownList& operator=(const DropDownList&) noexcept = delete;

    DropDownList& operator=(DropDownList&&) noexcept = delete;

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

        Item(int, int, const int, std::shared_ptr<Texture>, std::string_view) noexcept;

        bool onItem(int, int) const noexcept;

        void highlightItem(bool) noexcept;

        void swap(Item&) noexcept;

    public:

        static int itemOutlineThickness;

    public:

        RectangleShape itemRect_;
        std::shared_ptr<Texture> texture_;
        std::string_view locale_;
    };

    std::vector<Item> items_;
};
