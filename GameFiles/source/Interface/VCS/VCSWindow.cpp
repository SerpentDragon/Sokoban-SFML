#include "VCSWindow.hpp"

VCSWindow::VCSWindow(std::shared_ptr<RenderWindow> window) noexcept
    : window_(window), tree_(window),
    windowRect_(Vector2f(vcsw::VCSWindowWidth, vcsw::VCSWindowHeight))
{
    windowRect_.setFillColor(gl::WHITE);
    windowRect_.setPosition(vcsw::VCSWindowXPos, vcsw::VCSWindowYPos);
}

void VCSWindow::setCommits(const std::vector<Commit>& commits) noexcept
{
    tree_ = GraphicsTree(window_, commits);

    // for(std::size_t i = 0; i < commits.size(); i++)
    // {
    //     tree_.addCommit(commits[i]);
    // }
}

void VCSWindow::addCommit(const Commit& commit) noexcept
{
    tree_.addCommit(commit);
}

#include <iostream>

void VCSWindow::displayVCSWIndow() noexcept
{
    window_->draw(windowRect_);

    std::cout << "BEFORE display TREE\n";

    tree_.displayTree();

    std::cout << "display TREE\n";
}

std::size_t VCSWindow::checkCommitIsPressed(int x, int y) noexcept
{
    return tree_.commitIsPressed(x, y);
}
