#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <string_view>
#include "CommitTree.hpp"

namespace fs = std::filesystem;

class VersionControlSystem
{
public:

    VersionControlSystem() noexcept = default;

    VersionControlSystem(const VersionControlSystem&) = delete;

    VersionControlSystem(VersionControlSystem&&) noexcept = default;

    VersionControlSystem& operator=(const VersionControlSystem&) = delete;

    VersionControlSystem& operator=(VersionControlSystem&&) noexcept = default;

    ~VersionControlSystem() noexcept;

public:

    void init(int) noexcept;

    const Commit* commit(UI, const std::vector<COORDINATE>&) noexcept;

    std::vector<Commit> getCommits() const noexcept;

    const Commit* setNewCurrentState(std::size_t) noexcept;

    const Commit* getCurrentState() const noexcept;

private:

    void loadCommitTreeFromFile() noexcept;

    void loadCurrentStateFromFile() noexcept;

    void saveCommitToFile(const Commit&) const noexcept;

    void saveCurrentStateToFile() const noexcept;

private:

    unsigned int level_;

    // these fields must be updated during game process!
    std::size_t currentCommitState_;
    std::size_t currentBranch_;

    std::size_t branchesCounter_;

    std::string dir_;
    std::string treeFilename_;
    std::string stateFilename_;

    CommitTree tree_;

    // list of 'child'-commits for every commit
    std::map<std::size_t, std::vector<const Commit*>> children_;
};
