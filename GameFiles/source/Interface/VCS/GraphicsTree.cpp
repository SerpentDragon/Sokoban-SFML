#include "GraphicsTree.hpp"

GraphicsTree::GraphicsTree(std::shared_ptr<RenderWindow> window, 
    const std::vector<Commit>& commits) noexcept : window_(window)
{
    if (!commits.size()) return;

    generateBranchesHierarchy(commits);
    defineBranchesDrawOrder();

    // remember the most important info about commits
    for(std::size_t i = 0; i < commits.size(); i++)
    {
        const auto& commit = commits[i];

        commits_[commits[i].commit_] = { 
            .parent = commit.parent_, 
            .branch = commit.branch_, 
            .level = 0 
        };
    }

    processTree();

    for(std::size_t i = 1; i < hierarchy_.size(); i++)
    {
        hierarchy_[i].color = { 
            static_cast<Uint8>(rand() % 101 + 100),
            static_cast<Uint8>(rand() % 101 + 100),
            static_cast<Uint8>(rand() % 101 + 100)
        };
    }

    // set default values for graphic tree
    for(std::size_t i = 1; i <= commits_.size(); i++)
    {
        tree_[i] = CircleShape(GT::commitSize);
        tree_[i].setOutlineThickness(3);
        tree_[i].setOutlineColor(hierarchy_[commits_[i].branch].color);
    }
    
    lines_.resize(commits_.size() - 1);
    for(std::size_t i = 0; i < lines_.size(); i++)
    {
        lines_[i].first.color = hierarchy_[commits_[i + 2].branch].color;
        lines_[i].second.color = lines_[i].first.color;
    }
}

void GraphicsTree::generateBranchesHierarchy(const std::vector<Commit>& commits) noexcept
{
    // here we keep info about commits and branches it creates
    // format = commit_id : <list_of_branches>
    std::map<std::size_t, std::vector<std::size_t>> fork;

    for(std::size_t i = 0; i < commits.size(); i++)
    {
        auto parent = commits[i].parent_;

        if(commits[i].branch_ != commits[parent - 1].branch_)
        {
            fork[parent].emplace_back(commits[i].branch_);
        }
    }

    for(auto it = fork.cbegin(); it != fork.cend(); it++)
    {
        if(!it->second.empty())
        {
            // branch in which the commit in question is located
            auto& branch = hierarchy_[commits[it->first].branch_].children;
            branch.insert(branch.end(), it->second.begin(), it->second.end());
        }
    }
}

void GraphicsTree::defineBranchesDrawOrder(std::vector<std::size_t>& order, 
    std::size_t branch) noexcept
{
    const auto& children = hierarchy_[branch].children;

    for(auto it = children.crbegin(); it != children.crend(); it++)
    {
        order.emplace_back(*it);

        if(!children.empty())
        {
            defineBranchesDrawOrder(order, *it);
        }
    }
}

void GraphicsTree::defineBranchesDrawOrder() noexcept
{
    // order in which branches must be drawn
    std::vector<std::size_t> order;

    // we always start to draw the tree from the 1st branch
    // hence, we append it to the list
    order.emplace_back(1);

    defineBranchesDrawOrder(order, 1);

    for(std::size_t i = 0; i < order.size(); i++)
    {
        hierarchy_[order[i]].position = i;
    }
}

void GraphicsTree::processTree() noexcept
{
    // the 1st commit is always placed on the 0 level
    commits_[1].level = 0;

    for(std::size_t i = 2; i <= commits_.size(); i++)
    {
        commits_[i].level = commits_[commits_[i].parent].level + 1;
    }
}

void GraphicsTree::calculatePositions() noexcept
{
    static int leftBranchXPos;

    leftBranchXPos = GT::zeroLevelXPos - (hierarchy_.size() / 2) * GT::branchInterval;

    tree_[1].setPosition(
        VCSWIN::VCSWindowXPos + GT::zeroLevelXPos, 
        GT::zeroLevelYPos);
    
    for(std::size_t i = 2; i <= tree_.size(); i++)
    {
        // setting current position for the commit
        tree_[i].setPosition(
            VCSWIN::VCSWindowXPos + leftBranchXPos + hierarchy_[commits_[i].branch].position * GT::branchInterval, 
            VCSWIN::VCSWindowYPos + GT::zeroLevelYPos - commits_[i].level * GT::commitInterval);

        // setting color to commit  according to the branch it belongs
        tree_[i].setOutlineColor(hierarchy_[commits_[i].branch].color);
    }

    for(std::size_t i = 0; i < lines_.size(); i++)
    {
        auto [x1, y1] = tree_[commits_[i + 2].parent].getPosition();
        lines_[i].first.position = { x1 + GT::commitSize, y1 + GT::commitSize};

        auto [x2, y2] = tree_[i + 2].getPosition();
        lines_[i].second.position = { x2 + GT::commitSize, y2 + GT::commitSize};
    }
}

void GraphicsTree::displayTree() noexcept
{
    // OPTIMIZATION: it should only be called 
    // when a player 'moves' tree on the screen
    // or a new commit has been added
    calculatePositions();

    for(auto line : lines_)
    {
        Vertex vtx[2] = { line.first , line.second };
        window_->draw(vtx, 2, Lines);
    }

    for(auto it = tree_.cbegin(); it != tree_.cend(); it++)
    {
        window_->draw(it->second);
    }
}
