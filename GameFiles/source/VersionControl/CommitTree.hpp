#pragma once

#include <map>
#include "Commit.hpp"

using CommitList = std::map<std::size_t, Commit>;

class CommitTree
{
public:

    CommitTree() noexcept = default;

    CommitTree(const CommitTree&) noexcept = default;

    CommitTree(CommitTree&&) noexcept = default;

    CommitTree& operator=(const CommitTree&) noexcept = default;

    CommitTree& operator=(CommitTree&&) noexcept = default;

    ~CommitTree() noexcept = default;

public:

    const Commit* addCommit(const Commit&) noexcept;

    const CommitList& getCommits() const noexcept;

    std::size_t getSize() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Commit&);

private:

    // commitNumber and Commit itself
    CommitList tree_;
};
