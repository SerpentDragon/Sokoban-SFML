#include "CommitTree.hpp"

const Commit* CommitTree::addCommit(const Commit& commit) noexcept
{
    auto [it, res] = tree_.insert({ commit.commit_, commit });

    return res ? &(*it).second : nullptr;
}

const std::map<std::size_t, Commit>& CommitTree::getCommits() const noexcept 
{ 
    return tree_; 
}

std::size_t CommitTree::getSize() const noexcept
{
    return tree_.size();
}
