#include "Interface.hpp"

Interface::Interface(RenderWindow* window)
    : window_(window), currentMode_(MainMenuMode), currentLevel_(0),
    passedLevel_(0), coins_(0), drawing(window)
{
    Texture texture;

    texture.loadFromFile("images/interface/background.png");
    img_["background"] = std::pair(Texture(texture), RectangleShape(Vector2f(Width, Height)));
    img_["background"].second.setTexture(&img_["background"].first);

    texture.loadFromFile("images/interface/logo.png");
    img_["logo"] = std::pair(Texture(texture), RectangleShape(Vector2f(0.416 * Width, 0.0975 * Height)));
    img_["logo"].second.setTexture(&img_["logo"].first);
    img_["logo"].second.setPosition((Width - img_["logo"].second.getGlobalBounds().width) / 2, Height * 0.03);

    texture.loadFromFile("images/interface/levels_back.png");
    img_["levels_back"] = std::pair(Texture(texture), RectangleShape(Vector2f(Width, Height)));
    img_["levels_back"].second.setTexture(&img_["levels_back"].first);
}

Interface::~Interface()
{
    window_ = nullptr;
}

void Interface::showMenu()
{
    currentMode_ = MainMenuMode; 

    int button_width = Width / 4.8, button_height = Height / 8;
    int xPos = (Width - button_width) / 2, yPos = (Height - 3 * button_height) / 4;

    Button newGameButton(window_, Text(L"НОВАЯ ИГРА", font, 0.025 * Width), xPos, yPos + button_height, button_width, button_height, GREEN, BLUE);
    Button continueButton(window_, Text(L"ПРОДОЛЖИТЬ", font, 0.025 * Width), xPos, 2 * yPos + button_height, button_width, button_height, GREEN, BLUE);
    Button exitButton(window_, Text(L"ВЫХОД", font, 0.025 * Width), xPos, 3 * yPos + button_height, button_width, button_height, GREEN, BLUE);

    while (window_->isOpen())
    {
        pollEvents(window_);
    
        window_->draw(img_["background"].second);
        window_->draw(img_["logo"].second);

        newGameButton.drawButton();
        continueButton.drawButton();
        exitButton.drawButton();

        if (newGameButton.isPressed())
        {
            if (currentLevel_)
            {
                if (showWarning(window_, L"Ваши результы будут утеряны!"))
                {
                    currentLevel_ = 0;
                    currentMode_ = ChooseLevelMode;
                    break;
                }
            }
            else 
            {
                currentMode_ = ChooseLevelMode;
                break;
            }
        }
        else if (continueButton.isPressed())
        {
            currentMode_ = ChooseLevelMode;
            break;
        }
        else if (exitButton.isPressed())
        {
            currentMode_ = ExitMode;
            break;
        }

        window_->display();
    }
}

void Interface::chooseLevel()
{
    Text titleText(L"Уровни", font, 0.04 * Width);
    titleText.setFillColor(DARK_BLUE);
    titleText.setPosition(0.433 * Width, 0.0375 * Height);

    std::vector<Button> ButtonArray;
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            Color tmp_color;
            if (i * 4 + j <= currentLevel_) tmp_color = GREEN;
            else tmp_color = GREY;

            ButtonArray.emplace_back(Button(window_, 
                Text(std::to_string(i * 4 + j + 1), font, 0.0375 * Width), 
                0.3083 * Width + j * (size * 2 + 0.0166 * Width), 
                0.14375 * Height + i * (size * 2 + 0.025 * Height), 
                size * 2, size * 2, tmp_color, BLUE));
        }
    }
    ButtonArray.emplace_back(Button(window_, Text(L"МЕНЮ", font, 0.0375 * Width), 
        0.3958 * Width, 0.8125 * Height, size * 5, size * 2, GREEN, BLUE));
    
    while(window_->isOpen())
    {
        pollEvents(window_);
        
        window_->draw(img_["levels_back"].second);
        window_->draw(titleText);

        for(size_t i = 0; i < 17; i++) 
        { 
            ButtonArray[i].drawButton();
            if (i <= currentLevel_ || i == 16)
            {
                if (ButtonArray[i].isPressed())
                {
                    switch(i)
                    {
                        case 16:
                            currentMode_ = MainMenuMode;
                            break;
                        default:
                            drawing.setCoins(getCoins());
                            if (drawing.drawWorld(i + 1)) 
                            {
                                currentMode_ = ChooseAction;
                                passedLevel_ = i + 1;
                            }
                            coins_ = drawing.getCoins();
                            break;
                    }
                }
            }
        }

        if (currentMode_ != ChooseLevelMode) break;

        window_->display();
    }
}

void Interface::chooseFurtherAction()
{
    sleep(milliseconds(250));

    SoundBuffer buf;
    buf.loadFromFile("music/level_complete.wav");

    Sound levelCompleteSound(buf);
    levelCompleteSound.play();

    Text coinsText("", font, 0.045 * Width);
    coinsText.setPosition(Width * 0.45, Height * 0.31);
    coinsText.setFillColor(GOLD);

    Texture coinsTexture;
    coinsTexture.loadFromFile("images/player/coin.png");

    RectangleShape coinsRect(Vector2f(size, size));
    coinsRect.setTexture(&coinsTexture);
    coinsRect.setPosition(Width * 0.53, Height * 0.325);
    
    switch(passedLevel_)
    {
        case 1: case 2:
            coins_ += 20;
            coinsText.setString("+20");
            break;
        case 3: case 4: case 6:
        case 7: case 8: case 9:
        case 10: case 11:
            coins_ += 30;
            coinsText.setString("+30");
            break;
        case 5: case 12: case 13:
        case 14: case 15:
            coins_ += 40;
            coinsText.setString("+40");
            break;
        case 16:
            coins_ += 50;
            coinsText.setString("+50");
            break;
    }

    if (passedLevel_ > currentLevel_) currentLevel_ = passedLevel_;
    std::string fileName = "images/levels/" + std::to_string(passedLevel_) + "-2.png";

    Texture texture;
    texture.loadFromFile(fileName);

    Sprite background(texture, Rect(0, 0, Width, Height));

    RectangleShape rect(Vector2f(0.341666 * Width, 0.08125 * Height));
    rect.setPosition(0.33333 * Width, 0.4375 * Height);
    rect.setFillColor(BLUE);

    Text text(L"Уровень пройден!", font, 0.03333 * Width);
    text.setPosition(Width / 3 + (rect.getGlobalBounds().width - text.getGlobalBounds().width) / 2, 
        0.43 * Height + (rect.getGlobalBounds().height - text.getGlobalBounds().height) / 2);     

    int button_width = 0.16666 * Width;
    int button_height = 0.08125 * Height;

    Button levelsButton(window_, Text(L"уровни", font, 0.025 * Width), 0.241666 * Width, 
        0.5325 * Height, button_width, button_height, GREEN, BLUE);
    Button repeatButton(window_, Text(L"повтор", font, 0.025 * Width), 0.416666 * Width, 
        0.5325 * Height, button_width, button_height, GREEN, BLUE);
    Button nextButton(window_, Text(L"дальше", font, 0.025 * Width), 0.591666 * Width, 
        0.5325 * Height, button_width, button_height, GREEN, BLUE);
    if (passedLevel_ == 16) nextButton.setButtonColor(GREY);

    while(window_->isOpen())
    {
        pollEvents(window_);

        window_->draw(background);

        window_->draw(rect);
        window_->draw(text);
        window_->draw(coinsRect);
        window_->draw(coinsText);

        levelsButton.drawButton();
        repeatButton.drawButton();
        nextButton.drawButton();

        if (levelsButton.isPressed()) 
        {
            currentMode_ = ChooseLevelMode;
            break;
        }

        else if (repeatButton.isPressed())
        {
            drawing.setCoins(getCoins());
            if (!drawing.drawWorld(passedLevel_)) currentMode_ = ChooseLevelMode;
            coins_ = drawing.getCoins();
            break;
        }

        else if (passedLevel_ != 16 && nextButton.isPressed())
        {
            drawing.setCoins(getCoins());
            if (drawing.drawWorld(passedLevel_ + 1)) passedLevel_ = passedLevel_ + 1;
            else currentMode_ = ChooseLevelMode;
            coins_ = drawing.getCoins();
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

int Interface::readFile()
{
    std::fstream recordFile("data/records.ltx", std::ios_base::in | std::ios_base::binary);
    std::fstream coinsFile("data/coins.ltx", std::ios_base::in | std::ios_base::binary);
    
    if (!recordFile)
    {
        std::filesystem::create_directory("data");
        std::fstream tmp("data/records.ltx", std::ios_base::out | std::ios_base::binary);
        tmp << 0;
        tmp.close();
        currentLevel_ = 0;
        coins_ = 50;
    }
    else
    {
        std::string str;
        recordFile >> str;
        try
        {
            currentLevel_ = stoi(str);
        }
        catch(const std::exception& e)
        {
            currentLevel_ = 0;
            remove("data/records.ltx");
        }

        if (currentLevel_ < 0 || currentLevel_ > 15) currentLevel_ = 0;      
    }

    if (!coinsFile)
    {
        std::fstream tmp("data/records.ltx", std::ios_base::out | std::ios_base::binary);
        tmp << 50;
        tmp.close();
        coins_ = 50;
    }
    else
    {
        std::string str;
        coinsFile >> str;
        try
        {
            coins_ = stoi(str);
        }
        catch(const std::exception& e)
        {
            coins_ = 50;
            remove("data/records.ltx");
        }

        if (coins_ < 0) coins_ = 50;  
    }

    recordFile.close();
    coinsFile.close();

    return currentLevel_;
}

void Interface::writeFile()
{
    std::fstream recordFile("data/records.ltx", std::ios_base::out | std::ios_base::binary);
    recordFile << currentLevel_;
    recordFile.close();

    std::fstream coinsFile("data/coins.ltx", std::ios_base::out | std::ios_base::binary);
    coinsFile << coins_;
    coinsFile.close();
}

void Interface::setCoins(int coins_num) { coins_ = coins_num; }

const int Interface::getCoins() const { return coins_; }

const size_t Interface::getCurrentMode() const { return currentMode_; }

void Interface::setCurrentLevel(size_t curr_level) { currentLevel_ = curr_level; }
