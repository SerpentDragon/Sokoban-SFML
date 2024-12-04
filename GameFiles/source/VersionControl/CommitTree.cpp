#include "CommitTree.h"

// CommitTree class

void CommitTree::addCommit(const Commit& commit) noexcept
{
    tree_.insert({ commit.commit_, commit });
}

const std::unordered_map<UI, CommitTree::Commit>& CommitTree::getCommits() const noexcept 
{ 
    return tree_; 
}

std::size_t CommitTree::getSize() const noexcept
{
    return tree_.size();
}


// Commit class

CommitTree::Commit::Commit(std::size_t commit, std::size_t parent, 
    std::size_t branch, UI money, const std::vector<COORDINATE>& coordinates) noexcept
    : commit_(commit), parent_(parent), branch_(branch), 
    money_(money), coordinates_(coordinates)
{

}

std::ostream& operator<<(std::ostream& os, const CommitTree::Commit& commit)
{
    os << commit.commit_ << ' ' << commit.parent_ << ' ';
    os << commit.branch_ << ' ' << commit.money_ << ' ';

    for(const auto& coord : commit.coordinates_)
    {
        os << coord.first << ' ' << coord.second << ' ';
    }

    os << '\n';

    return os;
}

bool CommitTree::Commit::operator=(const CommitTree::Commit& oth) const noexcept
{
    return this->money_ == oth.money_ && this->branch_ == oth.branch_ 
        && this->coordinates_ == oth.coordinates_;
}

UI CommitTree::Commit::getBranch() const noexcept
{
    return branch_;
}
