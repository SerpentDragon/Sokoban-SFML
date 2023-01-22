#include "Player.h"

template<typename T>
void Player::Swap(T&& obj) noexcept
{
    window = obj.window;
    level = obj.level;
    boxes = obj.boxes;
    aims = obj.aims;
    playerMoves = obj.playerMoves;
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
    this->speed = speed > size ? size : speed;

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

    texture.loadFromFile("images/player/player.png");
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

size_t Player::checkPosition(const Vector2i& vec)
{
    return level[(vec.y - offset2) / size][(vec.x - offset1) / size];
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

std::pair<int, int>* Player::checkBoxes(const Vector2i& vec)
{
    for(const auto& box : boxes)
    {
        if (box.first == vec.x && (box.second < vec.y && vec.y < box.second + size) || box.second == vec.y && (box.first < vec.x && vec.x < box.first + size))
            return const_cast<std::pair<int, int>*>(&box);
    }
    return nullptr;
}

void Player::movement(const int& pressed_key)
{    
    int dist, destination = 1, *ptr, *coord;
    Vector2i nextPos, behindNextPos;
    std::pair<int, int>* it;

    int prevX = (x - offset1) / size, prevY = (y - offset2) / size;
    int currX, currY;

    std::vector<std::pair<int, int>> prevBoxesPos;
    for(const auto& box : boxes) prevBoxesPos.emplace_back(std::pair((box.first - offset1) / size, (box.second - offset2) / size));
    
    switch(pressed_key)
    {
        case Keyboard::W: case Keyboard::Up:
            dist = (y - offset2) % size;
            nextPos = Vector2i(x, y - speed);
            behindNextPos = Vector2i(x, y - size - speed);
            ptr = &y; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->second);
            // currX = (x + size - offset1) / size; currY = (y + size - offset2) / size;
            // currY++; prevY++;
            break;

        case Keyboard::A: case Keyboard::Left:
            dist = (x - offset1) % size;
            nextPos = Vector2i(x - speed, y);
            behindNextPos = Vector2i(x - size - speed, y);
            ptr = &x; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->first);
            // currX = (x + size - offset1) / size; currY = (y + size - offset2) / size;
            // currX++; prevX++;
            break;

        case Keyboard::S: case Keyboard::Down:
            dist = size - (y - offset2) % size;
            nextPos = Vector2i(x, y + size + speed);
            behindNextPos = Vector2i(x, y + 2 * size + speed);
            ptr = &y; it = checkBoxes(nextPos);
            coord = &(it->second);
            break;

        case Keyboard::D: case Keyboard::Right:
            dist = size - (x - offset1) % size;
            nextPos = Vector2i(x + size + speed, y);
            behindNextPos = Vector2i(x + 2 * size + speed, y);
            ptr = &x; it = checkBoxes(nextPos);
            coord = &(it->first);
            break;

        default: return;
    } 

    int playerMoved = *ptr; // this variable keep info if player moved or not
    bool checkBoxesAround = false; // this variable keep info if there is a box next to the player
    
    if (checkPosition(nextPos) != 1)
    {
        if (it)
        {
            if (checkPosition(behindNextPos) != 1 && !checkBoxes(behindNextPos))
            {
                (*ptr) += destination * speed;
                (*coord) += destination * speed;
                checkBoxesAround = true;
            }
            else
            {
                (*ptr) += dist && dist <= speed ? destination * dist : 0;
                (*coord) = (*ptr) + destination * size;
            }
        }
        else (*ptr) += destination * speed;
    }
    else if (size - dist) (*ptr) += destination * dist;

    currX = (x - offset1) / size; currY = (y - offset2) / size;

    if (currX != prevX || currY != prevY)
    {
        playerMoves.push(std::tuple(prevX, prevY, checkBoxesAround));
        for(const auto& el : prevBoxesPos) boxesMoves.push(el);
    }

    img["player"].second.setPosition(x, y);
}

void Player::alignPlayer(const int& released_key, const int& param) // player and boxes must be aligned by cells
{
    bool flag = false;

    if (param == 1)
    {
        switch(released_key)
        {
            case Keyboard::W: case Keyboard::Up:
                y -= size / 2;
                break;
            case Keyboard::A: case Keyboard::Left:
                x -= size / 2;
                break;
            case Keyboard::S: case Keyboard::Down:
                if (checkPosition(x, y + 1.5 * size) != 1) 
                {
                    auto it = checkBoxes(x, y + 1.5 * size);
                    if (it)
                    {
                        if (checkPosition(x, y + 2.5 * size) != 1 && !checkBoxes(x, y + 2.5 * size)) y += size / 2;
                    }
                    else y += size / 2; 
                }
                break;
            case Keyboard::D: case Keyboard::Right:
                if (checkPosition(x + 1.5 * size, y) != 1) 
                {
                    auto it = checkBoxes(x + 1.5 * size, y);
                    if (it)
                    {
                        if (checkPosition(x + 2.5 * size, y) != 1 && !checkBoxes(x + 2.5 * size, y)) x += size / 2;
                    }
                    else x += size / 2;
                }
                break;
            default: return;
        }
    }

    switch(released_key)
    {
        case Keyboard::W: case Keyboard::Up:
        case Keyboard::S: case Keyboard::Down:
        {
            int dyUp = (y - offset2) % size; // here we know which cell is player closest to
            int dyDown = size - dyUp;

            auto it1 = checkBoxes(x, y - speed);
            auto it2 = checkBoxes(x, y + size + speed);

            dyUp < dyDown ? y -= dyUp : (y += dyDown, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::S || released_key == Keyboard::Down) 
                {
                    playerMoves.push(std::tuple((x - offset1) / size, (y - offset2) / size - 1, false));
                    for(const auto& box : boxes) boxesMoves.push(std::pair((box.first - offset1) / size, (box.second - offset2) / size));
                }
                else if ((released_key == Keyboard::W || released_key == Keyboard::Up) && dyDown != size / 2)
                {
                    playerMoves.pop();
                    for(int i = 0; i < boxes.size(); i++) boxesMoves.pop();
                }
            }

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

            dxLeft < dxRight ? x -= dxLeft : (x += dxRight, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::D || released_key == Keyboard::Right) 
                {
                    playerMoves.push(std::tuple((x - offset1) / size - 1, (y - offset2) / size, false));
                    for(const auto& box : boxes) 
                    {
                        boxesMoves.push(std::pair((box.first - offset1) / size, (box.second - offset2) / size));
                    }
                }
                else if ((released_key == Keyboard::A || released_key == Keyboard::Left) && dxRight != size / 2) 
                {
                    playerMoves.pop();
                    for(int i = 0; i < boxes.size(); i++) boxesMoves.pop();
                }
            }
            

            if (it1) (*it1).first = x - size;
            if (it2) (*it2).first = x + size;

            break;
        }

        default: return;
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

    while(!playerMoves.empty()) playerMoves.pop();
    while(!boxesMoves.empty()) boxesMoves.pop();

    img["player"].second.setPosition(x, y);
}

bool Player::cancelMove()
{
    if (!playerMoves.empty())
    {
        x = std::get<0>(playerMoves.top()) * size + offset1;
        y = std::get<1>(playerMoves.top()) * size + offset2;

        img["player"].second.setPosition(x, y);
        window->draw(img["player"].second);

        for(int i = boxes.size() - 1; i >= 0; i--)
        {
            boxes[i].first = boxesMoves.top().first * size + offset1;
            boxes[i].second = boxesMoves.top().second * size + offset2;

            img["box"].second.setPosition(boxes[i].first, boxes[i].second);
            window->draw(img["box"].second);

            boxesMoves.pop();
        }

        playerMoves.pop();
        return true;
    }
    return false;
}
