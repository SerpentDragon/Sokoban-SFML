#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class GraphicsTree
{
public:

    GraphicsTree() noexcept = default;

    GraphicsTree(const GraphicsTree&) noexcept = default;

    GraphicsTree(GraphicsTree&&) noexcept = default;

    GraphicsTree& operator=(const GraphicsTree&) noexcept = default;

    GraphicsTree& operator=(GraphicsTree&&) noexcept = default;

    ~GraphicsTree() noexcept = default;

private:

    
};
