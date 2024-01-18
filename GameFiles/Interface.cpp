#include "Interface.hpp"

void Interface::loadTextures()
{
    img_.emplace("background", RectangleShape(Vector2f(Width, Height))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/interface/background"));

    img_.emplace("logo", RectangleShape(Vector2f(logoWidth, logoHeight))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/interface/logo"));
    img_["logo"].setPosition((Width - img_["logo"].getGlobalBounds().width) / 2, logoYPos);

    img_.emplace("levels_back", RectangleShape(Vector2f(Width, Height))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/interface/levels_back"));  

    img_.emplace("coin", RectangleShape(Vector2f(size, size))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/player/coin")); 
}

void Interface::createMainMenuButtons()
{
    newGameButton_ = Button(window_, Text(Localizer::translate(L"NEW GAME"), font, 
        mainMenuButtonsTextSize), mainMenuButtonsXPos, newGameButtonYPos, 
        mainMenuButtonsWidth, mainMenuButtonsHeight, GREEN, BLUE);

    continueButton_ = Button(window_, Text(Localizer::translate(L"CONTINUE"), font, 
        mainMenuButtonsTextSize), mainMenuButtonsXPos, continueButtonYPos, 
        mainMenuButtonsWidth, mainMenuButtonsHeight, GREEN, BLUE);

    exitButton_ = Button(window_, Text(Localizer::translate(L"EXIT"), font, 
        mainMenuButtonsTextSize), mainMenuButtonsXPos, exitButtonYPos, 
        mainMenuButtonsWidth, mainMenuButtonsHeight, GREEN, BLUE);

    menuButton_ = Button(window_, Text(Localizer::translate(L"MENU"), font, 
        menuButtonTextSize), menuButtonXPos, menuButtonYPos, 
        menuButtonWidth, menuButtonHeight, GREEN, BLUE);
}

void Interface::createLevelButtons()
{
    size_t rows = 4;
    size_t columns = 4;

    for(size_t i = 0; i < rows; i++)
    {   
        for(size_t j = 0; j < columns; j++)
        {
            levelsButtons_.emplace_back(Button(window_, 
                Text(std::to_string(i * rows + j + 1), font, levelsButtonTextSize), 
                levelsButtonsXOffset + j * (levelsButtonSize + betweenButtonsXPos), 
                levelsButtonsYOffset + i * (levelsButtonSize + betweenButtonsYPos), 
                levelsButtonSize, levelsButtonSize, GREY, BLUE));
        }
    }
}

void Interface::createFurtherActionButtons()
{
    levelsButton_ = Button(window_, Text(Localizer::translate(L"levels"), font, 
        furtherActionButtonsTextSize), levelButtonXPos, furtherActionButtonsYPos, 
        furtherActionButtonWidth, furtherActionButtonHeight, GREEN, BLUE);
    repeatButton_ = Button(window_, Text(Localizer::translate(L"again"), font, 
        furtherActionButtonsTextSize), repeatButtonXPos, furtherActionButtonsYPos, 
        furtherActionButtonWidth, furtherActionButtonHeight, GREEN, BLUE);
    nextButton_ = Button(window_, Text(Localizer::translate(L"next"), font, 
        furtherActionButtonsTextSize), nextButtonXPos, furtherActionButtonsYPos, 
        furtherActionButtonWidth, furtherActionButtonHeight, GREEN, BLUE);
}

void Interface::initTexts()
{
    titleText_ = Text(Localizer::translate(L"Levels"), font, titleTextSize);
    titleText_.setFillColor(DARK_BLUE);
    titleText_.setPosition((Width - titleText_.getGlobalBounds().width) / 2, 
        titleTextYPos);

    coinsText_ = Text("", font, interfaceCoinsTextSize);
    coinsText_.setFillColor(GOLD);
}

void Interface::initLevelPassedText()
{
    levelPassedSubstrate_.setPosition((Width - 
        levelPassedSubstrate_.getGlobalBounds().width) / 2, levelPassedSubstrateYPos);
    levelPassedSubstrate_.setFillColor(BLUE);

    int levelPassedSubstrateLeft_ = levelPassedSubstrate_.getGlobalBounds().left;
    int levelPassedSubstrateTop_ = levelPassedSubstrate_.getGlobalBounds().top;
    int levelPassedSubstrateWidth_ = levelPassedSubstrate_.getGlobalBounds().width;
    int levelPassedSubstrateHeight_ = levelPassedSubstrate_.getGlobalBounds().height;

    levelPassedText_.setString(Localizer::translate(L"Level is passed!"));
    levelPassedText_.setPosition(levelPassedSubstrateLeft_ + 
        (levelPassedSubstrateWidth_ - levelPassedText_.getGlobalBounds().width) / 2,
        levelPassedSubstrateTop_ + (levelPassedSubstrateHeight_ - 
        levelPassedText_.getGlobalBounds().height) / 3);
}

void Interface::updateLevelButtonsColor()
{
    for(size_t i = 0; i < levelsButtons_.size(); i++)
    {
        if (i <= currentLevel_) 
            levelsButtons_[i].setButtonColor(GREEN);
    }
}

void Interface::updateCoinsText()
{
    switch(passedLevel_)
    {
        case 1: case 2:
            coins_ += 20;
            coinsText_.setString("+20");
            break;
        case 3: case 4: case 6:
        case 7: case 8: case 9:
        case 10: case 11:
            coins_ += 30;
            coinsText_.setString("+30");
            break;
        case 5: case 12: case 13:
        case 14: case 15:
            coins_ += 40;
            coinsText_.setString("+40");
            break;
        case 16:
            coins_ += 50;
            coinsText_.setString("+50");
            break;
    }

    int coinsTextWidth = coinsText_.getGlobalBounds().width;
    int coinsTextureWidth = img_["coin"].getGlobalBounds().width;

    coinsText_.setPosition((Width - 
        (coinsTextWidth + coinsTextureWidth + size / 3)) / 2, coinTextureYPos);

    int coinsTextXPos = coinsText_.getGlobalBounds().left;

    img_["coin"].setPosition(coinsTextXPos + coinsTextWidth + size / 3, 
        coinTextureYPos + size / 4);
}

Interface::Interface(RenderWindow* window)
    : window_(window), currentMode_(MODE::MainMenuMode), 
    currentLevel_(0), passedLevel_(0), coins_(0), 
    drawing_(window),
    levelPassedText_("", font, levelPassedTextSize),
    levelPassedSubstrate_(Vector2f(levelPassedSubstrateWidth, 
        levelPassedSubstrateHeight))    
{
    loadTextures();
    createMainMenuButtons();
    createLevelButtons();
    createFurtherActionButtons();
    initTexts();
    initLevelPassedText();

    std::tie(coins_, currentLevel_) = file_.readDataFromFile();
}

Interface::~Interface()
{
    window_ = nullptr;
    file_.writeDataToFile(coins_, currentLevel_);
}

void Interface::showMenu()
{
    DropDownList dropDownList(window_);

    while (window_->isOpen())
    {
        pollEvents(window_);
    
        window_->draw(img_["background"]);
        window_->draw(img_["logo"]);

        newGameButton_.drawButton();
        continueButton_.drawButton();
        exitButton_.drawButton();

        dropDownList.drawList();

        if (newGameButton_.isPressed())
        {
            if (currentLevel_)
            {
                if (showWarning(window_, 
                    Localizer::translate(L"Your results will be lost!")))
                {
                    currentLevel_ = 0;
                    currentMode_ = MODE::ChooseLevelMode;
                    break;
                }
            }
            else 
            {
                currentMode_ = MODE::ChooseLevelMode;
                break;
            }
        }
        else if (continueButton_.isPressed())
        {
            currentMode_ = MODE::ChooseLevelMode;
            break;
        }
        else if (exitButton_.isPressed())
        {
            currentMode_ = MODE::ExitMode;
            break;
        }
        
        std::string locale = dropDownList.isPressed();
        if (locale.size())
        {
            
        }

        window_->display();
    }
}

void Interface::chooseLevel()
{
    updateLevelButtonsColor();
    
    while(window_->isOpen())
    {
        pollEvents(window_);
        
        window_->draw(img_["levels_back"]);
        window_->draw(titleText_);
        menuButton_.drawButton();

        for(size_t i = 0; i < levelsButtons_.size(); i++) 
        { 
            levelsButtons_[i].drawButton();
            if (i <= currentLevel_)
            {
                if (levelsButtons_[i].isPressed())
                {
                    drawing_.setCoins(getCoins());
                    if (drawing_.drawWorld(i + 1)) 
                    {
                        currentMode_ = MODE::ChooseAction;
                        passedLevel_ = i + 1;
                    }
                    coins_ = drawing_.getCoins();
                }
            }
        }

        if (menuButton_.isPressed())
            currentMode_ = MODE::MainMenuMode;

        if (currentMode_ != ChooseLevelMode) break;

        window_->display();
    }
}

void Interface::chooseFurtherAction()
{
    sleep(milliseconds(250));

    SoundManager::getManager()->playSound("level_complete");
    
    updateCoinsText();

    if (passedLevel_ > currentLevel_) currentLevel_ = passedLevel_;

    Sprite background(*TextureManager::getManager()->loadTextureFromFile(
        "textures/levels/" + std::to_string(passedLevel_) + "-2.png"), 
        { 0, 0, Width, Height });

    if (passedLevel_ == levelsMap.size()) 
        nextButton_.setButtonColor(GREY);

    while(window_->isOpen())
    {
        pollEvents(window_);

        window_->draw(background);

        window_->draw(levelPassedSubstrate_);
        window_->draw(levelPassedText_);
        window_->draw(img_["coin"]);
        window_->draw(coinsText_);

        levelsButton_.drawButton();
        repeatButton_.drawButton();
        nextButton_.drawButton();

        if (levelsButton_.isPressed()) 
        {
            currentMode_ = MODE::ChooseLevelMode;
            break;
        }

        else if (repeatButton_.isPressed())
        {
            drawing_.setCoins(getCoins());

            if (!drawing_.drawWorld(passedLevel_)) 
                currentMode_ = MODE::ChooseLevelMode;

            coins_ = drawing_.getCoins();
            break;
        }

        else if (passedLevel_ != levelsMap.size() 
            && nextButton_.isPressed())
        {
            drawing_.setCoins(getCoins());

            if (drawing_.drawWorld(passedLevel_ + 1)) 
                passedLevel_++;
            else currentMode_ = MODE::ChooseLevelMode;

            coins_ = drawing_.getCoins();
            break;
        }

        window_->display();
    }
}

void Interface::exitGame()
{
    if (!showWarning(window_, 
        Localizer::translate(L"Are you sure you want to exit?"))) 
            currentMode_ = MainMenuMode;
    else window_->close();
}

void Interface::setCoins(int coins_num) { coins_ = coins_num; }

const int Interface::getCoins() const { return coins_; }

const size_t Interface::getCurrentMode() const { return currentMode_; }

void Interface::setCurrentLevel(size_t curr_level) { currentLevel_ = curr_level; }
