#include "Drawing.hpp"

Drawing::Drawing(std::shared_ptr<RenderWindow> window) noexcept 
    : window_(window), coins_(0), player_(window),
    levelText_("", gl::font, DR::levelTextSize),
    coinsText_("", gl::font, DR::coinsTextSize),
    background_(Vector2f(gl::Width, gl::Height)), level_(0)
{
    loadTextures();
    createButtons();

    levelText_.setFillColor(gl::DARK_BLUE);

    coinsText_.setFillColor(gl::GOLD);
    coinsText_.setPosition(DR::drawingCoinsTextXPos, DR::drawingCoinsTextYPos);
}

void Drawing::setLevel(const int level) noexcept { level_ = level; }

int Drawing::getLevel() const noexcept { return level_; }

bool Drawing::drawWorld() noexcept
{
    updateBackground(level_);
    updateLevelText(level_);
    updateCoinsText();

    size_t mapHeight = levelsMap[level_].size();
    size_t mapWidth = levelsMap[level_][0].size();
    int offset1 = (gl::Width - mapWidth * gl::size) / 2;
    int offset2 = (gl::Height - mapHeight * gl::size) / 2;

    int initialCoinsValue = coins_;

    player_.setLevel(levelsMap[level_]);

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
                {
                    if (showWarning(window_, 
                        Localizer::translate(STRING::SureToExit)))
                            window_->close();
                    break;
                }
                case Event::KeyPressed:
                {
                    count_pressed++;
                    switch(event.key.code)
                    {
                        case Keyboard::Escape:
                            if (showWarning(window_, 
                                Localizer::translate(STRING::SureToExit)))
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
                }   
                case Event::KeyReleased:
                {
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
        }

        window_->clear();

        window_->draw(background_); 
        window_->draw(levelText_);
        window_->draw(coinsText_);
        window_->draw(world_["coin"]);
        
        drawMap(mapHeight, mapWidth, levelsMap[level_], offset1, offset2);

        backButton_.drawButton();
        restartButton_.drawButton();
        levelsButton_.drawButton();

        saveButton_.drawButton();
        showCommitTreeButton_.drawButton();

        std::pair<int, int> res = player_.drawPlayer();

        if (res.second)
        {
            SoundManager::getManager().playSound("box_placed");
        }

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
            if (showWarning(window_, Localizer::translate(STRING::LostResults))) 
                break;
        }
        else if (saveButton_.isPressed())
        {

        }
        else if (showCommitTreeButton_.isPressed())
        {
            displayVCSWindow();
        }

        window_->display();
    }

    return false;
}

void Drawing::setCoins(int coins_num) noexcept { coins_ = coins_num; }

const int Drawing::getCoins() const noexcept { return coins_; }

bool showWarning(std::shared_ptr<RenderWindow> window, const String& str) noexcept
{
    RectangleShape warningWindow(
            Vector2f(DR::warningWindowWidth, DR::warningWindowHeight));
    warningWindow.setFillColor(gl::DARK_BLUE);
    warningWindow.setPosition(DR::warningWindowXPos, 
        DR::warningWindowYPos);

    String continueText = Localizer::translate(STRING::Continue);

    Text mainMessage(str, gl::font, DR::warningTextSize);
    mainMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - mainMessage.getGlobalBounds().width) / 2, 
        DR::warningWindowYPos + gl::size / 3);
    
    Text continueMessage(continueText, gl::font, DR::warningTextSize);
    continueMessage.setPosition(DR::warningWindowXPos + 
        (DR::warningWindowWidth - continueMessage.getGlobalBounds().width) / 2,
        mainMessage.getGlobalBounds().top + mainMessage.getGlobalBounds().height + gl::size / 4);

    Button yesButton(window, Text(Localizer::translate(STRING::Yes), gl::font, 
        0.0225 * gl::Width), DR::yesButtonXPos, DR::yesButtonYPos, 
        DR::warningButtonWidth, DR::warningButtonHeight, gl::WHITE, gl::BLUE);
    yesButton.setTextColor(gl::DARK_BLUE);
    
    Button noButton(window, Text(Localizer::translate(STRING::No), gl::font, 
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

void pollEvents(std::shared_ptr<RenderWindow> window) noexcept
{
    Event event;

    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                    if (showWarning(window, 
                        Localizer::translate(STRING::SureToExit))) window->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    if (showWarning(window, 
                        Localizer::translate(STRING::SureToExit))) window->close();
                return;
        }
        window->clear();
    }
}

void Drawing::loadTextures() noexcept
{
    world_.emplace("wall", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/wall").get());

    world_.emplace("floor", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/floor").get());

    world_.emplace("cross", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/cell/cross").get());

    world_.emplace("coin", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/coin").get());
    world_["coin"].setPosition(0.759 * gl::Width, gl::size / 2);
}

void Drawing::createButtons() noexcept
{
    backButton_ = Button(window_, DR::backButtonXPos, gl::size / 2, gl::size, gl::size, 
        TextureManager::getManager().getTexture("textures/buttons/back"));

    restartButton_ = Button(window_, DR::restartButtonXPos, gl::size / 2, gl::size, gl::size, 
        TextureManager::getManager().getTexture("textures/buttons/restart"));

    levelsButton_ = Button(window_, DR::levelsButtonXPos, gl::size / 2, gl::size, gl::size, 
        TextureManager::getManager().getTexture("textures/buttons/levels"));

    saveButton_ = Button(window_, DR::saveButtonXPos, gl::size / 2, gl::size, gl::size, 
        TextureManager::getManager().getTexture("textures/buttons/save"));

    showCommitTreeButton_ = Button(window_, DR::showCommitTreeButtonXPos, gl::size / 2, gl::size, gl::size, 
        TextureManager::getManager().getTexture("textures/buttons/fork"));
}

void Drawing::updateLevelText(int level) noexcept
{
    levelText_.setString(Localizer::translate(STRING::Level) 
        + std::to_string(level));

    const int levelTextXPos = (gl::Width - levelText_.getGlobalBounds().width) / 2;
    levelText_.setPosition(levelTextXPos, DR::levelTextYPos);
}

void Drawing::updateCoinsText() noexcept
{
    coinsText_.setString(std::to_string(coins_));
    coinsText_.setPosition(world_["coin"].getGlobalBounds().left - 
        coinsText_.getGlobalBounds().width - gl::size / 2, DR::drawingCoinsTextYPos);
}

void Drawing::updateBackground(int level) noexcept
{
    background_.setTexture(TextureManager::getManager().
        loadTextureFromFile("textures/levels/" + 
        std::to_string(level) + "-1.png").get());
}

void Drawing::drawMap(size_t height, size_t width, 
    const std::vector<std::vector<int>>& map,
    int offset1, int offset2) noexcept
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

void Drawing::displayVCSWindow() noexcept
{
    VCSWindow vcsWindow(window_);

    vcsWindow.displayVCSWIndow();
}
