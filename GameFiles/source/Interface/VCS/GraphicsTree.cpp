#include "GraphicsTree.hpp"

GraphicsTree::GraphicsTree(const std::vector<Commit>& commits) noexcept
{
    if (!commits.size()) return;

    generateBranchesHierarchy(commits);

    // we always start to draw the tree from the 1st branch
    // hence, we append it to the list
    order_.emplace_back(1);

    defineBranchesDrawOrder(1);

    // remember the most important info about commits
    for(std::size_t i = 0; i < commits.size(); i++)
    {
        const auto& commit = commits[i];

        tree_[commits[i].commit_] = { 
            .parent = commit.parent_, 
            .branch = commit.branch_, 
            .level = 0 
        };
    }

    processTree();
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
            auto& branch = hierarchy_[commits[it->first].branch_];
            branch.insert(branch.end(), it->second.begin(), it->second.end());
        }
    }
}

void GraphicsTree::defineBranchesDrawOrder(std::size_t branch) noexcept
{
    for(auto it = hierarchy_[branch].crbegin(); it != hierarchy_[branch].crend(); it++)
    {
        order_.emplace_back(*it);

        if(!hierarchy_[*it].empty())
        {
            defineBranchesDrawOrder(*it);
        }
    }
}

void GraphicsTree::processTree() noexcept
{
    // the 1st commit is always placed on the 0 level
    tree_[1].level = 0;

    for(std::size_t i = 2; i <= tree_.size(); i++)
    {
        tree_[i].level = tree_[tree_[i].parent].level + 1;
    }
}
