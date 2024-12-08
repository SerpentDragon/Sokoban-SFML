#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../settings/settings.h"
#include "../../VersionControl/Commit.hpp"

using namespace sf;
namespace GT = VCSWIN::GT;

class GraphicsTree
{
public:

    GraphicsTree() noexcept = default;

    GraphicsTree(std::shared_ptr<RenderWindow>, const std::vector<Commit>&) noexcept;

    GraphicsTree(const GraphicsTree&) noexcept = default;

    GraphicsTree(GraphicsTree&&) noexcept = default;

    GraphicsTree& operator=(const GraphicsTree&) noexcept = default;

    GraphicsTree& operator=(GraphicsTree&&) noexcept = default;

    ~GraphicsTree() noexcept = default;

private:

    void generateBranchesHierarchy(const std::vector<Commit>&) noexcept;

    void defineBranchesDrawOrder(std::size_t) noexcept;

    void processTree() noexcept;

    void calculatePositions() noexcept;

public:

    void displayTree() noexcept;

private:

    struct CommitInfo
    {
        std::size_t parent;
        std::size_t branch;
        unsigned int level; // 'level' on which the commit will be drawn
    };

    struct BranchInfo
    {
        std::vector<std::size_t> children; // list of 'child' branches
        Color color; // the color of the branch
    };

    using HIERARCHY = std::map<std::size_t, BranchInfo>;

private:

    // the window on which the tree will be drawn
    std::shared_ptr<RenderWindow> window_;

    // commit and it's info
    std::map<std::size_t, CommitInfo> commits_;

    // graphic representation of commits
    std::map<std::size_t, CircleShape> tree_;

    // defines which branch creates which branches
    // format = branch_id : <BranchInfo>
    HIERARCHY hierarchy_;

    // order in which branches must be drawn
    std::vector<std::size_t> order_;
};
