#include "GraphicsTree.hpp"

GraphicsTree::GraphicsTree(std::shared_ptr<RenderWindow> window, 
    const std::vector<Commit>& commits) noexcept : window_(window),
    currentState_(0)
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
        hierarchy_[i].color = generateRandomColor();
    }

    // set default values for graphic tree
    for(std::size_t i = 1; i <= commits_.size(); i++)
    {
        tree_[i] = CircleShape(GT::commitSize);
        tree_[i].setOutlineThickness(3);
        tree_[i].setOutlineColor(hierarchy_[commits_[i].branch].color);
    }

    // !!!!
    tree_[tree_.size()].setFillColor(tree_[tree_.size()].getOutlineColor());
    currentState_ = tree_.size();
    
    lines_.resize(commits_.size() - 1);
    for(std::size_t i = 0; i < lines_.size(); i++)
    {
        lines_[i].first.color = hierarchy_[commits_[i + 2].branch].color;
        lines_[i].second.color = lines_[i].first.color;
    }

    calculatePositions();
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
            auto& children = hierarchy_[commits[it->first].branch_].children;
            children.insert(children.end(), it->second.begin(), it->second.end());

            hierarchy_[commits[it->first].branch_].commit = it->first;
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
    int leftBranchXPos = GT::zeroLevelXPos - (hierarchy_.size() / 2) * GT::branchInterval;

    if (tree_.empty()) return;

    tree_[1].setPosition(
        VCSWIN::VCSWindowXPos + GT::zeroLevelXPos, 
        GT::zeroLevelYPos);

    for(std::size_t i = 2; i <= tree_.size(); i++)
    {
        // setting current position for the commit
        tree_[i].setPosition(
            VCSWIN::VCSWindowXPos + leftBranchXPos + hierarchy_[commits_[i].branch].position * GT::branchInterval, 
            VCSWIN::VCSWindowYPos + GT::zeroLevelYPos - static_cast<int>(commits_[i].level) * GT::commitInterval);
    }

    for(std::size_t i = 0; i < lines_.size(); i++)
    {
        auto [x1, y1] = tree_[commits_[i + 2].parent].getPosition();
        lines_[i].first.position = { x1 + GT::commitSize, y1 + GT::commitSize};

        auto [x2, y2] = tree_[i + 2].getPosition();
        lines_[i].second.position = { x2 + GT::commitSize, y2 + GT::commitSize};
    }
}

Color GraphicsTree::generateRandomColor() noexcept
{
    return { 
            static_cast<Uint8>(rand() % 101 + 100),
            static_cast<Uint8>(rand() % 101 + 100),
            static_cast<Uint8>(rand() % 101 + 100)
        };
}

void GraphicsTree::addCommit(const Commit& commit) noexcept
{
    CommitInfo cmti {
        .parent = commit.parent_,
        .branch = commit.branch_,
        .level = commits_.contains(commit.parent_) ? 
            commits_[commit.parent_].level + 1 : 0
        };

    commits_.insert({ commit.commit_, cmti });

    // here we should check whether new commit is in new branch
    // if it is, we should create that branch
    if (cmti.branch > hierarchy_.size())
    {
        if (!hierarchy_.empty())
        {

            hierarchy_[cmti.branch].commit = cmti.parent;

            auto& children = hierarchy_[commits_[cmti.parent].branch].children;
            if (children.empty())
            {
                children.emplace_back(cmti.branch);
            }
            else
            {
                for(auto it = children.cbegin(); it != children.cend(); it++)
                {
                    if (hierarchy_[*it].commit != cmti.parent 
                        || it == children.cend() - 1)
                    {
                        children.insert(it, cmti.branch);
                        break;
                    }
                }
            }
        }
        else
        {
            hierarchy_[commit.branch_].commit = 1;
        }

        defineBranchesDrawOrder();

        hierarchy_[commit.branch_].children = {};
        hierarchy_[commit.branch_].color = generateRandomColor();
    }

    if (!tree_.empty())
    {
        lines_.emplace_back(std::pair{ Vertex(), Vertex() });
        lines_.back().first.color = hierarchy_[commit.branch_].color;
        lines_.back().second.color = lines_.back().first.color;
    }

    CircleShape cs(GT::commitSize);
    cs.setOutlineThickness(3);
    cs.setOutlineColor(hierarchy_[commit.branch_].color);
    tree_[commit.commit_] = cs;

    if (tree_.contains(currentState_))
    {
        tree_[currentState_].setFillColor(Color::White);
    }
    currentState_ = commit.commit_;
    tree_[currentState_].setFillColor(hierarchy_[commit.branch_].color);
    
    calculatePositions();
}

void GraphicsTree::displayTree() noexcept
{
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

void GraphicsTree::moveTree(int dx, int dy) noexcept
{
    GT::zeroLevelXPos += dx;
    GT::zeroLevelYPos += dy;

    calculatePositions();
}

std::size_t GraphicsTree::commitIsPressed(int x, int y) noexcept
{
    for(auto it = tree_.cbegin(); it != tree_.cend(); it++)
    {
        if (it->second.getGlobalBounds().contains(x, y))
        {
            tree_[currentState_].setFillColor(Color::White);
            currentState_ = it->first;
            tree_[currentState_].setFillColor(it->second.getOutlineColor());
            return it->first;
        }
    }

    return 0;
}

void GraphicsTree::updateCurrentState(std::size_t newState) noexcept
{
    tree_[currentState_].setFillColor(Color::White);
    currentState_ = newState;
    tree_[currentState_].setFillColor(hierarchy_[commits_[newState].branch].color);
}
