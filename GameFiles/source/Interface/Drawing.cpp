#include "Drawing.hpp"

bool showWarning(std::shared_ptr<RenderWindow> window, const String& str)
{
    RectangleShape warningWindow(
            Vector2f(DR::warningWindowWidth, DR::warningWindowHeight));
    warningWindow.setFillColor(gl::DARK_BLUE);
    warningWindow.setPosition(DR::warningWindowXPos, 
        DR::warningWindowYPos);

    String continueText = Localizer::translate(L"Continue?");

    Text mainMessage(str, gl::font, DR::warningTextSize);
    mainMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - mainMessage.getGlobalBounds().width) / 2, 
        DR::warningWindowYPos + gl::size / 3);
    
    Text continueMessage(continueText, gl::font, DR::warningTextSize);
    continueMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - continueMessage.getGlobalBounds().width) / 2,
        mainMessage.getGlobalBounds().top + mainMessage.getGlobalBounds().height + gl::size / 4);

    Button yesButton(window, Text(Localizer::translate(L"Yes"), gl::font, 
        0.0225 * gl::Width), DR::yesButtonXPos, DR::yesButtonYPos, 
        DR::warningButtonWidth, DR::warningButtonHeight, gl::WHITE, gl::BLUE);
    yesButton.setTextColor(gl::DARK_BLUE);
    
    Button noButton(window, Text(Localizer::translate(L"No"), gl::font, 
        0.0225 * gl::Width), DR::noButtonXPos, DR::noButtonYPos, 
        DR::warningButtonWidth, DR::warningButtonHeight, gl::WHITE, gl::BLUE);
    noButton.setTextColor(gl::DARK_BLUE);

    Event event;

    while(true)
    {
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed: // we shouldn't process these events because otherwise a lot of warning windows will be opened
                case Event::KeyPressed:
                    break;
            }
        }

        window->draw(warningWindow);
        window->draw(mainMessage);
        window->draw(continueMessage);
        yesButton.drawButton();
        noButton.drawButton();

        if (yesButton.isPressed()) return true;
        else if (noButton.isPressed()) return false;

        window->display();
    }
}

void pollEvents(std::shared_ptr<RenderWindow> window)
{
    Event event;

    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                    if (showWarning(window, 
                        Localizer::translate(L"Are you sure you want to exit?"))) window->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    if (showWarning(window, 
                        Localizer::translate(L"Are you sure you want to exit?"))) window->close();
                return;
        }
        window->clear();
    }
}

void Drawing::loadTextures()
{
    world_.emplace("wall", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/wall"));

    world_.emplace("floor", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/floor"));

    world_.emplace("cross", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/cross"));

    world_.emplace("coin", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/coin"));
    world_["coin"].setPosition(0.759 * gl::Width, gl::size / 2);
}

void Drawing::createButtons()
{
    backButton_ = Button(window_, DR::backButtonXPos, gl::size / 2, gl::size, gl::size, 
        std::make_shared<Texture>(*TextureManager::getManager().getTexture("textures/buttons/back")));

    restartButton_ = Button(window_, DR::restartButtonXPos, gl::size / 2, gl::size, gl::size, 
        std::make_shared<Texture>(*TextureManager::getManager().getTexture("textures/buttons/restart")));

    levelsButton_ = Button(window_, DR::levelsButtonXPos, gl::size / 2, gl::size, gl::size, 
        std::make_shared<Texture>(*TextureManager::getManager().getTexture("textures/buttons/levels")));
}

void Drawing::updateLevelText(int level)
{
    levelText_.setString(Localizer::translate(L"Level ") 
        + std::to_string(level));
}

void Drawing::updateCoinsText()
{
    coinsText_.setString(std::to_string(coins_));
    coinsText_.setPosition(world_["coin"].getGlobalBounds().left - 
        coinsText_.getGlobalBounds().width - gl::size / 2, DR::drawingCoinsTextYPos);
}

void Drawing::updateBackground(int level)
{
    background_.setTexture(TextureManager::getManager().
        loadTextureFromFile("textures/levels/" + 
        std::to_string(level) + "-1.png"));
}

void Drawing::drawMap(size_t height, size_t width, 
    const std::vector<std::vector<int>>& map,
    int offset1, int offset2)
{
    for(size_t i = 0; i < height; i++)
    {
        for(size_t j = 0; j < width; j++)
        {
            switch(map[i][j])
            {
                case FIELD::NO_FIELD:
                    break;
                case FIELD::WALL:
                    world_["wall"].setPosition(j * gl::size + offset1, i * gl::size + offset2);
                    window_->draw(world_["wall"]);
                    break;
                default:
                    world_["floor"].setPosition(j * gl::size + offset1, i * gl::size + offset2);
                    window_->draw(world_["floor"]);

                    if (map[i][j] == FIELD::AIM)
                    {
                        world_["cross"].setPosition(j * gl::size + offset1, i * gl::size + offset2);
                        window_->draw(world_["cross"]);
                    }
                    break;
            }
        }
    }
}

Drawing::Drawing(std::shared_ptr<RenderWindow> window) 
    : window_(window), coins_(0), player_(window),
    levelText_("", gl::font, DR::levelTextSize),
    coinsText_("", gl::font, DR::coinsTextSize),
    background_(Vector2f(gl::Width, gl::Height))
{
    loadTextures();
    createButtons();

    levelText_.setFillColor(gl::DARK_BLUE);
    levelText_.setPosition(DR::levelTextXPos, DR::levelTextYPos);

    coinsText_.setFillColor(gl::GOLD);
    coinsText_.setPosition(DR::drawingCoinsTextXPos, DR::drawingCoinsTextYPos);
}

bool Drawing::drawWorld(const int level)
{
    updateBackground(level);
    updateLevelText(level);
    updateCoinsText();

    size_t mapHeight = levelsMap[level].size();
    size_t mapWidth = levelsMap[level][0].size();
    int offset1 = (gl::Width - mapWidth * gl::size) / 2;
    int offset2 = (gl::Height - mapHeight * gl::size) / 2;

    int initialCoinsValue = coins_;

    player_.setLevel(levelsMap[level]);

    Event event;

    int count_pressed = 0; // is used to catch single press
    bool move_up = false, move_down = false;
    bool move_right = false, move_left = false;

    while(window_->isOpen())
    {
        while(window_->pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                    if (showWarning(window_, 
                        Localizer::translate(L"Are you sure you want to exit?")))
                            window_->close();
                    break;
                case Event::KeyPressed:
                    count_pressed++;
                    switch(event.key.code)
                    {
                        case Keyboard::Escape:
                            if (showWarning(window_, 
                                Localizer::translate(L"Are you sure you want to exit?")))
                                    window_->close();
                            break;
                        case Keyboard::W: case Keyboard::Up:
                            if (!move_down && !move_right && !move_left) move_up = true; 
                            else event.key.code = Keyboard::Key::Unknown; 
                            break;
                        case Keyboard::A: case Keyboard::Left:
                            if (!move_down && !move_up && !move_right) move_left = true;
                            else event.key.code = Keyboard::Key::Unknown;
                            break;
                        case Keyboard::S: case Keyboard::Down:
                            if (!move_up && !move_right && !move_left) move_down = true;
                            else event.key.code = Keyboard::Key::Unknown;
                            break;
                        case Keyboard::D: case Keyboard::Right:
                            if (!move_down && !move_up && !move_left) move_right = true; 
                            else event.key.code = Keyboard::Key::Unknown;
                            break;
                    }
                    player_.movement(event.key.code);
                    break;
                case Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case Keyboard::W: case Keyboard::Up: 
                            move_up = false; 
                            break;
                        case Keyboard::A: case Keyboard::Left:
                            move_left = false; 
                            break;
                        case Keyboard::S: case Keyboard::Down:
                            move_down = false;
                            break;
                        case Keyboard::D: case Keyboard::Right:
                            move_right = false;
                            break;
                    }
                    player_.alignPlayer(event.key.code, count_pressed);
                    count_pressed = 0;
                    break;
            }
        }

        window_->clear();

        window_->draw(background_); 
        window_->draw(levelText_);
        window_->draw(coinsText_);
        window_->draw(world_["coin"]);
        
        drawMap(mapHeight, mapWidth, levelsMap[level], offset1, offset2);

        backButton_.drawButton();
        restartButton_.drawButton();
        levelsButton_.drawButton();

        std::pair<int, int> res = player_.drawPlayer();

        window_->display();

        if (res.second)
            SoundManager::getManager().playSound("box_placed");

        if (backButton_.isPressed()) 
        {
            if (coins_ >= price_) 
            {
                if (player_.cancelMove()) 
                {
                    coins_ -= price_;
                    updateCoinsText();
                    SoundManager::getManager().playSound("waste_money");
                }
            }
        }
        else if (res.first) return true;

        if (restartButton_.isPressed()) 
        {
            coins_ = initialCoinsValue;
            updateCoinsText();
            player_.restartLevel();
        }

        else if (levelsButton_.isPressed()) 
        {
            if (showWarning(window_, 
                Localizer::translate(L"Your results will be lost!"))) 
                    break;
        }
    }

    return false;
}

void Drawing::setCoins(int coins_num) { coins_ = coins_num; }

const int Drawing::getCoins() const { return coins_; }
