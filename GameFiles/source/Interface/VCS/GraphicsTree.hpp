#pragma once

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "../../VersionControl/Commit.hpp"

using namespace sf;

using HIERARCHY = std::map<std::size_t, std::vector<std::size_t>>;

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

    void generateBranchesHierarchy(const std::vector<Commit>&) noexcept;

    void defineBranchesDrawOrder(std::size_t) noexcept;

private:

    // branchNumber and Commits of this branch
    std::map<std::size_t, std::vector<Commit>> tree_;

    // defines which branch creates which branches
    // format = branch_id : <list_of_child_branches>
    HIERARCHY hierarchy_;

    // order in which branches must be drawn
    std::vector<std::size_t> order_;
};
