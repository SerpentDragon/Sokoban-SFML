#include "GraphicsTree.hpp"

#include <iostream>

GraphicsTree::GraphicsTree(const std::vector<Commit>& commits) noexcept
{
    // here we get 'parent' for each commit
    std::vector<std::size_t> parents(commits.size());
    for(std::size_t i = 0; i < commits.size(); i++)
    {
        parents[i] = commits[i].branch_;
    }

    std::sort(parents.begin(), parents.end());

    // here we need to get duplicated values - from these
    // commits new branches are originates
    std::vector<std::size_t> duplicate_parents;
    for(std::size_t i = 0; i < parents.size() - 1; i++)
    {
        if(parents[i] == parents[i + 1])
        {
            duplicate_parents.emplace_back(parents[i]);
        }
    }

    for(std::size_t i = 0; i < duplicate_parents.size(); i++)
    {
        std::cout << duplicate_parents[i] << ' ';
    }
    std::cout << std::endl;
}
