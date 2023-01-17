#include "Interface.h"
#include <iostream>

template<typename T>
void Interface::Swap(T&& obj) noexcept
{
    window = obj.window;
    img = obj.img;
    currentMode = obj.currentMode;
    currentLevel = obj.currentLevel;
    passedLevel = obj.passedLevel;
}

Interface::Interface(RenderWindow* window)
{
    this->window = window;

    Texture texture;

    texture.loadFromFile("images/interface/background.png");
    img["background"] = std::pair(Texture(texture), RectangleShape(Vector2f(Width, Height)));
    img["background"].second.setTexture(&img["background"].first);

    texture.loadFromFile("images/interface/logo.png");
    img["logo"] = std::pair(Texture(texture), RectangleShape(Vector2f(0.416 * Width, 0.0975 * Height)));
    img["logo"].second.setTexture(&img["logo"].first);
    img["logo"].second.setPosition((Width - img["logo"].second.getGlobalBounds().width) / 2, Height * 0.03);

    texture.loadFromFile("images/interface/levels_back.png");
    img["levels_back"] = std::pair(Texture(texture), RectangleShape(Vector2f(Width, Height)));
    img["levels_back"].second.setTexture(&img["levels_back"].first);

    currentMode = MainMenuMode;
    currentLevel = 0;
    passedLevel = 0;   
}

Interface::Interface(const Interface& obj)
{
    Swap(obj);
}

Interface::Interface(Interface&& obj) noexcept 
{
    Swap(obj);

    obj.window = nullptr;
    currentMode = passedLevel = currentLevel = 0;
}

Interface& Interface::operator=(const Interface& obj)
{
    if (this != &obj)
    {
        Swap(obj);
    }
    return *this;
}

Interface& Interface::operator=(Interface&& obj) noexcept
{
    if (this != &obj)
    {
        Swap(obj);
        
        obj.window = nullptr;
        currentMode = passedLevel = currentLevel = 0;
    }
    return *this;
}

Interface::~Interface()
{
    // We don't delete window pointer because it was taken by link and also will be deleted with destructor in main.cpp
    window = nullptr;
}

void Interface::showMenu()
{
    currentMode = MainMenuMode; 

    Font font;
    font.loadFromFile("fonts/arial_bold.ttf"); 

    int button_width = Width / 4.8, button_height = Height / 8;
    int xPos = (Width - button_width) / 2, yPos = (Height - 3 * button_height) / 4;

    Button newGameButton(window, Text(L"НОВАЯ ИГРА", font, 0.025 * Width), xPos, yPos + button_height, button_width, button_height, GREEN, BLUE);
    Button continueButton(window, Text(L"ПРОДОЛЖИТЬ", font, 0.025 * Width), xPos, 2 * yPos + button_height, button_width, button_height, GREEN, BLUE);
    Button exitButton(window, Text(L"ВЫХОД", font, 0.025 * Width), xPos, 3 * yPos + button_height, button_width, button_height, GREEN, BLUE);

    while (window->isOpen())
    {
        pollEvents(window);
    
        window->draw(img["background"].second);
        window->draw(img["logo"].second);

        newGameButton.drawButton();
        continueButton.drawButton();
        exitButton.drawButton();

        if (newGameButton.isPressed())
        {
            if (currentLevel)
            {
                if (showWarning(window, L"Ваши результы будут утеряны!"))
                {
                    currentLevel = 0;
                    currentMode = ChooseLevelMode;
                    break;
                }
            }
            else 
            {
                currentMode = ChooseLevelMode;
                break;
            }
        }
        else if (continueButton.isPressed())
        {
            currentMode = ChooseLevelMode;
            break;
        }
        else if (exitButton.isPressed())
        {
            currentMode = ExitMode;
            break;
        }

        window->display();
    }
}

void Interface::chooseLevel()
{
    Font font;
    font.loadFromFile("fonts/arial_bold.ttf"); 

    Text titleText(L"Уровни", font, 0.04 * Width);
    titleText.setFillColor(DARK_BLUE);
    titleText.setPosition(0.433 * Width, 0.0375 * Height);

    Drawing draw(window);

    std::vector<Button> ButtonArray;
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            Color tmp_color;
            if (i * 4 + j <= currentLevel) tmp_color = GREEN;
            else tmp_color = GREY;

            ButtonArray.emplace_back(Button(window, Text(std::to_string(i * 4 + j + 1), font, 0.0375 * Width), 0.3083 * Width + j * (size * 2 + 0.0166 * Width), 
                                    0.14375 * Height + i * (size * 2 + 0.025 * Height), size * 2, size * 2, tmp_color, BLUE));
        }
    }
    ButtonArray.emplace_back(Button(window, Text(L"МЕНЮ", font, 0.0375 * Width), 0.3958 * Width, 0.8125 * Height, size * 5, size * 2, GREEN, BLUE));
    
    while(window->isOpen())
    {
        pollEvents(window);
        
        window->draw(img["levels_back"].second);
        window->draw(titleText);

        for(size_t i = 0; i < 17; i++) 
        { 
            ButtonArray[i].drawButton();
            if (i <= currentLevel || i == 16)
            {
                if (ButtonArray[i].isPressed())
                {
                    switch(i)
                    {
                        case 16:
                            currentMode = MainMenuMode;
                            break;
                        default:
                            if (draw.drawWorld(i + 1)) 
                            {
                                currentMode = ChooseAction;
                                passedLevel = i + 1;
                            }
                            break;
                    }
                }
            }
        }

        if (currentMode != ChooseLevelMode) break;

        window->display();
    }
}

void Interface::chooseFurtherAction()
{
    sleep(milliseconds(250));

    if (passedLevel > currentLevel) currentLevel = passedLevel;
    std::string fileName = "images/levels/" + std::to_string(passedLevel) + "-2.png";

    Texture texture;
    texture.loadFromFile(fileName);

    Sprite background(texture, Rect(0, 0, Width, Height));

    RectangleShape rect(Vector2f(0.341666 * Width, 0.08125 * Height));
    rect.setPosition(0.33333 * Width, 0.4375 * Height);
    rect.setFillColor(BLUE);

    Font font;
    font.loadFromFile("fonts/arial_bold.ttf"); 

    Text text(L"Уровень пройден!", font, 0.03333 * Width);
    text.setPosition(Width / 3 + (rect.getGlobalBounds().width - text.getGlobalBounds().width) / 2, 0.43 * Height + (rect.getGlobalBounds().height - text.getGlobalBounds().height) / 2);     

    int button_width = 0.16666 * Width;
    int button_height = 0.08125 * Height;

    std::cout << passedLevel << std::endl;

    Button levelsButton(window, Text(L"уровни", font, 0.025 * Width), 0.241666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
    Button repeatButton(window, Text(L"повтор", font, 0.025 * Width), 0.416666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
    Button nextButton(window, Text(L"дальше", font, 0.025 * Width), 0.591666 * Width, 0.5325 * Height, button_width, button_height, GREEN, BLUE);
    if (passedLevel == 16) nextButton.setButtonColor(GREY);

    while(window->isOpen())
    {
        pollEvents(window);

        window->draw(background);

        window->draw(rect);
        window->draw(text);

        levelsButton.drawButton();
        repeatButton.drawButton();
        nextButton.drawButton();

        if (levelsButton.isPressed()) 
        {
            currentMode = ChooseLevelMode;
            break;
        }

        else if (repeatButton.isPressed())
        {
            Drawing draw(window);
            if (!draw.drawWorld(passedLevel)) currentMode = ChooseLevelMode;
            break;
        }

        else if (passedLevel != 16 && nextButton.isPressed())
        {
            Drawing draw(window);
            if (draw.drawWorld(passedLevel + 1)) passedLevel = passedLevel + 1;
            else currentMode = ChooseLevelMode;
            break;
        }

        window->display();
    }
}

void Interface::exitGame()
{
    if (!showWarning(window, L"Вы уверены, что хотите выйти?")) currentMode = MainMenuMode;
    else window->close();
}

int Interface::readFile()
{
    int currentLevel;
    std::fstream file("data/records.ltx", std::ios_base::in | std::ios_base::binary);
    
    if (!file)
    {
        std::filesystem::create_directory("data");
        std::fstream tmp("data/records.ltx", std::ios_base::out | std::ios_base::binary);
        tmp << 0;
        tmp.close();
        currentLevel = 0;
    }
    else
    {
        std::string str;
        file >> str;
        try
        {
            currentLevel = stoi(str);
        }
        catch(const std::exception& e)
        {
            currentLevel = 0;
            remove("data/records.ltx");
            std::filesystem::create_directory("data");
        }

        if (currentLevel < 0 || currentLevel > 15) currentLevel = 0;

       
        file.close();
    }

    return currentLevel;
}

void Interface::writeFile()
{
    std::fstream file("data/records.ltx", std::ios_base::out | std::ios_base::binary);
    file << currentLevel;
    file.close();
}

const size_t Interface::getCurrentMode() const { return currentMode; }

void Interface::setCurrentLevel(const size_t& curr_level) { currentLevel = curr_level; }
