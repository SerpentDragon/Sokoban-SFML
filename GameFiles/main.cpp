#include <SFML/Graphics.hpp>
#include "source/Interface/Interface.hpp"

using namespace sf;

int main()
{
    std::cout << VCSWIN::VCSWindowXPos + VCSWIN::GT::zeroLevelXPos << ' ' << VCSWIN::GT::zeroLevelYPos << '\n';

    srand(time(nullptr));
    
    gl::initFont();

    Interface interface;

    while(interface.isRunning())
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
