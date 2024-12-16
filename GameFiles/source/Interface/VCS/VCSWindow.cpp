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
}

void VCSWindow::addCommit(const Commit& commit) noexcept
{
    tree_.addCommit(commit);
}

void VCSWindow::displayVCSWIndow() noexcept
{
    window_->draw(windowRect_);

    tree_.displayTree();
}

std::size_t VCSWindow::checkCommitIsPressed(int x, int y) noexcept
{
    return tree_.commitIsPressed(x, y);
}

void VCSWindow::updateCurrentState(std::size_t newState) noexcept
{
    tree_.updateCurrentState(newState);
}