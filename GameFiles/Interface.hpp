#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "TextureManager.hpp"
#include "FileIOManager.hpp"
#include "Button.hpp"
#include "Drawing.hpp"
#include "settings.h"

using namespace sf;

enum MODE : unsigned int { MainMenuMode = 0, ChooseLevelMode, ExitMode, ChooseAction };

class Interface
{
public:

    Interface(RenderWindow*);

    Interface(const Interface&) = delete;

    Interface(Interface&&) noexcept = delete;

    Interface& operator=(const Interface&) = delete;

    Interface& operator=(Interface&&) noexcept = delete;

    ~Interface();

    void showMenu();

    void chooseLevel();

    void chooseFurtherAction();

    void exitGame();

    const size_t getCurrentMode() const;

    void setCurrentLevel(size_t);

private:

    void loadTextures();

    void createMainMenuButtons();

    void createLevelButtons();

    void updateLevelButtonsColor();

    void setCoins(int);

    const int getCoins() const;

private:

    // window to render objects
    RenderWindow* window_;
    
    //set of used textures
    std::unordered_map<std::string, RectangleShape> img_;

    // info about current state of the interface
    size_t currentMode_;
    size_t currentLevel_;
    size_t passedLevel_;
    int coins_;

    // main menu buttons
    Button newGameButton_;
    Button continueButton_;
    Button exitButton_;
    Button menuButton_;

    // level buttons
    std::vector<Button> levelButtons_;

    // main manu window title
    Text titleText_;

    // object to draw levels
    Drawing drawing_;

    // object to keep progress of the player
    FileIOManager file_;
};
