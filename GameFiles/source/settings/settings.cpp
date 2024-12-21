#include "settings.h"

namespace gl
{
    // global parameters
    const int ScreenWidth = VideoMode::getDesktopMode().width;
    const int ScreenHeight = VideoMode::getDesktopMode().height;

    const int WindowWidth = 5 * ScreenWidth / 6;
    const int WindowHeight = 0.74075 * ScreenHeight;
    
    const int GameScreenWidth = 5 * ScreenWidth / 8; 
    const int GameScreenHeight = WindowHeight; 
    const int size = gl::GameScreenWidth / 24;

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
    // warning window parameters
    const int warningWindowWidth = gl::size * 10;
    const int warningWindowHeight = gl::GameScreenHeight / 4;
    const int warningWindowXPos = (gl::GameScreenWidth - warningWindowWidth) / 2;
    const int warningWindowYPos = (gl::GameScreenHeight - warningWindowHeight) / 2;

    // "yes" and "no" buttons parameters
    const int warningButtonWidth = warningWindowWidth / 4;
    const int warningButtonHeight = warningWindowHeight / 4;
    const int yesButtonXPos = warningWindowXPos + warningButtonWidth / 1.1; 
    const int yesButtonYPos = warningWindowYPos + warningWindowHeight - 
        1.5 * warningButtonHeight;
    const int noButtonXPos = warningWindowXPos + warningWindowWidth - 
        warningButtonWidth - (yesButtonXPos - warningWindowXPos);
    const int noButtonYPos = yesButtonYPos;

    // warning text size
    const int warningTextSize = 0.0216 * gl::GameScreenWidth; // 26
    const int levelTextSize = 0.025 * gl::GameScreenWidth;
    const int coinsTextSize = 0.039 * gl::GameScreenWidth;

    // main menu buttons x-positions
    const int backButtonXPos = gl::size * 19.7;
    const int restartButtonXPos = backButtonXPos + gl::size * 1.3;
    const int levelsButtonXPos = restartButtonXPos + gl::size * 1.3;

    // version control system buttons x-positions
    const int saveButtonXPos = gl::size;
    const int showCommitTreeButtonXPos = saveButtonXPos + gl::size * 1.3;

    // level text positions
    const int levelTextYPos = gl::size / 2;

    // coins text positions
    const int drawingCoinsTextXPos = gl::size * 16.5;
    const int drawingCoinsTextYPos = gl::size / 2.5;
}

namespace IN
{
    // logo & coins textures settings
    const int coinTextureYPos = gl::size * 5.2;
    const int logoWidth = gl::size * 10;
    const int logoHeight = gl::size * 1.56;
    const int logoYPos = gl::size / 2;

    // main menu buttons settings
    const int mainMenuButtonsWidth = gl::GameScreenWidth / 4.8;
    const int mainMenuButtonsHeight = gl::GameScreenHeight / 8;
    const int mainMenuButtonsXPos = (gl::GameScreenWidth - mainMenuButtonsWidth) / 2;
    const int mainMenuButtonsYPos = (gl::GameScreenHeight - 3 * mainMenuButtonsHeight) / 4;
    const int newGameButtonYPos = mainMenuButtonsYPos + mainMenuButtonsHeight;
    const int continueButtonYPos = 2 * mainMenuButtonsYPos + mainMenuButtonsHeight;
    const int exitButtonYPos = 3 * mainMenuButtonsYPos + mainMenuButtonsHeight;

    // main menu buttons text size & menu button text size
    const int mainMenuButtonsTextSize = 0.025 * gl::GameScreenWidth;
    const int menuButtonTextSize = 0.0375 * gl::GameScreenWidth;

    // levels buttons settings
    const int levelsButtonsSize = gl::GameScreenHeight / 8;
    const int betweenButtonsXPos = levelsButtonsSize * 0.2;
    const int betweenButtonsYPos = betweenButtonsXPos;
    const int levelsButtonsXOffset = (gl::GameScreenWidth - columns * levelsButtonsSize 
        - (columns - 1) * betweenButtonsXPos) / 2;
    const int levelsButtonsYOffset = levelsButtonsSize * 1.2;
    const int levelsButtonsTextSize = 0.0375 * gl::GameScreenWidth;

    // menu button settings
    const int menuButtonWidth = gl::size * 5;
    const int menuButtonHeight = levelsButtonsSize;
    const int menuButtonXPos = mainMenuButtonsXPos;
    const int menuButtonYPos = levelsButtonsYOffset + rows * levelsButtonsSize + 
        (rows - 1) * betweenButtonsXPos + 2 * betweenButtonsXPos;

    // further action buttons settings
    const int furtherActionButtonWidth = gl::size * 4;
    const int furtherActionButtonHeight = gl::size * 1.3;
    const int betweenFurtherActionsButtonsOffset = gl::size / 5;
    const int levelButtonXPos = (gl::GameScreenWidth - furtherActionButtonWidth * 3 - 
        betweenFurtherActionsButtonsOffset * 2) / 2;
    const int repeatButtonXPos = levelButtonXPos + furtherActionButtonWidth + 
        betweenFurtherActionsButtonsOffset;
    const int nextButtonXPos = levelButtonXPos + (furtherActionButtonWidth + 
        betweenFurtherActionsButtonsOffset) * 2;
    const int furtherActionButtonsYPos = gl::size * 8.5;
    const int furtherActionButtonsTextSize = 0.025 * gl::GameScreenWidth;

    // title & coins texts settings
    const int titleTextSize = 0.04 * gl::GameScreenWidth;
    const int titleTextYPos = gl::size * 0.6;
    const int interfaceCoinsTextSize = 0.045 * gl::GameScreenWidth;

    // "level passed" text and substrate settings
    const int levelPassedSubstrateYPos = gl::size * 7;
    const int levelPassedTextSize = 0.03333 * gl::GameScreenWidth;
    const int levelPassedSubstrateWidth = 8 * gl::size;
    const int levelPassedSubstrateHeight = 1.3 * gl::size;

    // drop down list settings
    const int dropDownListWidth = gl::size;
    const int dropDownListHeight = gl::size;
    const int dropDownListXPos = gl::GameScreenWidth - 1.5 * dropDownListWidth;
    const int dropDownListYPos = gl::size / 2;
}

namespace VCSWIN
{
    // VCS Window params
    const int VCSWindowWidth = gl::GameScreenWidth / 3;
    const int VCSWindowHeight = gl::GameScreenHeight;
    const int VCSWindowXPos = gl::GameScreenWidth;
    const int VCSWindowYPos = 0;

    // Close VCS Window button params
    const int closeButtonSize= gl::size / 2;
    const int closeButtonXPos = gl::GameScreenWidth - closeButtonSize;
    const int closeButtonYPos = 0;
    
    // Graphics tree params
    namespace GT
    {
        const int commitSize = gl::size / 6;
        const int commitInterval = commitSize * 4;

        const int branchInterval = commitInterval;

        int zeroLevelYPos = VCSWindowHeight - gl::size;
        int zeroLevelXPos = VCSWindowWidth / 2 - commitSize;

        const int zeroLevelYPosINIT = zeroLevelYPos;
        const int zeroLevelXPosINIT = zeroLevelXPos;
    }
}
