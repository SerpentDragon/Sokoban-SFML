#include "Player.hpp"

Player::Player(RenderWindow* window, int speed)
    : window_(window)
{
    this->speed_ = speed > size ? size : speed;

    Texture texture;

    texture.loadFromFile("images/player/player.png");
    img_["player"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img_["player"].second.setTexture(&img_["player"].first);

    texture.loadFromFile("images/player/box.png");
    img_["box"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img_["box"].second.setTexture(&img_["box"].first);

    texture.loadFromFile("images/player/gold_box.png");
    img_["gold_box"] = std::pair(Texture(texture), RectangleShape(Vector2f(size, size)));
    img_["gold_box"].second.setTexture(&img_["gold_box"].first);
}

void Player::setLevel(const std::vector<std::vector<int>>& level)
{
    this->level_ = level;

    offset1_ = (Width - level_[0].size() * size) / 2;
    offset2_ = (Height - level_.size() * size) / 2;

    for(size_t i = 0; i < level_.size(); i++)
    {
        for(size_t j = 0; j < level_[0].size(); j++)
        {
            switch(level_[i][j])
            {
                case FIELD::AIM:
                    aims_.emplace_back(std::pair(j * size + offset1_, i * size + offset2_));
                    break;
                case FIELD::BOX:
                    boxes_.emplace_back(std::pair(j * size + offset1_, i * size + offset2_));
                    break;
                case FIELD::PLAYER:
                    x_ = j * size + offset1_;
                    y_ = i * size + offset2_;
                    img_["player"].second.setPosition(x_, y_);
                    break;
            }
        }
    }
}

Player::~Player()
{
    window_ = nullptr;
}

size_t Player::checkPosition(int xPos, int yPos)
{
    return level_[(yPos - offset2_) / size][(xPos - offset1_) / size];
}

size_t Player::checkPosition(const Vector2i& vec)
{
    return level_[(vec.y - offset2_) / size][(vec.x - offset1_) / size];
}

std::pair<int, int>* Player::checkBoxes(int first, int second)
{
    for(const auto& box : boxes_)
    {
        if (box.first == first && (box.second < second && second < box.second + size) 
            || box.second == second && (box.first < first && first < box.first + size))
            return const_cast<std::pair<int, int>*>(&box);
    }
    return nullptr;
}

std::pair<int, int>* Player::checkBoxes(const Vector2i& vec)
{
    for(const auto& box : boxes_)
    {
        if (box.first == vec.x && (box.second < vec.y && vec.y < box.second + size) 
            || box.second == vec.y && (box.first < vec.x && vec.x < box.first + size))
            return const_cast<std::pair<int, int>*>(&box);
    }
    return nullptr;
}

void Player::movement(int pressed_key)
{    
    int dist, destination = 1, *ptr, *coord;
    Vector2i nextPos, behindNextPos;
    std::pair<int, int>* it;

    // player position before and after move
    int prevX = (x_ - offset1_) / size, prevY = (y_ - offset2_) / size;
    int currX, currY;

    // boxes positions before player's move
    std::vector<std::pair<int, int>> prevBoxesPos;
    for(const auto& box : boxes_) prevBoxesPos.emplace_back(
        std::pair((box.first - offset1_) / size, (box.second - offset2_) / size));
    
    switch(pressed_key)
    {
        case Keyboard::W: case Keyboard::Up:
            dist = (y_ - offset2_) % size;
            nextPos = Vector2i(x_, y_ - speed_);
            behindNextPos = Vector2i(x_, y_ - size - speed_);
            ptr = &y_; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->second);
            break;

        case Keyboard::A: case Keyboard::Left:
            dist = (x_ - offset1_) % size;
            nextPos = Vector2i(x_ - speed_, y_);
            behindNextPos = Vector2i(x_ - size - speed_, y_);
            ptr = &x_; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->first);
            break;

        case Keyboard::S: case Keyboard::Down:
            dist = size - (y_ - offset2_) % size;
            nextPos = Vector2i(x_, y_ + size + speed_);
            behindNextPos = Vector2i(x_, y_ + 2 * size + speed_);
            ptr = &y_; it = checkBoxes(nextPos);
            coord = &(it->second);
            break;

        case Keyboard::D: case Keyboard::Right:
            dist = size - (x_ - offset1_) % size;
            nextPos = Vector2i(x_ + size + speed_, y_);
            behindNextPos = Vector2i(x_ + 2 * size + speed_, y_);
            ptr = &x_; it = checkBoxes(nextPos);
            coord = &(it->first);
            break;

        default: return;
    } 

    int playerMoved = *ptr; // this variable keep info if player moved or not
    
    if (checkPosition(nextPos) != 1)
    {
        if (it)
        {
            if (checkPosition(behindNextPos) != 1 && !checkBoxes(behindNextPos))
            {
                (*ptr) += destination * speed_;
                (*coord) += destination * speed_;
            }
            else
            {
                (*ptr) += dist && dist <= speed_ ? destination * dist : 0;
                (*coord) = (*ptr) + destination * size;
            }
        }
        else (*ptr) += destination * speed_;
    }
    else if (size - dist) (*ptr) += destination * dist;

    currX = (x_ - offset1_) / size; currY = (y_ - offset2_) / size;

    if (currX != prevX || currY != prevY)
    {
        playerMoves_.push(std::pair(prevX, prevY));
        for(const auto& el : prevBoxesPos) boxesMoves_.push(el);
    }

    img_["player"].second.setPosition(x_, y_);
}

// align player and boxes by cells
void Player::alignPlayer(int released_key, int param) 
{
    bool flag = false;

    if (param == 1)
    {
        switch(released_key)
        {
            case Keyboard::W: case Keyboard::Up:
                y_ -= size / 2;
                break;
            case Keyboard::A: case Keyboard::Left:
                x_ -= size / 2;
                break;
            case Keyboard::S: case Keyboard::Down:
                if (checkPosition(x_, y_ + 1.5 * size) != 1) 
                {
                    auto it = checkBoxes(x_, y_ + 1.5 * size);
                    if (it)
                    {
                        if (checkPosition(x_, y_ + 2.5 * size) != 1 && 
                            !checkBoxes(x_, y_ + 2.5 * size)) y_ += size / 2;
                    }
                    else y_ += size / 2; 
                }
                break;
            case Keyboard::D: case Keyboard::Right:
                if (checkPosition(x_ + 1.5 * size, y_) != 1) 
                {
                    auto it = checkBoxes(x_ + 1.5 * size, y_);
                    if (it)
                    {
                        if (checkPosition(x_ + 2.5 * size, y_) != 1 && 
                            !checkBoxes(x_ + 2.5 * size, y_)) x_ += size / 2;
                    }
                    else x_ += size / 2;
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
            int dyUp = (y_ - offset2_) % size; // here we know which cell is player closest to
            int dyDown = size - dyUp;

            auto it1 = checkBoxes(x_, y_ - speed_);
            auto it2 = checkBoxes(x_, y_ + size + speed_);

            dyUp < dyDown ? y_ -= dyUp : (y_ += dyDown, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::S || released_key == Keyboard::Down) 
                {
                    playerMoves_.push(
                            std::pair((x_ - offset1_) / size, (y_ - offset2_) / size - 1));
                    for(const auto& box : boxes_) boxesMoves_.push(
                            std::pair((box.first - offset1_) / size, (box.second - offset2_) / size));
                }
                else if ((released_key == Keyboard::W 
                    || released_key == Keyboard::Up) && dyDown != size / 2)
                {
                    playerMoves_.pop();
                    for(int i = 0; i < boxes_.size(); i++) boxesMoves_.pop();
                }
            }

            if (it1) (*it1).second = y_ - size; // here we should check if there is a box above or beneath player. And if there is, we will align it too
            else if (it2) (*it2).second = y_ + size;

            break;
        }
        
        case Keyboard::A: case Keyboard::Left:
        case Keyboard::D: case Keyboard::Right:
        {
            int dxLeft = (x_ - offset1_) % size;
            int dxRight = size - dxLeft;

            auto it1 = checkBoxes(x_ - speed_, y_);
            auto it2 = checkBoxes(x_ + size + speed_, y_);

            dxLeft < dxRight ? x_ -= dxLeft : (x_ += dxRight, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::D || released_key == Keyboard::Right) 
                {
                    playerMoves_.push(
                        std::pair((x_ - offset1_) / size - 1, (y_ - offset2_) / size));
                    for(const auto& box : boxes_) boxesMoves_.push(
                        std::pair((box.first - offset1_) / size, (box.second - offset2_) / size));
                }
                else if ((released_key == Keyboard::A 
                    || released_key == Keyboard::Left) && dxRight != size / 2) 
                {
                    playerMoves_.pop();
                    for(int i = 0; i < boxes_.size(); i++) boxesMoves_.pop();
                }
            }
            

            if (it1) (*it1).first = x_ - size;
            else if (it2) (*it2).first = x_ + size;

            break;
        }

        default: return;
    }

    img_["player"].second.setPosition(x_, y_);
}

std::pair<bool, bool> Player::drawPlayer()
{
    static int prev_goals_counter = 0;
    int goals_counter = 0;

    window_->draw(img_["player"].second);
    for(const auto& box : boxes_)
    {
        if (std::find(aims_.begin(), aims_.end(), box) == aims_.end()) 
        {
            img_["box"].second.setPosition(box.first, box.second);
            window_->draw(img_["box"].second);
        }
        else
        {
            img_["gold_box"].second.setPosition(box.first, box.second);
            window_->draw(img_["gold_box"].second);
            goals_counter++;
        }
    }

    bool result = goals_counter > prev_goals_counter;
    prev_goals_counter = goals_counter;

    // check if all the boxes are in their positions
    return std::pair(goals_counter == aims_.size(), result);
}   

void Player::restartLevel()
{
    aims_.clear();
    boxes_.clear();

    for(size_t i = 0; i < level_.size(); i++)
    {
        for(size_t j = 0; j < level_[0].size(); j++)
        {
            switch(level_[i][j])
            {
                case 3:
                    aims_.emplace_back(std::pair(j * size + offset1_, i * size + offset2_));
                    break;
                case 4:
                    boxes_.emplace_back(std::pair(j * size + offset1_, i * size + offset2_));
                    break;
                case 5:
                    x_ = j * size + offset1_;
                    y_ = i * size + offset2_;
                    break;
            }
        }
    }

    while(!playerMoves_.empty()) playerMoves_.pop();
    while(!boxesMoves_.empty()) boxesMoves_.pop();

    img_["player"].second.setPosition(x_, y_);
}

bool Player::cancelMove()
{
    if (!playerMoves_.empty())
    {
        x_ = playerMoves_.top().first * size + offset1_;
        y_ = playerMoves_.top().second * size + offset2_;

        img_["player"].second.setPosition(x_, y_);
        window_->draw(img_["player"].second);

        for(int i = boxes_.size() - 1; i >= 0; i--)
        {
            boxes_[i].first = boxesMoves_.top().first * size + offset1_;
            boxes_[i].second = boxesMoves_.top().second * size + offset2_;

            img_["box"].second.setPosition(boxes_[i].first, boxes_[i].second);
            window_->draw(img_["box"].second);

            boxesMoves_.pop();
        }

        playerMoves_.pop();
        return true;
    }
    return false;
}
