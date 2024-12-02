#include "settings.h"

namespace gl
{
    // global parameters
    const int ScreenWidth = VideoMode::getDesktopMode().width;
    const int ScreenHeight = VideoMode::getDesktopMode().height;
    const int Width = 5 * ScreenWidth / 8; 
    const int Height = 0.74075 * ScreenHeight; 
    const int size = gl::Width / 24;

    // colors
    const Color WHITE(255, 255, 255);
    const Color GREEN(0, 128, 0);
    const Color BLUE(66, 170, 255);
    const Color DARK_BLUE(0, 39, 174);
    const Color GREY(128, 128, 128);
    const Color GOLD(255, 215, 0);

    // fonts
    Font font;
    void initFont() noexcept
    {
        font.loadFromFile("app_data/fonts/arial_bold.ttf");
    }
}

namespace DR
{
    // Drawing settings
    const int warningWindowWidth = gl::size * 10;
    const int warningWindowHeight = gl::Height / 4;
    const int warningWindowXPos = (gl::Width - warningWindowWidth) / 2;
    const int warningWindowYPos = (gl::Height - warningWindowHeight) / 2;

    const int warningButtonWidth = warningWindowWidth / 4;
    const int warningButtonHeight = warningWindowHeight / 4;
    const int yesButtonXPos = warningWindowXPos + warningButtonWidth / 1.1; 
    const int yesButtonYPos = gl::size * 8.5;
    const int noButtonXPos = warningWindowXPos + warningWindowWidth - 
        warningButtonWidth - (yesButtonXPos - warningWindowXPos);
    const int noButtonYPos = yesButtonYPos;

    const int warningTextSize = 0.0216 * gl::Width; // 26
    const int levelTextSize = 0.025 * gl::Width;
    const int coinsTextSize = 0.039 * gl::Width;

    const int backButtonXPos = gl::size * 19.7;
    const int restartButtonXPos = backButtonXPos + gl::size * 1.3;
    const int levelsButtonXPos = restartButtonXPos + gl::size * 1.3;
    const int saveButtonXPos = gl::size;
    const int showCommitTreeButtonXPos = saveButtonXPos + gl::size * 1.3;

    const int levelTextYPos = gl::size / 2;

    const int drawingCoinsTextXPos = gl::size * 16.5;
    const int drawingCoinsTextYPos = gl::size / 2.5;
}

namespace IN
{
    // Interface settings
    const int coinTextureYPos = gl::size * 5.2;
    const int logoWidth = gl::size * 10;
    const int logoHeight = gl::size * 1.56;
    const int logoYPos = gl::size / 2;

    const int mainMenuButtonsWidth = gl::Width / 4.8;
    const int mainMenuButtonsHeight = gl::Height / 8;
    const int mainMenuButtonsXPos = (gl::Width - mainMenuButtonsWidth) / 2;
    const int mainMenuButtonsYPos = (gl::Height - 3 * mainMenuButtonsHeight) / 4;
    const int newGameButtonYPos = mainMenuButtonsYPos + mainMenuButtonsHeight;
    const int continueButtonYPos = 2 * mainMenuButtonsYPos + mainMenuButtonsHeight;
    const int exitButtonYPos = 3 * mainMenuButtonsYPos + mainMenuButtonsHeight;

    const int menuButtonWidth = gl::size * 5;
    const int menuButtonHeight = gl::size * 2;
    const int menuButtonXPos = mainMenuButtonsXPos;
    const int menuButtonYPos = gl::size * 13;

    const int mainMenuButtonsTextSize = 0.025 * gl::Width;
    const int menuButtonTextSize = 0.0375 * gl::Width;

    const int levelsButtonSize = gl::size * 2;
    const int levelsButtonsXOffset = (gl::Width - 4 * levelsButtonSize - 3 * betweenButtonsXPos) / 2;
    const int betweenButtonsXPos = gl::size * 0.4;
    const int levelsButtonsYOffset = gl::size * 2.3;
    const int betweenButtonsYPos = betweenButtonsXPos;
    const int levelsButtonTextSize = 0.0375 * gl::Width;

    const int furtherActionButtonWidth = gl::size * 4;
    const int furtherActionButtonHeight = gl::size * 1.3;
    const int betweenFurtherActionsButtonsOffset = gl::size / 5;
    const int levelButtonXPos = (gl::Width - furtherActionButtonWidth * 3 - 
        betweenFurtherActionsButtonsOffset * 2) / 2;
    const int repeatButtonXPos = levelButtonXPos + furtherActionButtonWidth + 
        betweenFurtherActionsButtonsOffset;
    const int nextButtonXPos = levelButtonXPos + (furtherActionButtonWidth + 
        betweenFurtherActionsButtonsOffset) * 2;
    const int furtherActionButtonsYPos = gl::size * 8.5;
    const int furtherActionButtonsTextSize = 0.025 * gl::Width;

    const int titleTextSize = 0.04 * gl::Width;
    const int titleTextYPos = gl::size * 0.6;
    const int interfaceCoinsTextSize = 0.045 * gl::Width;

    const int levelPassedSubstrateYPos = gl::size * 7;
    const int levelPassedTextSize = 0.03333 * gl::Width;
    const int levelPassedSubstrateWidth = 8 * gl::size;
const int levelPassedSubstrateHeight = 1.3 * gl::size;
}
