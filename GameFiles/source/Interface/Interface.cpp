#include "Interface.hpp"

Interface::Interface() noexcept
    : window_(new RenderWindow()), currentMode_(MODE::MainMenuMode), 
    currentLevel_(0), passedLevel_(0), coins_(0), 
    environment_(window_), dropDownList_(window_),
    levelPassedText_("", gl::font, IN::levelPassedTextSize),
    levelPassedSubstrate_(Vector2f(IN::levelPassedSubstrateWidth, 
        IN::levelPassedSubstrateHeight))    
{
    createWindow(gl::GameScreenWidth, gl::GameScreenHeight);

    initTexts();
    loadTextures();
    createLevelButtons();
    initLevelPassedText();
    createMainMenuButtons();
    createFurtherActionButtons();

    std::tie(coins_, currentLevel_) = file_.readDataFromFile();
}

Interface::~Interface() noexcept
{
    file_.writeDataToFile(coins_, currentLevel_);
}

bool Interface::isRunning() const noexcept { return window_->isOpen(); }

void Interface::showMenu() noexcept
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

void Interface::chooseLevel() noexcept
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
                    environment_.setLevel(i + 1);
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

void Interface::displayLevel() noexcept
{
    environment_.setCoins(this->getCoins());

    createWindow(gl::WindowWidth, gl::WindowHeight);

    if (environment_.drawWorld()) 
    {
        currentMode_ = MODE::ChooseAction;
        passedLevel_ = environment_.getLevel();
    }
    else currentMode_ = MODE::ChooseLevelMode;

    coins_ = environment_.getCoins();

    createWindow(gl::GameScreenWidth, gl::GameScreenHeight);
}

void Interface::chooseFurtherAction() noexcept
{
    sleep(milliseconds(250));

    SoundManager::getManager().playSound("level_complete");
    
    updateCoinsText();

    if (passedLevel_ > currentLevel_) currentLevel_ = passedLevel_;

    RectangleShape background(Vector2f(gl::GameScreenWidth, gl::GameScreenHeight));
    background.setTexture(TextureManager::getManager().loadTextureFromFile(
        "textures/levels/" + std::to_string(passedLevel_) + "-2.png").get());

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
            environment_.setCoins(getCoins());

            if (!environment_.drawWorld()) 
                currentMode_ = MODE::ChooseLevelMode;

            coins_ = environment_.getCoins();
            break;
        }

        else if (passedLevel_ != levelsMap.size() 
            && nextButton_.isPressed())
        {
            environment_.setCoins(getCoins());
            environment_.setLevel(passedLevel_ + 1);

            if (environment_.drawWorld())
                passedLevel_++;
            else currentMode_ = MODE::ChooseLevelMode;

            coins_ = environment_.getCoins();
            break;
        }

        window_->display();
    }
}

void Interface::exitGame() noexcept
{
    if (!showWarning(window_, 
        Localizer::translate(STRING::SureToExit))) 
            currentMode_ = MainMenuMode;
    else window_->close();
}

const size_t Interface::getCurrentMode() const noexcept { return currentMode_; }

void Interface::setCurrentLevel(size_t curr_level) noexcept { currentLevel_ = curr_level; }

void Interface::createWindow(int width, int height) noexcept
{
    window_->create(VideoMode(width, height), "Sokoban", Style::Close);
    window_->setPosition(Vector2i(
        (gl::ScreenWidth - width) / 2, 
        (gl::ScreenHeight - height) / 2));
}

void Interface::loadTextures() noexcept
{
    img_.emplace("background", RectangleShape(Vector2f(gl::GameScreenWidth, gl::GameScreenHeight))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/background").get());

    img_.emplace("logo", RectangleShape(Vector2f(IN::logoWidth, IN::logoHeight))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/logo").get());
    img_["logo"].setPosition((gl::GameScreenWidth - img_["logo"].getGlobalBounds().width) / 2, IN::logoYPos);

    img_.emplace("levels_back", RectangleShape(Vector2f(gl::GameScreenWidth, gl::GameScreenHeight))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/interface/levels_back").get());  

    img_.emplace("coin", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/coin").get()); 
}

void Interface::createMainMenuButtons() noexcept
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

void Interface::createLevelButtons() noexcept
{
    for(size_t i = 0; i < IN::rows; i++)
    {   
        for(size_t j = 0; j < IN::columns; j++)
        {
            levelsButtons_.emplace_back(Button(window_, 
                Text(std::to_string(i * IN::rows + j + 1), gl::font, IN::levelsButtonsTextSize), 
                IN::levelsButtonsXOffset + j * (IN::levelsButtonsSize + IN::betweenButtonsXPos), 
                IN::levelsButtonsYOffset + i * (IN::levelsButtonsSize + IN::betweenButtonsYPos), 
                IN::levelsButtonsSize, IN::levelsButtonsSize, gl::GREY, gl::BLUE));
        }
    }
}

void Interface::createFurtherActionButtons() noexcept
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

void Interface::initTexts() noexcept
{
    titleText_ = Text(Localizer::translate(STRING::LevelsLabel), gl::font, IN::titleTextSize);
    titleText_.setFillColor(gl::DARK_BLUE);
    titleText_.setPosition((gl::GameScreenWidth - titleText_.getGlobalBounds().width) / 2, 
        IN::titleTextYPos);

    coinsText_ = Text("", gl::font, IN::interfaceCoinsTextSize);
    coinsText_.setFillColor(gl::GOLD);
}

void Interface::initLevelPassedText() noexcept
{
    levelPassedSubstrate_.setPosition((gl::GameScreenWidth - 
        levelPassedSubstrate_.getGlobalBounds().width) / 2, IN::levelPassedSubstrateYPos);
    levelPassedSubstrate_.setFillColor(gl::BLUE);

    auto levelPassedBounds = levelPassedSubstrate_.getGlobalBounds();

    levelPassedText_.setString(Localizer::translate(STRING::LevelPassed));
    levelPassedText_.setPosition(levelPassedBounds.left + 
        (levelPassedBounds.width - levelPassedText_.getGlobalBounds().width) / 2,
        levelPassedBounds.top + (levelPassedBounds.height - 
        levelPassedText_.getGlobalBounds().height) / 3);
}

void Interface::updateLevelButtonsColor() noexcept
{
    Color color;
    for(size_t i = 0; i < levelsButtons_.size(); i++)
    {
        color = i <= currentLevel_ ? gl::GREEN : gl::GREY;
        levelsButtons_[i].setButtonColor(color);
    }
}

void Interface::updateCoinsText() noexcept
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

    coinsText_.setPosition((gl::GameScreenWidth - 
        (coinsTextWidth + coinsTextureWidth + gl::size / 3)) / 2, IN::coinTextureYPos);

    int coinsTextXPos = coinsText_.getGlobalBounds().left;

    img_["coin"].setPosition(coinsTextXPos + coinsTextWidth + gl::size / 3, 
        IN::coinTextureYPos + gl::size / 4);
}

void Interface::recreateTexts() noexcept
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

void Interface::setCoins(int coins_num) noexcept { coins_ = coins_num; }

const int Interface::getCoins() const noexcept { return coins_; }
