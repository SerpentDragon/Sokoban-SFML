#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "Button.hpp"
#include "Drawing.hpp"
#include "settings.h"

using namespace sf;

enum Mode { MainMenuMode, ChooseLevelMode, ExitMode, ChooseAction };

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

    int readFile();

    void writeFile();

    void setCoins(int);

    const int getCoins() const;

    const size_t getCurrentMode() const;

    void setCurrentLevel(size_t);

private:

    RenderWindow* window_;
    
    std::map<std::string, std::pair<Texture, RectangleShape>> img_;

    Drawing drawing;

    size_t currentMode_;
    size_t currentLevel_;
    size_t passedLevel_;
    int coins_;
};
