#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string_view>
#include "CommitTree.h"

namespace fs = std::filesystem;

class VersionControlSystem
{
public:

    VersionControlSystem(int) noexcept;

    VersionControlSystem(const VersionControlSystem&) = delete;

    VersionControlSystem(VersionControlSystem&&) noexcept = default;

    VersionControlSystem& operator=(const VersionControlSystem&) = delete;

    VersionControlSystem& operator=(VersionControlSystem&&) noexcept = default;

    ~VersionControlSystem() noexcept;

public:

    void commit(UI, const std::vector<COORDINATE>&) noexcept;

private:

    void loadCommitTreeFromFile() noexcept;

    void loadCurrentStateFromFile() noexcept;

    void saveCommitToFile(const CommitTree::Commit&) const noexcept;

    void saveCurrentStateToFile() const noexcept;

private:

    unsigned int level_;

    unsigned int currentCommitState_;

    std::string dir_;
    std::string treeFilename_;
    std::string stateFilename_;

    CommitTree tree_;
};
