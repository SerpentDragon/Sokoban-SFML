#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "settings.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(Width, Height), "Sokoban", Style::Close);
    window.setPosition(Vector2i((ScreenWidth - Width) / 2, (ScreenHeight - Height) / 2));

    Interface interface(&window);

    int currentLevel = interface.readFile();
    
    interface.setCurrentLevel(currentLevel);

    while (window.isOpen())
    {
        switch(interface.getCurrentMode())
        {
            case MainMenuMode:
                interface.showMenu();
                break;
            case ChooseLevelMode:
                interface.chooseLevel();
                break;
            case ChooseAction:
                interface.chooseFurtherAction();
                break;
            case ExitMode:
                interface.exitGame();
                break;
        }
    }

    interface.writeFile();

    return 0;
}
