#include "VersionControlSystem.hpp"

VersionControlSystem::~VersionControlSystem()
{
    saveCurrentStateToFile();
}

void VersionControlSystem::init(int level) noexcept
{
    this->level_ = level;
    this->currentCommitState_ = 1;
    this->currentBranch_ = 1;
    this->branchesCounter_ = 0;
    this->root_ = "app_data/.vcs/";
    this->dir_ = root_ + std::to_string(level_);
    this->treeFilename_ = dir_ + "/tree";
    this->stateFilename_ = dir_ + "/commit";
    this->children_.clear();

    if (!fs::exists(dir_))
    {
        fs::create_directories(dir_);
    }

    this->tree_ = CommitTree();

    loadCommitTreeFromFile();
    loadCurrentStateFromFile();
}

void VersionControlSystem::reset() noexcept
{
    this->level_ = 0;
    this->currentCommitState_ = 1;
    this->currentBranch_ = 1;
    this->branchesCounter_ = 0;
    this->children_.clear();

    fs::remove_all(root_);
}

std::pair<const Commit*, bool> VersionControlSystem::commit(unsigned int money, 
    const std::vector<COORDINATE>& coordinates) noexcept
{
    auto commitNum = tree_.getSize() + 1;

    Commit commit{ commitNum, currentCommitState_, 
        currentBranch_, money, coordinates };

    const auto& tree = tree_.getCommits();
    
    try
    {
        if (!tree.empty())
        {
            if(commit == tree.at(currentCommitState_)) return { nullptr, false };

            // info about 'children' of current state
            const auto& currentStateChildren = children_[tree.at(currentCommitState_).commit_];

            // has 'children' 
            if(!currentStateChildren.empty())
            {
                for(std::size_t i = 0; i < currentStateChildren.size(); i++)
                {
                    if (commit == *currentStateChildren[i])
                    {
                        // may be we chould jump to that commit
                        return { currentStateChildren[i], false };
                    }
                }

                branchesCounter_++;
                commit.branch_ = branchesCounter_;
                currentBranch_ = branchesCounter_;
            }
            // has no 'children'
            else
            {
                // we just add a new commit
                commit.branch_ = currentBranch_;
            }
        }
        else
        {
            currentBranch_ = commit.branch_;
            branchesCounter_++;
        }
    }
    catch(const std::out_of_range& ex)
    {
        currentCommitState_ = 1;
        currentBranch_ = 1;

        return { nullptr, false };
    }

    currentCommitState_ = commit.commit_;

    auto ptr = tree_.addCommit(commit);

    if (!tree.empty() && ptr != nullptr && commit.commit_ != 1) 
    {
        children_[commit.parent_].emplace_back(ptr);
    }

    saveCommitToFile(commit);

    return { ptr, true };

    /* 
        before createing a new commit we must:

        1. verify our new commit doesn't equal to the current one
            
            1.1 it equals -> no new commit
            1.2 jump to point 2

        2. check if the current state has 'children'

            2.1 current commit has no 'children' -> our commit is the new one!

            2.2 current commit has at least one 'child' -> we should check
            if our commit is equal to one of these 'children'

                2.2.1 it equals -> it's just an already existing state (no new commit) 
                (may be we should jump to it - change currentCommitState_)

                2.2.2 it doesn't -> we create a new branch! (change currentBranch_
                and branchesCounter_)

        Furtheremore: everey single move of our player we should check if the current
        state of the game is equal one of the 'children' (if they exist) of current commit
        (we need to do it if we want to automatically change the current state)
    */ 
}

std::vector<Commit> VersionControlSystem::getCommits() const noexcept
{
    auto commitTree = tree_.getCommits();

    std::vector<Commit> commits(commitTree.size());

    std::size_t i = 0;
    for(auto it = commitTree.cbegin(); it != commitTree.cend(); it++, i++)
    {
        commits[i] = it->second;
    }

    return commits;
}

const Commit* VersionControlSystem::setNewCurrentState(std::size_t newState) noexcept
{
    try
    {
        currentCommitState_ = newState;
        currentBranch_ = tree_.getCommits().at(newState).branch_;

        return &(tree_.getCommits().at(newState));
    }
    catch(const std::out_of_range&)
    {
        return nullptr;
    }
}

const Commit* VersionControlSystem::getCurrentState() const noexcept
{
    try
    {
        return &tree_.getCommits().at(currentCommitState_);
    }
    catch(const std::out_of_range&)
    {
        return nullptr;
    }
}

void VersionControlSystem::loadCommitTreeFromFile() noexcept
{
    std::fstream treeFile(treeFilename_, std::ios_base::in);
    if(!treeFile.is_open()) return;

    // commit info
    std::size_t commit = 0;
    std::size_t parent = 0;
    std::size_t branch = 0;

    // amount of money
    unsigned int money = 0;
    // coordinates
    unsigned int x = 0, y = 0;
    std::vector<std::pair<int, int>> coordinates;

    std::string line;
    while(std::getline(treeFile, line))
    {
        std::stringstream commit_(line);

        commit_ >> commit >> parent >> branch;
        commit_ >> money;
        
        while(commit_ >> x)
        {
            commit_ >> y;

            coordinates.emplace_back(std::pair{ x, y });
        }

        Commit newCommit{ commit, parent, branch, money, coordinates };
    
        if (auto ptr = tree_.addCommit(newCommit); ptr != nullptr)
        {
            children_[parent].emplace_back(ptr);
        }

        branchesCounter_ = std::max(branchesCounter_, branch);

        coordinates.clear();
    }

    treeFile.close();
}

void VersionControlSystem::loadCurrentStateFromFile() noexcept
{
    std::fstream stateFile(stateFilename_, std::ios_base::in);
    if(!stateFile.is_open()) 
    {
        // if we face error opening file, we need to fill 
        // this parameter manually
        currentCommitState_ = tree_.getSize() ? tree_.getSize() : 1;
        return;
    }

    // here we read current commit
    stateFile >> currentCommitState_;

    stateFile.close();

    if(currentCommitState_ > tree_.getSize()) currentCommitState_ = 1;

    // here we get branch number of current commit
    try
    {
        currentBranch_ = tree_.getCommits().at(currentCommitState_).branch_;
    }
    catch(const std::out_of_range& ex)
    {
        currentBranch_ = 1;
        currentCommitState_ = 1;
    }
}

void VersionControlSystem::saveCommitToFile(const Commit& commit) const noexcept
{
    std::fstream treeFile(treeFilename_, std::ios_base::app);
    if(!treeFile.is_open()) return;

    // add new commit to the tree file
    treeFile << commit;

    treeFile.close();
}

void VersionControlSystem::saveCurrentStateToFile() const noexcept
{
    std::fstream stateFile(stateFilename_, std::ios_base::out);
    if(!stateFile.is_open()) return;

    // update current commit
    stateFile << currentCommitState_;

    stateFile.close();
}
