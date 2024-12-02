#pragma once

#include <string_view>
#include <SFML/Graphics.hpp>

using namespace sf;

// GLOBAL SETTINGS
namespace gl
{
    // global parameters
    extern const int ScreenWidth; // screen dimensions
    extern const int ScreenHeight;
    extern const int Width; // game window width
    extern const int Height; // game window height
    extern const int size; // size of cells

    // colors
    extern const Color WHITE;
    extern const Color GREEN;
    extern const Color BLUE;
    extern const Color DARK_BLUE;
    extern const Color GREY;
    extern const Color GOLD;

    // fonts
    extern Font font;
    void initFont() noexcept;
}

// DRAWING SETTINGS
namespace DR
{
    // warning window parameters
    extern const int warningWindowWidth;
    extern const int warningWindowHeight;
    extern const int warningWindowXPos;
    extern const int warningWindowYPos;

    // "yes" and "no" buttons parameters
    extern const int warningButtonWidth;
    extern const int warningButtonHeight;
    extern const int yesButtonXPos;
    extern const int yesButtonYPos;
    extern const int noButtonXPos;
    extern const int noButtonYPos;

    // warning text size
    extern const int warningTextSize;
    extern const int levelTextSize;
    extern const int coinsTextSize;

    // main menu buttons x-positions
    extern const int backButtonXPos;
    extern const int restartButtonXPos;
    extern const int levelsButtonXPos;

    // version control system buttons x-positions
    extern const int saveButtonXPos;
    extern const int showCommitTreeButtonXPos;

    // level text positions
    extern const int levelTextYPos;

    // coins text positions
    extern const int drawingCoinsTextXPos;
    extern const int drawingCoinsTextYPos;
}

// INTERFACE SETTINGS
namespace IN
{
    // INTERFACE SETTINGS

    // logo & coins textures settings
    extern const int coinTextureYPos;
    extern const int logoWidth;
    extern const int logoHeight;
    extern const int logoYPos;

    // main menu buttons settings
    extern const int mainMenuButtonsWidth;
    extern const int mainMenuButtonsHeight;
    extern const int mainMenuButtonsXPos;
    extern const int mainMenuButtonsYPos;
    extern const int newGameButtonYPos;
    extern const int continueButtonYPos;
    extern const int exitButtonYPos;

    // menu button settings
    extern const int menuButtonWidth;
    extern const int menuButtonHeight;
    extern const int menuButtonXPos;
    extern const int menuButtonYPos;

    // main menu buttons text size & menu button text size
    extern const int mainMenuButtonsTextSize;
    extern const int menuButtonTextSize;

    // levels buttons settings
    extern const int levelsButtonSize;
    extern const int levelsButtonsXOffset;
    extern const int betweenButtonsXPos;
    extern const int levelsButtonsYOffset;
    extern const int betweenButtonsYPos;
    extern const int levelsButtonTextSize;

    // further action buttons settings
    extern const int furtherActionButtonWidth;
    extern const int furtherActionButtonHeight;
    extern const int betweenFurtherActionsButtonsOffset;
    extern const int levelButtonXPos;
    extern const int repeatButtonXPos;
    extern const int nextButtonXPos;
    extern const int furtherActionButtonsYPos;
    extern const int furtherActionButtonsTextSize;

    // title & coins texts settings
    extern const int titleTextSize;
    extern const int titleTextYPos;
    extern const int interfaceCoinsTextSize;

    // "level passed" text and substrate settings
    extern const int levelPassedSubstrateYPos;
    extern const int levelPassedTextSize;
    extern const int levelPassedSubstrateWidth;
    extern const int levelPassedSubstrateHeight;
}

// STRINGS TO TRANSLATE
namespace STRING
{
    constexpr std::wstring_view Continue = L"Continue?";
    constexpr std::wstring_view Yes = L"Yes";
    constexpr std::wstring_view No = L"No";
    constexpr std::wstring_view SureToExit = L"Are you shure you want to exit?";
    constexpr std::wstring_view Level = L"Level ";
    constexpr std::wstring_view LostResults = L"Your results will be lost!";
    constexpr std::wstring_view NewGame = L"NEW GAME";
    constexpr std::wstring_view ContinueGame = L"CONTINUE";
    constexpr std::wstring_view ExitGame = L"EXIT";
    constexpr std::wstring_view Menu = L"MENU";
    constexpr std::wstring_view Levels = L"levels";
    constexpr std::wstring_view Again = L"again";
    constexpr std::wstring_view Next = L"next";
    constexpr std::wstring_view LevelsLabel = L"Levels";
    constexpr std::wstring_view LevelPassed = L"Level is passed!";
}