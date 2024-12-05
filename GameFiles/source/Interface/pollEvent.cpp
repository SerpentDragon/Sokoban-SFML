#include "pollEvent.hpp"

bool showWarning(std::shared_ptr<RenderWindow> window, const String& str) noexcept
{
    RectangleShape warningWindow(
            Vector2f(DR::warningWindowWidth, DR::warningWindowHeight));
    warningWindow.setFillColor(gl::DARK_BLUE);
    warningWindow.setPosition(DR::warningWindowXPos, 
        DR::warningWindowYPos);

    String continueText = Localizer::translate(STRING::Continue);

    Text mainMessage(str, gl::font, DR::warningTextSize);
    mainMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - mainMessage.getGlobalBounds().width) / 2, 
        DR::warningWindowYPos + gl::size / 3);
    
    Text continueMessage(continueText, gl::font, DR::warningTextSize);
    continueMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - continueMessage.getGlobalBounds().width) / 2,
        mainMessage.getGlobalBounds().top + mainMessage.getGlobalBounds().height + gl::size / 4);

    Button yesButton(window, Text(Localizer::translate(STRING::Yes), gl::font, 
        0.0225 * gl::Width), DR::yesButtonXPos, DR::yesButtonYPos, 
        DR::warningButtonWidth, DR::warningButtonHeight, gl::WHITE, gl::BLUE);
    yesButton.setTextColor(gl::DARK_BLUE);
    
    Button noButton(window, Text(Localizer::translate(STRING::No), gl::font, 
        0.0225 * gl::Width), DR::noButtonXPos, DR::noButtonYPos, 
        DR::warningButtonWidth, DR::warningButtonHeight, gl::WHITE, gl::BLUE);
    noButton.setTextColor(gl::DARK_BLUE);

    Event event;

    while(true)
    {
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed: // we shouldn't process these events because otherwise a lot of warning windows will be opened
                case Event::KeyPressed:
                    break;
            }
        }

        window->draw(warningWindow);
        window->draw(mainMessage);
        window->draw(continueMessage);
        yesButton.drawButton();
        noButton.drawButton();

        if (yesButton.isPressed()) return true;
        else if (noButton.isPressed()) return false;

        window->display();
    }
}

void pollEvents(std::shared_ptr<RenderWindow> window) noexcept
{
    Event event;

    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                    if (showWarning(window, 
                        Localizer::translate(STRING::SureToExit))) window->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    if (showWarning(window, 
                        Localizer::translate(STRING::SureToExit))) window->close();
                return;
        }
        window->clear();
    }
}
