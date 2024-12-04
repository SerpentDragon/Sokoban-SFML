#include "VCSWindow.hpp"

#include <cassert>

VCSWindow::VCSWindow(std::shared_ptr<RenderWindow> window) noexcept
    : window_(window), windowRect_(Vector2f(gl::Width / 3, gl::Height)),
    closeButton_(window_, gl::Width - gl::size / 2, 0, gl::size / 2, gl::size / 2, 
        TextureManager::getManager().getTexture("textures/buttons/close"))
{
    windowRect_.setFillColor(gl::WHITE);
    windowRect_.setPosition(
        gl::Width - windowRect_.getGlobalBounds().width, 0);
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

        closeButton_.drawButton();

        if(closeButton_.isPressed())
        {
            break;
        }

        window_->display();
    }
}
