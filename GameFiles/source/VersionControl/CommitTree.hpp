#pragma once

#include "Commit.hpp"
#include <unordered_map>

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

    const std::unordered_map<UI, Commit>& getCommits() const noexcept;

    std::size_t getSize() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Commit&);

private:

    std::unordered_map<UI, Commit> tree_;
};
