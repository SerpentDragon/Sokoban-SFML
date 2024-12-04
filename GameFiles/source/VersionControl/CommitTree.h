#pragma once

#include <vector>
#include <ostream>
#include <unordered_map>

using UI = unsigned int;
using COORDINATE = std::pair<int, int>;

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

    class Commit
    {
    public:

        Commit(std::size_t, std::size_t, std::size_t, UI, const std::vector<COORDINATE>&) noexcept;

        Commit(const Commit&) noexcept = default;

        Commit(Commit&&) noexcept = default;

        Commit& operator=(const Commit&) noexcept = default;

        Commit& operator=(Commit&&) noexcept = default;

        ~Commit() noexcept = default;

        friend std::ostream& operator<<(std::ostream& os, const Commit& commit);

        friend class CommitTree;

        bool operator=(const Commit&) const noexcept;

    public:

        UI getBranch() const noexcept;

    private:

        std::size_t commit_;
        std::size_t parent_;
        std::size_t branch_;

        UI money_;

        std::vector<COORDINATE> coordinates_;
    };

public:

    void addCommit(const Commit&) noexcept;

    const std::unordered_map<UI, CommitTree::Commit>& getCommits() const noexcept;

    std::size_t getSize() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Commit&);

private:

    std::unordered_map<UI, Commit> tree_;
};
