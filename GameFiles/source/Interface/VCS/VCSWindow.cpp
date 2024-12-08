#include "VCSWindow.hpp"

VCSWindow::VCSWindow(std::shared_ptr<RenderWindow> window) noexcept
    : window_(window), windowRect_(Vector2f(gl::Width / 3, gl::Height)),
    closeButton_(window_, vcsw::closeButtonXPos, vcsw::closeButtonYPos, 
        vcsw::closeButtonSize, vcsw::closeButtonSize, 
        TextureManager::getManager().getTexture("textures/buttons/close"))
{
    windowRect_.setFillColor(gl::WHITE);
    windowRect_.setPosition(
        gl::Width - windowRect_.getGlobalBounds().width, 0);
}

void VCSWindow::setCommits(const std::vector<Commit>& commits) noexcept
{
    tree_ = GraphicsTree(window_, commits);
}

void VCSWindow::displayVCSWIndow() noexcept
{
    Event event;

    while(window_->isOpen())
    {
        while(window_->pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                {
                    break;
                }
            }   
        }
        
        window_->draw(windowRect_);

        tree_.displayTree();

        closeButton_.drawButton();

        if(closeButton_.isPressed())
        {
            break;
        }

        window_->display();
    }
}
