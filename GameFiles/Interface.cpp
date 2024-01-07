#include "Interface.hpp"

void Interface::loadTextures()
{
    img_.emplace("background", RectangleShape(Vector2f(Width, Height))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/interface/background"));

    img_.emplace("logo", RectangleShape(Vector2f(0.416 * Width, 0.0975 * Height))).
        first->second.setTexture(TextureManager::getManager()->getTexture("textures/interface/logo"));
    img_["logo"].setPosition((Width - img_["logo"].getGlobalBounds().width) / 2, Height * 0.03);

    img_.emplace("levels_back", RectangleShape(Vector2f(Width, Height))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/interface/levels_back"));  

    img_.emplace("coin", RectangleShape(Vector2f(size, size))).first->second.setTexture(
        TextureManager::getManager()->getTexture("textures/player/coin")); 
    img_["coin"].setPosition(Width * 0.53, Height * 0.325); 
}

void Interface::createMainMenuButtons()
{
    int button_width = Width / 4.8, button_height = Height / 8;
    int xPos = (Width - button_width) / 2, yPos = (Height - 3 * button_height) / 4;

    newGameButton_ = Button(window_, Text(L"НОВАЯ ИГРА", font, 0.025 * Width), 
        xPos, yPos + button_height, button_width, button_height, GREEN, BLUE);

    continueButton_ = Button(window_, Text(L"ПРОДОЛЖИТЬ", font, 0.025 * Width), 
        xPos, 2 * yPos + button_height, button_width, button_height, GREEN, BLUE);

    exitButton_ = Button(window_, Text(L"ВЫХОД", font, 0.025 * Width), 
        xPos, 3 * yPos + button_height, button_width, button_height, GREEN, BLUE);

    menuButton_ = Button(window_, Text(L"МЕНЮ", font, 0.0375 * Width), 
        0.3958 * Width, 0.8125 * Height, size * 5, size * 2, GREEN, BLUE);
}

void Interface::createLevelButtons()
{
    size_t rows = 4;
    size_t columns = 4;

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            levelButtons_.emplace_back(Button(window_, 
                Text(std::to_string(i * rows + j + 1), font, 0.0375 * Width), 
                0.3083 * Width + j * (size * 2 + 0.0166 * Width), 
                0.14375 * Height + i * (size * 2 + 0.025 * Height), 
                size * 2, size * 2, GREY, BLUE));
        }
    }
}

void Interface::createFurtherActionButtons()
{
    int button_width = 0.16666 * Width;
    int button_height = 0.08125 * Height;

    levelsButton_ = Button(window_, Text(L"уровни", font, 0.025 * Width), 
        0.241666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
    repeatButton_ = Button(window_, Text(L"повтор", font, 0.025 * Width), 
        0.416666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
    nextButton_ = Button(window_, Text(L"дальше", font, 0.025 * Width), 
        0.591666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
}

void Interface::initTexts()
{
    titleText_ = Text(L"Уровни", font, 0.04 * Width);
    titleText_.setFillColor(DARK_BLUE);
    titleText_.setPosition(0.433 * Width, 0.0375 * Height);

    coinsText_ = Text("", font, 0.045 * Width);
    coinsText_.setPosition(Width * 0.45, Height * 0.31);
    coinsText_.setFillColor(GOLD);
}

void Interface::initLevelPassedText()
{
    levelPassedSubstrate_.setPosition(0.33333 * Width, 0.4375 * Height);
    levelPassedSubstrate_.setFillColor(BLUE);

    levelPassedText_.setString(L"Уровень пройден!");
    levelPassedText_.setPosition(Width / 3 + (levelPassedSubstrate_.getGlobalBounds().width - 
        levelPassedText_.getGlobalBounds().width) / 2, 
        0.43 * Height + (levelPassedSubstrate_.getGlobalBounds().height - 
        levelPassedText_.getGlobalBounds().height) / 2);
}

void Interface::updateLevelButtonsColor()
{
    for(size_t i = 0; i < levelButtons_.size(); i++)
    {
        if (i <= currentLevel_) 
            levelButtons_[i].setButtonColor(GREEN);
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
}

Interface::Interface(RenderWindow* window)
    : window_(window), currentMode_(MODE::MainMenuMode), 
    currentLevel_(0), passedLevel_(0), coins_(0), 
    drawing_(window),
    levelPassedText_("", font, 0.03333 * Width),
    levelPassedSubstrate_(Vector2f(0.341666 * Width, 0.08125 * Height))    
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
    while (window_->isOpen())
    {
        pollEvents(window_);
    
        window_->draw(img_["background"]);
        window_->draw(img_["logo"]);

        newGameButton_.drawButton();
        continueButton_.drawButton();
        exitButton_.drawButton();

        if (newGameButton_.isPressed())
        {
            if (currentLevel_)
            {
                if (showWarning(window_, L"Ваши результы будут утеряны!"))
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

        for(size_t i = 0; i < levelButtons_.size(); i++) 
        { 
            levelButtons_[i].drawButton();
            if (i <= currentLevel_)
            {
                if (levelButtons_[i].isPressed())
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

    if (passedLevel_ == 16) nextButton_.setButtonColor(GREY);

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
    if (!showWarning(window_, L"Вы уверены, что хотите выйти?")) currentMode_ = MainMenuMode;
    else window_->close();
}

void Interface::setCoins(int coins_num) { coins_ = coins_num; }

const int Interface::getCoins() const { return coins_; }

const size_t Interface::getCurrentMode() const { return currentMode_; }

void Interface::setCurrentLevel(size_t curr_level) { currentLevel_ = curr_level; }
