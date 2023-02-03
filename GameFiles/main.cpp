#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "settings.h"

using namespace sf;

int ScreenWidth = VideoMode::getDesktopMode().width;
int ScreenHeight = VideoMode::getDesktopMode().height;
int Width = 0.625 * ScreenWidth; 
int Height = 0.74075 * ScreenHeight; 
int size = Width / 24;

Color WHITE(255, 255, 255);
Color GREEN(0, 128, 0);
Color BLUE(66, 170, 255);
Color DARK_BLUE(0, 39, 174);
Color GREY(128, 128, 128);
Color GOLD(255, 215, 0);

Font font;

void initFont()
{
    font.loadFromFile("fonts/arial_bold.ttf");
}

int main()
{
    initFont();
    
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
