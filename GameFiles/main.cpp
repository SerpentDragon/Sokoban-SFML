#include <SFML/Graphics.hpp>
#include "Interface/Interface.hpp"
#include "Player/settings.h"

using namespace sf;

int main()
{
    initFont();
    
    RenderWindow window(VideoMode(Width, Height), "Sokoban", Style::Close);
    window.setPosition(Vector2i((ScreenWidth - Width) / 2, (ScreenHeight - Height) / 2));

    Interface interface(&window);

    while (window.isOpen())
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
            case MODE::ExitMode:
                interface.exitGame();
                break;
        }
    }

    return 0;
}
