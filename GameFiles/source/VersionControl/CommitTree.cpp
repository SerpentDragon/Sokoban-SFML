#include "CommitTree.hpp"

// CommitTree class

void CommitTree::addCommit(const Commit& commit) noexcept
{
    tree_.insert({ commit.commit_, commit });
}

const std::unordered_map<UI, Commit>& CommitTree::getCommits() const noexcept 
{ 
    return tree_; 
}

std::size_t CommitTree::getSize() const noexcept
{
    return tree_.size();
}
