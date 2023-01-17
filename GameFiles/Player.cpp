#include "Player.h"

template<typename T>
void Player::Swap(T&& obj) noexcept
{
    window = obj.window;
    level = obj.level;
    boxes = obj.boxes;
    aims = obj.aims;
    offset1 = obj.offset1;
    offset2 = obj.offset2;
    img = obj.img;
    x = obj.x;
    y = obj.y;
    speed = obj.speed;
}

Player::Player(RenderWindow* window, const std::vector<std::vector<int>> level, const int& speed)
{
    this->window = window;
    this->level = level;
    this->speed = speed;

    offset1 = (Width - level[0].size() * size) / 2;
    offset2 = (Height - level.size() * size) / 2;

    for(size_t i = 0; i < level.size(); i++)
    {
        for(size_t j = 0; j < level[0].size(); j++)
        {
            switch(level[i][j])
            {
                case 3:
                    aims.emplace_back(std::pair(j * size + offset1, i * size + offset2));
                    break;
                case 4:
                    boxes.emplace_back(std::pair(j * size + offset1, i * size + offset2));
                    break;
                case 5:
                    x = j * size + offset1;
                    y = i * size + offset2;
                    break;
            }
        }
    }

    Texture texture;

    texture.loadFromFile("images/player/man.png");
    img["player"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img["player"].second.setTexture(&img["player"].first);
    img["player"].second.setPosition(x, y);

    texture.loadFromFile("images/player/box.png");
    img["box"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img["box"].second.setTexture(&img["box"].first);

    texture.loadFromFile("images/player/gold_box.png");
    img["gold_box"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img["gold_box"].second.setTexture(&img["gold_box"].first);
}

Player::Player(const Player& obj)
{
    Swap(obj);
}

Player::Player(Player&& obj) noexcept
{
    Swap(obj);

    obj.window = nullptr;
    obj.offset1 = obj.offset2 = obj.x = obj.y = obj.speed = 0;
}

Player& Player::operator=(const Player& obj)
{
    if (this != &obj)
    {
        Swap(obj);
    }
    return *this;
}

Player& Player::operator=(Player&& obj) noexcept
{
    if (this != &obj)
    {
        Swap(obj);

        obj.window = nullptr;
        obj.offset1 = obj.offset2 = obj.x = obj.y = obj.speed = 0;
    }
    return *this;
}

Player::~Player()
{
    window = nullptr;
}

size_t Player::checkPosition(const int& xPos, const int& yPos)
{
    return level[(yPos - offset2) / size][(xPos - offset1) / size];
}

std::pair<int, int>* Player::checkBoxes(const int& first, const int& second)
{
    for(const auto& box : boxes)
    {
        if (box.first == first && (box.second < second && second < box.second + size) || box.second == second && (box.first < first && first < box.first + size))
            return const_cast<std::pair<int, int>*>(&box);
    }
    return nullptr;
}

void Player::movement(const int& pressed_key)
{      
    switch(pressed_key)
    {
        case Keyboard::W: case Keyboard::Up:
        {
            int dist = (y - offset2) % size;
            if (checkPosition(x, y - speed) != 1) // check if the next (up) cell is a wall
            {
                auto it = checkBoxes(x, y - speed); // check if the next (up) cell is a box
                if (it)
                {
                    if (checkPosition(x, y - size - speed) != 1 && !checkBoxes(x, y - size - speed)) // check if the cell behind next one (up) is not a wall or a box
                    {
                        (*it).second -= speed;
                        y -= speed;
                    }
                    else // if the previous check has failed player and box should be moved up by the vlue of "dist" 
                    {
                        y -= dist && dist <= speed ? dist : 0;
                        (*it).second = y - size;
                    }
                }
                else y -= speed; // if the next (up) cell is not a wall or a box player should be moved right by the value of "speed"
            }
            else if (size - dist) y -= dist; // if the next (up) cell is a wall player should be moved right by the value of the difference between it's current "y"-position - size and the position of the next (up) cell
            break;
        }
        case Keyboard::A: case Keyboard::Left:
        {
            int dist = (x - offset1) % size;
            if (checkPosition(x - speed, y) != 1)
            {
                auto it = checkBoxes(x - speed, y);
                if (it)
                {
                    if (checkPosition(x - size - speed, y) != 1 && !checkBoxes(x - size - speed, y))
                    {
                        (*it).first -= speed;
                        x -= speed;
                    }
                    else
                    {
                        x -= dist && dist <= speed ? dist : 0;
                        (*it).first = x - size;
                    }
                }
                else x -= speed;
            }
            else if (size - dist) x -= dist;
            break;
        }
        case Keyboard::S: case Keyboard::Down:
        {
            int dist = size - (y - offset2) % size;
            if (checkPosition(x, y + size + speed) != 1)
            {
                auto it = checkBoxes(x, y + size + speed);
                if (it)
                {
                    if (checkPosition(x, y + 2 * size + speed) != 1 && !checkBoxes(x, y + 2 * size + speed))
                    {
                        (*it).second += speed;
                        y += speed;
                    }
                    else
                    {
                        y += dist && dist <= speed ? dist : 0;
                        (*it).second = y + size;
                    }
                }
                else y += speed;
            }
            else if (size - dist) y += dist;
            break;
        }
        case Keyboard::D: case Keyboard::Right:
        {
            int dist = size - (x - offset1) % size;
            if (checkPosition(x + size + speed, y) != 1) 
            {
                auto it = checkBoxes(x + size + speed, y); 
                if (it) 
                {
                    if (checkPosition(x + 2 * size + speed, y) != 1 && !checkBoxes(x + 2 * size + speed, y)) 
                    {
                        (*it).first += speed;
                        x += speed;
                    }
                    else
                    {
                        x += dist && dist <= speed ? dist : 0;
                        (*it).first = x + size;
                    }
                        
                }
                else x += speed;
            }
            else if (size - dist) x += dist;
            break;
        }
    }
    
    img["player"].second.setPosition(x, y);
}

void Player::alignPlayer(const int& released_key) // player and boxes must be aligned by cells
{
    switch(released_key)
    {
        case Keyboard::W: case Keyboard::Up:
        case Keyboard::S: case Keyboard::Down:
        {
            int dyUp = (y - offset2) % size; // here we know which cell is player closest to
            int dyDown = size - dyUp;

            auto it1 = checkBoxes(x, y - speed);
            auto it2 = checkBoxes(x, y + size + speed);

            y += dyUp < dyDown ? -dyUp : dyDown; // align player by cells

            if (it1) (*it1).second = y - size; // here we should check if there is a box above or beneath player. And if there is, we will align it too
            else if (it2) (*it2).second = y + size;

            break;
        }
        
        case Keyboard::A: case Keyboard::Left:
        case Keyboard::D: case Keyboard::Right:
        {
            int dxLeft = (x - offset1) % size;
            int dxRight = size - dxLeft;

            auto it1 = checkBoxes(x - speed, y);
            auto it2 = checkBoxes(x + size + speed, y);

            x += dxLeft < dxRight ? -dxLeft : dxRight;

            if (it1) (*it1).first = x - size;
            if (it2) (*it2).first = x + size;

            break;
        }
    }

    img["player"].second.setPosition(x, y);
}

bool Player::drawPlayer()
{
    int goals_counter = 0;

    window->draw(img["player"].second);
    for(auto& box : boxes)
    {
        if (std::find(aims.begin(), aims.end(), box) == aims.end()) 
        {
            img["box"].second.setPosition(box.first, box.second);
            window->draw(img["box"].second);
        }
        else
        {
            img["gold_box"].second.setPosition(box.first, box.second);
            window->draw(img["gold_box"].second);
            goals_counter++;
        }
    }

    return goals_counter == aims.size(); // check if all the boxes are in their positions
}   

void Player::restartLevel()
{
    aims.clear();
    boxes.clear();

    for(size_t i = 0; i < level.size(); i++)
    {
        for(size_t j = 0; j < level[0].size(); j++)
        {
            switch(level[i][j])
            {
                case 3:
                    aims.emplace_back(std::pair(j * size + offset1, i * size + offset2));
                    break;
                case 4:
                    boxes.emplace_back(std::pair(j * size + offset1, i * size + offset2));
                    break;
                case 5:
                    x = j * size + offset1;
                    y = i * size + offset2;
                    break;
            }
        }
    }

    img["player"].second.setPosition(x, y);
}
