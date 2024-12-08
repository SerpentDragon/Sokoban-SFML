#include <SFML/Graphics.hpp>
#include "source/Interface/Interface.hpp"

using namespace sf;

int main()
{
    gl::initFont();
    
    auto window = std::make_shared<RenderWindow>(
        VideoMode(gl::Width, gl::Height), "Sokoban", Style::Close);
    window->setPosition(Vector2i((gl::ScreenWidth - gl::Width) / 2, 
        (gl::ScreenHeight - gl::Height) / 2));

    Interface interface(window);

    while (window->isOpen())
    {
        switch(interface.getCurrentMode())
        {
            case MODE::MainMenuMode:
                interface.showMenu();   
                break;
            case MODE::ChooseLevelMode:
                interface.chooseLevel();
                break;
            case MODE::ChooseAction:
                interface.chooseFurtherAction();
                break;
            case MODE::PlayLevelMode:
                interface.displayLevel();
                break;
            case MODE::ExitMode:
                interface.exitGame();
                break;
        }
    }

    return 0;
}
