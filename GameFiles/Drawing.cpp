#include "Drawing.hpp"

bool showWarning(RenderWindow *window, const String& str)
{
    int button_width = 0.2083 * Width, button_height = Height / 8;

    RectangleShape warningWindow(Vector2f(button_width * 2, button_height * 2));
    warningWindow.setFillColor(DARK_BLUE);
    warningWindow.setPosition(0.292 * Width, 0.375 * Height);

    Text text(str + L"\n\t\t\t\tПродолжить?", font, 0.0216 * Width);
    text.setPosition(0.3291 * Width, 0.4 * Height);

    Button yesButton(window, Text(L"Да", font, 0.0225 * Width), 0.3917 * Width, 0.525 * Height, button_width / 2, button_height / 2, WHITE, BLUE);
    yesButton.setTextColor(DARK_BLUE);
    Button noButton(window, Text(L"Нет", font, 0.0225 * Width), 0.5077 * Width, 0.525 * Height, button_width / 2, button_height / 2, WHITE, BLUE);
    noButton.setTextColor(DARK_BLUE);

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
        window->draw(text);
        yesButton.drawButton();
        noButton.drawButton();

        if (yesButton.isPressed()) return true;
        else if (noButton.isPressed()) return false;

        window->display();
    }
}

void pollEvents(RenderWindow *window)
{
    Event event;

    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                    if (showWarning(window, L"Вы уверены, что хотите выйти?")) window->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                    if (showWarning(window, L"Вы уверены, что хотите выйти?")) window->close();
                return;
        }
        window->clear();
    }
}

Drawing::Drawing(RenderWindow* window) 
    : window_(window), coins_(0), player(window)
{
    Texture texture;

    texture.loadFromFile("images/cell/wall.png");
    world_["wall"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    world_["wall"].second.setTexture(&world_["wall"].first);

    texture.loadFromFile("images/cell/floor.png");
    world_["floor"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    world_["floor"].second.setTexture(&world_["floor"].first);

    texture.loadFromFile("images/cell/cross.png");
    world_["cross"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    world_["cross"].second.setTexture(&world_["cross"].first);

    texture.loadFromFile("images/player/coin.png");
    world_["coin"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    world_["coin"].second.setTexture(&world_["coin"].first);
    world_["coin"].second.setPosition(0.759 * Width, size / 2);
}

Drawing::~Drawing()
{
    window_ = nullptr;
}

bool Drawing::drawWorld(int level_num)
{
    std::string fileName = "images/levels/" + std::to_string(level_num) + "-1.png";

    Texture texture;

    Text levelText(L"Уровень" + std::to_string(level_num), font, 0.025 * Width);
    levelText.setFillColor(DARK_BLUE);
    levelText.setPosition(0.041666 * Width, 0.03125 * Height);

    Text coinsText(std::to_string(coins_), font, 0.039 * Width);
    coinsText.setFillColor(GOLD);
    coinsText.setPosition(0.68 * Width, size / 2.5);

    texture.loadFromFile("images/buttons/back.png");
    Button backButton(window_, 0.817 * Width, size / 2, size, size, &texture);

    texture.loadFromFile("images/buttons/restart.png");
    Button restartButton(window_, 0.875 * Width, size / 2, size, size, &texture);

    texture.loadFromFile("images/buttons/levels.png");
    Button levelsButton(window_, 0.933 * Width, size / 2, size, size, &texture);

    texture.loadFromFile(fileName);
    Sprite background(texture, Rect(0, 0, Width, Height)); 

    SoundBuffer buf;
    buf.loadFromFile("music/waste_money.wav");
    Sound wasteCoins(buf);

    size_t mapHeight = levelsMap[level_num].size();
    size_t mapWidth = levelsMap[level_num][0].size();  

    int offset1 = (Width - mapWidth * size) / 2;
    int offset2 = (Height - mapHeight * size) / 2;
    int tmpCoins = coins_;

    player.setLevel(levelsMap[level_num]);

    Event event;

    int count_pressed = 0; // is used to catch single press
    bool move_up = false, move_down = false, move_right = false, move_left = false;

    while(window_->isOpen())
    {
        while(window_->pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                    if (showWarning(window_, L"Вы уверены, что хотите выйти?")) 
                        window_->close();
                    break;
                case Event::KeyPressed:
                    count_pressed++;
                    switch(event.key.code)
                    {
                        case Keyboard::Escape:
                            if (showWarning(window_, L"Вы уверены, что хотите выйти?")) 
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
                    player.movement(event.key.code);
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
                    player.alignPlayer(event.key.code, count_pressed);
                    count_pressed = 0;
                    break;
            }
        }

        window_->clear();

        window_->draw(background); 
        window_->draw(levelText);
        window_->draw(coinsText);
        window_->draw(world_["coin"].second);

        for(size_t i = 0; i < mapHeight; i++)
        {
            for(size_t j = 0; j < mapWidth; j++)
            {
                switch(levelsMap[level_num][i][j])
                {
                    case 1:
                        world_["wall"].second.setPosition(j * size + offset1, i * size + offset2);
                        window_->draw(world_["wall"].second);
                        break;
                    case 2: case 3: case 4: case 5:
                        world_["floor"].second.setPosition(j * size + offset1, i * size + offset2);
                        window_->draw(world_["floor"].second);

                        if (levelsMap[level_num][i][j] == 3)
                        {
                            world_["cross"].second.setPosition(j * size + offset1, i * size + offset2);
                            window_->draw(world_["cross"].second);
                        }
                        break;
                }
            }
        }

        restartButton.drawButton();
        levelsButton.drawButton();
        backButton.drawButton();

        std::pair<int, int> res = player.drawPlayer();

        window_->display();

        if (res.second)
        {
            SoundBuffer buf;
            buf.loadFromFile("music/box_placed.wav");
            Sound levelCompleteSound(buf);
            levelCompleteSound.play();
            sleep(milliseconds(500));
        }

        if (backButton.isPressed()) 
        {
            if (coins_ - 10 >= 0) 
            {
                if (player.cancelMove()) 
                {
                    coins_ -= 10;
                    coinsText.setString(std::to_string(coins_));
                    wasteCoins.play();
                    sleep(milliseconds(500));
                }
            }
        }

        else if (res.first) return true;

        if (restartButton.isPressed()) 
        {
            coins_ = tmpCoins;
            coinsText.setString(std::to_string(coins_));
            player.restartLevel();
        }

        else if (levelsButton.isPressed()) 
        {
            if (showWarning(window_, L"Ваши результаты будут утеряны")) break;
        }
    }

    return false;
}

void Drawing::setCoins(int coins_num) { coins_ = coins_num; }

const int Drawing::getCoins() const { return coins_; }
