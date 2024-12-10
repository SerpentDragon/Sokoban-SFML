#include "VCSWindow.hpp"

VCSWindow::VCSWindow(std::shared_ptr<RenderWindow> window) noexcept
    : window_(window), 
    windowRect_(Vector2f(vcsw::VCSWindowWidth, vcsw::VCSWindowHeight))
{
    windowRect_.setFillColor(gl::WHITE);
    windowRect_.setPosition(vcsw::VCSWindowXPos, vcsw::VCSWindowYPos);
}

void VCSWindow::setCommits(const std::vector<Commit>& commits) noexcept
{
    tree_ = GraphicsTree(window_, commits);
}

void VCSWindow::displayVCSWIndow() noexcept
{
    window_->draw(windowRect_);

    tree_.displayTree();
}
