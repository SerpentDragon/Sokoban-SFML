#include "Interface.hpp"

void Interface::loadTextures()
{
    img_.emplace("background", RectangleShape(Vector2f(gl::Width, gl::Height))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/background"));

    img_.emplace("logo", RectangleShape(Vector2f(IN::logoWidth, IN::logoHeight))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/logo"));
    img_["logo"].setPosition((gl::Width - img_["logo"].getGlobalBounds().width) / 2, IN::logoYPos);

    img_.emplace("levels_back", RectangleShape(Vector2f(gl::Width, gl::Height))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/levels_back"));  

    img_.emplace("coin", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/coin")); 
}

void Interface::createMainMenuButtons()
{
    newGameButton_ = Button(window_, Text(Localizer::translate(STRING::NewGame), gl::font, 
        IN::mainMenuButtonsTextSize), IN::mainMenuButtonsXPos, IN::newGameButtonYPos, 
        IN::mainMenuButtonsWidth, IN::mainMenuButtonsHeight, gl::GREEN, gl::BLUE);

    continueButton_ = Button(window_, Text(Localizer::translate(STRING::ContinueGame), gl::font, 
        IN::mainMenuButtonsTextSize), IN::mainMenuButtonsXPos, IN::continueButtonYPos, 
        IN::mainMenuButtonsWidth, IN::mainMenuButtonsHeight, gl::GREEN, gl::BLUE);

    exitButton_ = Button(window_, Text(Localizer::translate(STRING::ExitGame), gl::font, 
        IN::mainMenuButtonsTextSize), IN::mainMenuButtonsXPos, IN::exitButtonYPos, 
        IN::mainMenuButtonsWidth, IN::mainMenuButtonsHeight, gl::GREEN, gl::BLUE);

    menuButton_ = Button(window_, Text(Localizer::translate(STRING::Menu), gl::font, 
        IN::menuButtonTextSize), IN::menuButtonXPos, IN::menuButtonYPos, 
        IN::menuButtonWidth, IN::menuButtonHeight, gl::GREEN, gl::BLUE);
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
                Text(std::to_string(i * rows + j + 1), gl::font, IN::levelsButtonTextSize), 
                IN::levelsButtonsXOffset + j * (IN::levelsButtonSize + IN::betweenButtonsXPos), 
                IN::levelsButtonsYOffset + i * (IN::levelsButtonSize + IN::betweenButtonsYPos), 
                IN::levelsButtonSize, IN::levelsButtonSize, gl::GREY, gl::BLUE));
        }
    }
}

void Interface::createFurtherActionButtons()
{
    levelsButton_ = Button(window_, Text(Localizer::translate(STRING::Levels), gl::font, 
        IN::furtherActionButtonsTextSize), IN::levelButtonXPos, IN::furtherActionButtonsYPos, 
        IN::furtherActionButtonWidth, IN::furtherActionButtonHeight, gl::GREEN, gl::BLUE);
    repeatButton_ = Button(window_, Text(Localizer::translate(STRING::Again), gl::font, 
        IN::furtherActionButtonsTextSize), IN::repeatButtonXPos, IN::furtherActionButtonsYPos, 
        IN::furtherActionButtonWidth, IN::furtherActionButtonHeight, gl::GREEN, gl::BLUE);
    nextButton_ = Button(window_, Text(Localizer::translate(STRING::Next), gl::font, 
        IN::furtherActionButtonsTextSize), IN::nextButtonXPos, IN::furtherActionButtonsYPos, 
        IN::furtherActionButtonWidth, IN::furtherActionButtonHeight, gl::GREEN, gl::BLUE);
}

void Interface::initTexts()
{
    titleText_ = Text(Localizer::translate(STRING::LevelsLabel), gl::font, IN::titleTextSize);
    titleText_.setFillColor(gl::DARK_BLUE);
    titleText_.setPosition((gl::Width - titleText_.getGlobalBounds().width) / 2, 
        IN::titleTextYPos);

    coinsText_ = Text("", gl::font, IN::interfaceCoinsTextSize);
    coinsText_.setFillColor(gl::GOLD);
}

void Interface::initLevelPassedText()
{
    levelPassedSubstrate_.setPosition((gl::Width - 
        levelPassedSubstrate_.getGlobalBounds().width) / 2, IN::levelPassedSubstrateYPos);
    levelPassedSubstrate_.setFillColor(gl::BLUE);

    auto levelPassedBounds = levelPassedSubstrate_.getGlobalBounds();

    levelPassedText_.setString(Localizer::translate(STRING::LevelPassed));
    levelPassedText_.setPosition(levelPassedBounds.left + 
        (levelPassedBounds.width - levelPassedText_.getGlobalBounds().width) / 2,
        levelPassedBounds.top + (levelPassedBounds.height - 
        levelPassedText_.getGlobalBounds().height) / 3);
}

void Interface::updateLevelButtonsColor()
{
    Color color;
    for(size_t i = 0; i < levelsButtons_.size(); i++)
    {
        color = i <= currentLevel_ ? gl::GREEN : gl::GREY;
        levelsButtons_[i].setButtonColor(color);
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

    coinsText_.setPosition((gl::Width - 
        (coinsTextWidth + coinsTextureWidth + gl::size / 3)) / 2, IN::coinTextureYPos);

    int coinsTextXPos = coinsText_.getGlobalBounds().left;

    img_["coin"].setPosition(coinsTextXPos + coinsTextWidth + gl::size / 3, 
        IN::coinTextureYPos + gl::size / 4);
}

void Interface::recreateTexts()
{
    newGameButton_.setText(Localizer::translate(STRING::NewGame));
    continueButton_.setText(Localizer::translate(STRING::ContinueGame));
    exitButton_.setText(Localizer::translate(STRING::ExitGame));
    menuButton_.setText(Localizer::translate(STRING::Menu));
    levelsButton_.setText(Localizer::translate(STRING::Levels));
    repeatButton_.setText(Localizer::translate(STRING::Again));
    nextButton_.setText(Localizer::translate(STRING::Next));

    titleText_.setString(Localizer::translate(STRING::LevelsLabel));
    levelPassedText_.setString(Localizer::translate(STRING::LevelPassed));

    auto levelPassedBounds = levelPassedSubstrate_.getGlobalBounds();
    levelPassedText_.setPosition(levelPassedBounds.left + 
        (levelPassedBounds.width - levelPassedText_.getGlobalBounds().width) / 2,
        levelPassedBounds.top + (levelPassedBounds.height - 
        levelPassedText_.getGlobalBounds().height) / 3);
}

Interface::Interface(std::shared_ptr<RenderWindow> window)
    : window_(window), currentMode_(MODE::MainMenuMode), 
    currentLevel_(0), passedLevel_(0), coins_(0), 
    drawing_(window_), dropDownList_(window_),
    levelPassedText_("", gl::font, IN::levelPassedTextSize),
    levelPassedSubstrate_(Vector2f(IN::levelPassedSubstrateWidth, 
        IN::levelPassedSubstrateHeight))    
{
    initTexts();
    loadTextures();
    createLevelButtons();
    initLevelPassedText();
    createMainMenuButtons();
    createFurtherActionButtons();

    std::tie(coins_, currentLevel_) = file_.readDataFromFile();
}

Interface::~Interface()
{
    file_.writeDataToFile(coins_, currentLevel_);
}

void Interface::showMenu()
{
    while (window_->isOpen())
    {
        pollEvents(window_);
    
        window_->clear();

        window_->draw(img_["background"]);
        window_->draw(img_["logo"]);

        newGameButton_.drawButton();
        continueButton_.drawButton();
        exitButton_.drawButton();

        dropDownList_.drawList();

        if (newGameButton_.isPressed())
        {
            if (currentLevel_)
            {
                if (showWarning(window_, 
                    Localizer::translate(STRING::LostResults)))
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
        
        std::string_view locale = dropDownList_.isPressed();
        if (locale.size())
        {
            Localizer::initLocalizer(locale.data());
            recreateTexts();
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

        window_->clear();
        
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
                    drawing_.setLevel(i + 1);
                    currentMode_ = MODE::PlayLevelMode;
                    break;
                }
            }
        }

        if (menuButton_.isPressed())
            currentMode_ = MODE::MainMenuMode;

        if (currentMode_ != ChooseLevelMode) break;

        window_->display();
    }
}

void Interface::displayLevel()
{
    drawing_.setCoins(getCoins());

    if (drawing_.drawWorld()) 
    {
        currentMode_ = MODE::ChooseAction;
        passedLevel_ = drawing_.getLevel();
    }
    else currentMode_ = MODE::ChooseLevelMode;

    coins_ = drawing_.getCoins();
}

void Interface::chooseFurtherAction()
{
    sleep(milliseconds(250));

    SoundManager::getManager().playSound("level_complete");
    
    updateCoinsText();

    if (passedLevel_ > currentLevel_) currentLevel_ = passedLevel_;

    Sprite background(*TextureManager::getManager().loadTextureFromFile(
        "textures/levels/" + std::to_string(passedLevel_) + "-2.png"), 
        { 0, 0, gl::Width, gl::Height });

    if (passedLevel_ == levelsMap.size()) 
        nextButton_.setButtonColor(gl::GREY);

    while(window_->isOpen())
    {
        pollEvents(window_);

        window_->clear();

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

            if (!drawing_.drawWorld()) 
                currentMode_ = MODE::ChooseLevelMode;

            coins_ = drawing_.getCoins();
            break;
        }

        else if (passedLevel_ != levelsMap.size() 
            && nextButton_.isPressed())
        {
            drawing_.setCoins(getCoins());
            drawing_.setLevel(passedLevel_ + 1);

            if (drawing_.drawWorld())
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
        Localizer::translate(STRING::SureToExit))) 
            currentMode_ = MainMenuMode;
    else window_->close();
}

void Interface::setCoins(int coins_num) { coins_ = coins_num; }

const int Interface::getCoins() const { return coins_; }

const size_t Interface::getCurrentMode() const { return currentMode_; }

void Interface::setCurrentLevel(size_t curr_level) { currentLevel_ = curr_level; }
