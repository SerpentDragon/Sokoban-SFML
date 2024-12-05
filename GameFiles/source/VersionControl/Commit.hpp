#pragma once

#include <vector>
#include <ostream>

using UI = unsigned int;
using COORDINATE = std::pair<int, int>;

struct Commit
{
public:

    Commit(std::size_t, std::size_t, std::size_t, UI, const std::vector<COORDINATE>&) noexcept;

    Commit(const Commit&) noexcept = default;

    Commit(Commit&&) noexcept = default;

    Commit& operator=(const Commit&) noexcept = default;

    Commit& operator=(Commit&&) noexcept = default;

    ~Commit() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Commit& commit);

    bool operator=(const Commit&) const noexcept;

public:

    std::size_t commit_;
    std::size_t parent_;
    std::size_t branch_;

    UI money_;

    std::vector<COORDINATE> coordinates_;
};
