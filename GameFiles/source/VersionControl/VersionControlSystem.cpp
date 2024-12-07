#include "VersionControlSystem.hpp"

VersionControlSystem::VersionControlSystem(int level) noexcept 
    : level_(level), currentCommitState_(1), currentBranch_(1), 
    branchesCounter_(0), dir_("app_data/.vcs/")
{
    dir_ += std::to_string(level);

    treeFilename_ = dir_ + "/tree";
    stateFilename_ = dir_ + "/commit";

    if (!fs::exists(dir_))
    {
        fs::create_directory(dir_);
    }

    loadCommitTreeFromFile();
    loadCurrentStateFromFile();
}

VersionControlSystem::~VersionControlSystem()
{
    saveCurrentStateToFile();
}

void VersionControlSystem::commit(unsigned int money, 
    const std::vector<COORDINATE>& coordinates) noexcept
{
    auto commitNum = tree_.getSize() + 1;

    Commit commit{ commitNum, currentCommitState_, 
        currentBranch_, money, coordinates };

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

    currentCommitState_ = commitNum;

    tree_.addCommit(commit);

    saveCommitToFile(commit);
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

        tree_.addCommit(newCommit);

        branchesCounter_ = std::max(branchesCounter_, branch);
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
        currentCommitState_ = tree_.getSize() ? tree_.getSize() : 0;
        return;
    }

    // here we read current commit
    stateFile >> currentCommitState_;

    stateFile.close();

    // here we get branch number of current commit
    try
    {
        currentBranch_ = tree_.getCommits().at(currentCommitState_).branch_;
    }
    catch(const std::out_of_range& e)
    {
        currentBranch_ = 0;
        currentCommitState_ = 0;
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
