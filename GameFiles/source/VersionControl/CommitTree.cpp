#include "CommitTree.hpp"

void CommitTree::addCommit(const Commit& commit) noexcept
{
    tree_.insert({ commit.commit_, commit });
}

const std::map<std::size_t, Commit>& CommitTree::getCommits() const noexcept 
{ 
    return tree_; 
}

std::size_t CommitTree::getSize() const noexcept
{
    return tree_.size();
}
