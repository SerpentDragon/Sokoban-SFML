#include "settings.h"

// global parameters
const int ScreenWidth = VideoMode::getDesktopMode().width;
const int ScreenHeight = VideoMode::getDesktopMode().height;
const int Width = 5 * ScreenWidth / 8; 
const int Height = 0.74075 * ScreenHeight; 
const int size = Width / 24;

// colors
const Color WHITE(255, 255, 255);
const Color GREEN(0, 128, 0);
const Color BLUE(66, 170, 255);
const Color DARK_BLUE(0, 39, 174);
const Color GREY(128, 128, 128);
const Color GOLD(255, 215, 0);

// fonts
Font font;
void initFont()
{
    font.loadFromFile("fonts/arial_bold.ttf");
}

// Drawing settings
const int warningWindowWidth = size * 10;
const int warningWindowHeight = Height / 4;
const int warningWindowXPos = (Width - warningWindowWidth) / 2;
const int warningWindowYPos = (Height - warningWindowHeight) / 2;

const int warningButtonWidth = warningWindowWidth / 4;
const int warningButtonHeight = warningWindowHeight / 4;
const int yesButtonXPos = warningWindowXPos + warningButtonWidth / 1.1; 
const int yesButtonYPos = size * 8.5;
const int noButtonXPos = warningWindowXPos + warningWindowWidth - 
    warningButtonWidth - (yesButtonXPos - warningWindowXPos);
const int noButtonYPos = yesButtonYPos;

const int warningTextSize = 0.0216 * Width; // 26
const int levelTextSize = 0.025 * Width;
const int coinsTextSize = 0.039 * Width;

const int backButtonXPos = size * 19.7;
const int restartButtonXPos = size * 21;
const int levelsButtonXPos = size * 22.3;

const int levelTextXPos = size;
const int levelTextYPos = size / 2;

const int drawingCoinsTextXPos = size * 16.5;
const int drawingCoinsTextYPos = size / 2.5;

// Interface settings
const int coinTextureYPos = size * 5.2;
const int logoWidth = size * 10;
const int logoHeight = size * 1.56;
const int logoYPos = size / 2;

const int mainMenuButtonsWidth = Width / 4.8;
const int mainMenuButtonsHeight = Height / 8;
const int mainMenuButtonsXPos = (Width - mainMenuButtonsWidth) / 2;
const int mainMenuButtonsYPos = (Height - 3 * mainMenuButtonsHeight) / 4;
const int newGameButtonYPos = mainMenuButtonsYPos + mainMenuButtonsHeight;
const int continueButtonYPos = 2 * mainMenuButtonsYPos + mainMenuButtonsHeight;
const int exitButtonYPos = 3 * mainMenuButtonsYPos + mainMenuButtonsHeight;

const int menuButtonWidth = size * 5;
const int menuButtonHeight = size * 2;
const int menuButtonXPos = mainMenuButtonsXPos;
const int menuButtonYPos = size * 13;

const int mainMenuButtonsTextSize = 0.025 * Width;
const int menuButtonTextSize = 0.0375 * Width;

const int levelsButtonSize = size * 2;
const int levelsButtonsXOffset = (Width - 4 * levelsButtonSize - 3 * betweenButtonsXPos) / 2;
const int betweenButtonsXPos = size * 0.4;
const int levelsButtonsYOffset = size * 2.3;
const int betweenButtonsYPos = betweenButtonsXPos;
const int levelsButtonTextSize = 0.0375 * Width;

const int furtherActionButtonWidth = size * 4;
const int furtherActionButtonHeight = size * 1.3;
const int betweenFurtherActionsButtonsOffset = size / 5;
const int levelButtonXPos = (Width - furtherActionButtonWidth * 3 - 
    betweenFurtherActionsButtonsOffset * 2) / 2;
const int repeatButtonXPos = levelButtonXPos + furtherActionButtonWidth + 
    betweenFurtherActionsButtonsOffset;
const int nextButtonXPos = levelButtonXPos + (furtherActionButtonWidth + 
    betweenFurtherActionsButtonsOffset) * 2;
const int furtherActionButtonsYPos = size * 8.5;
const int furtherActionButtonsTextSize = 0.025 * Width;

const int titleTextSize = 0.04 * Width;
const int titleTextYPos = size * 0.6;
const int interfaceCoinsTextSize = 0.045 * Width;

const int levelPassedSubstrateYPos = size * 7;
const int levelPassedTextSize = 0.03333 * Width;
const int levelPassedSubstrateWidth = 8 * size;
const int levelPassedSubstrateHeight = 1.3 * size;