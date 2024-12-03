#include "CommitTree.h"

// CommitTree class

void CommitTree::addCommit(const Commit& commit) noexcept
{
    tree_.insert({ commit.commit_, commit });
}

std::unordered_map<UI, CommitTree::Commit> CommitTree::getCommits() const noexcept 
{ 
    return tree_; 
}

std::size_t CommitTree::getSize() const noexcept
{
    return tree_.size();
}


// Commit class

CommitTree::Commit::Commit(std::size_t commit, std::size_t parent, 
    UI money, const std::vector<COORDINATE>& coordinates) noexcept
    : commit_(commit), parent_(parent), 
    money_(money), coordinates_(coordinates)
{

}

std::ostream& operator<<(std::ostream& os, const CommitTree::Commit& commit)
{
    os << commit.commit_ << ' ' << commit.parent_ << ' ';
    os << commit.money_ << ' ';

    for(const auto& coord : commit.coordinates_)
    {
        os << coord.first << ' ' << coord.second << ' ';
    }

    os << '\n';

    return os;
}

bool CommitTree::Commit::operator=(const CommitTree::Commit& oth) const noexcept
{
    return this->money_ == oth.money_ 
        && this->coordinates_ == oth.coordinates_;
}