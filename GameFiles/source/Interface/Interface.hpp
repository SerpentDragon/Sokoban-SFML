#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include "Drawing.hpp"
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"
#include "../Widgets/Button.hpp"
#include "../Managers/Localizer.hpp"
#include "../Widgets/DropDownList.hpp"
#include "../Managers/FileIOManager.hpp"
#include "../Managers/TextureManager.hpp"

using namespace sf;

enum MODE : unsigned int { MainMenuMode = 0, ChooseLevelMode, ExitMode, PlayLevelMode, ChooseAction };

class Interface
{
public:

    Interface(std::shared_ptr<RenderWindow>) noexcept;

    Interface(const Interface&) = delete;

    Interface(Interface&&) noexcept = delete;

    Interface& operator=(const Interface&) = delete;

    Interface& operator=(Interface&&) noexcept = delete;

    ~Interface() noexcept;

    void showMenu() noexcept;

    void chooseLevel() noexcept;

    void displayLevel() noexcept;

    void chooseFurtherAction() noexcept;

    void exitGame() noexcept;

    const size_t getCurrentMode() const noexcept;

    void setCurrentLevel(size_t) noexcept;

private:

    void loadTextures() noexcept;

    void createMainMenuButtons() noexcept;

    void createLevelButtons() noexcept;

    void createFurtherActionButtons() noexcept;

    void initTexts() noexcept;

    void initLevelPassedText() noexcept;

    void updateLevelButtonsColor() noexcept;

    void updateCoinsText() noexcept;

    void recreateTexts() noexcept;

    void setCoins(int) noexcept;

    const int getCoins() const noexcept;

private:

    // window to render objects
    std::shared_ptr<RenderWindow> window_;
    
    //set of used textures
    std::unordered_map<std::string_view, RectangleShape> img_;

    // info about current state of the interface
    unsigned int currentMode_;
    unsigned int currentLevel_;
    unsigned int passedLevel_;
    int coins_;

    // main menu buttons
    Button newGameButton_;
    Button continueButton_;
    Button exitButton_;
    Button menuButton_;

    // further actions buttons
    Button levelsButton_;
    Button repeatButton_;
    Button nextButton_;

    // level buttons
    std::vector<Button> levelsButtons_;

    // dropdown list for localization
    DropDownList dropDownList_;

    // text to display
    Text titleText_;
    Text coinsText_;

    // elements to display level passed text
    Text levelPassedText_;
    RectangleShape levelPassedSubstrate_;

    // object to draw levels
    Drawing drawing_;

    // object to keep progress of the player
    FileIOManager file_;
};
