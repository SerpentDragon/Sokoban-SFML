#pragma once

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../VersionControl/Commit.hpp"

using namespace sf;

using HIERARCHY = std::map<std::size_t, std::vector<std::size_t>>;

class GraphicsTree
{
public:

    GraphicsTree() noexcept = default;

    GraphicsTree(const std::vector<Commit>&) noexcept;

    GraphicsTree(const GraphicsTree&) noexcept = default;

    GraphicsTree(GraphicsTree&&) noexcept = default;

    GraphicsTree& operator=(const GraphicsTree&) noexcept = default;

    GraphicsTree& operator=(GraphicsTree&&) noexcept = default;

    ~GraphicsTree() noexcept = default;

private:

    void generateBranchesHierarchy(const std::vector<Commit>&) noexcept;

    void defineBranchesDrawOrder(std::size_t) noexcept;

    void processTree() noexcept;

public:



private:

    struct CommitInfo
    {
        std::size_t parent;
        std::size_t branch;
        unsigned int level; // 'level' on which the commit will be drawn
    };

private:

    // commit and it's info
    std::map<std::size_t, CommitInfo> tree_;

    // defines which branch creates which branches
    // format = branch_id : <list_of_child_branches>
    HIERARCHY hierarchy_;

    // order in which branches must be drawn
    std::vector<std::size_t> order_;
};
