#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "Button.h"
#include "Drawing.h"
#include "settings.h"

enum Mode{MainMenuMode, ChooseLevelMode, ExitMode, ChooseAction};

class Interface
{
    RenderWindow* window;
    
    std::map<std::string, std::pair<Texture, RectangleShape>> img;

    size_t currentMode;
    size_t currentLevel;
    size_t passedLevel;
    int coins;

    template<typename T>
    void Swap(T&& obj) noexcept;

public:
    Interface(RenderWindow* window);

    Interface(const Interface& obj);

    Interface(Interface&& obj) noexcept;

    Interface& operator=(const Interface& obj);

    Interface& operator=(Interface&& obj) noexcept;

    ~Interface();

    void showMenu();

    void chooseLevel();

    void chooseFurtherAction();

    void exitGame();

    int readFile();

    void writeFile();

    void setCoins(const int& coins_num);

    const int getCoins() const;

    const size_t getCurrentMode() const;

    void setCurrentLevel(const size_t& curr_level);
};
