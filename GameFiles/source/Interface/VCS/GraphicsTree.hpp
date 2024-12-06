#pragma once

#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../../VersionControl/Commit.hpp"

using namespace sf;

class GraphicsTree
{
public:

    GraphicsTree(const std::vector<Commit>&) noexcept;

    GraphicsTree(const GraphicsTree&) noexcept = default;

    GraphicsTree(GraphicsTree&&) noexcept = default;

    GraphicsTree& operator=(const GraphicsTree&) noexcept = default;

    GraphicsTree& operator=(GraphicsTree&&) noexcept = default;

    ~GraphicsTree() noexcept = default;

public:

    void processTree() noexcept;

private:

    // branchNumber and Commits of this branch
    std::unordered_map<std::size_t, std::vector<Commit>> tree_;
};
