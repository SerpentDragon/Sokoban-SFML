#include "Commit.hpp"

Commit::Commit(std::size_t commit, std::size_t parent, 
    std::size_t branch, UI money, const std::vector<COORDINATE>& coordinates) noexcept
    : commit_(commit), parent_(parent), branch_(branch), 
    money_(money), coordinates_(coordinates)
{

}

std::ostream& operator<<(std::ostream& os, const Commit& commit)
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

bool Commit::operator=(const Commit& oth) const noexcept
{
    return this->money_ == oth.money_ && this->branch_ == oth.branch_ 
        && this->coordinates_ == oth.coordinates_;
}
