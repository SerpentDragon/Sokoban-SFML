#pragma once

#include <map>
#include "Commit.hpp"

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

    void addCommit(const Commit&) noexcept;

    const std::map<std::size_t, Commit>& getCommits() const noexcept;

    std::size_t getSize() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Commit&);

private:

    // commitNumber and Commit itself
    std::map<std::size_t, Commit> tree_;
};
