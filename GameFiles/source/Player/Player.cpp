#include "Player.hpp"

Player::Player(std::shared_ptr<RenderWindow> window, int speed) noexcept
    : window_(window)
{
    this->speed_ = speed > gl::size ? gl::size : speed;

    img_.emplace("player", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/player").get());

    img_.emplace("box", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/box").get());

    img_.emplace("gold_box", RectangleShape(Vector2f(gl::size, gl::size))).first->second.setTexture(
        TextureManager::getManager().getTexture("textures/player/gold_box").get());
}

void Player::setLevel(const std::vector<std::vector<int>>& level) noexcept
{
    level_ = level;
    boxes_.clear(); aims_.clear();
    while(!playerMoves_.empty()) playerMoves_.pop();
    while(!boxesMoves_.empty()) boxesMoves_.pop();

    offset1_ = (gl::Width - level_[0].size() * gl::size) / 2;
    offset2_ = (gl::Height - level_.size() * gl::size) / 2;

    for(size_t i = 0; i < level_.size(); i++)
    {
        for(size_t j = 0; j < level_[0].size(); j++)
        {
            switch(level_[i][j])
            {
                case FIELD::AIM:
                    aims_.emplace_back(std::pair(j * gl::size + offset1_, i * gl::size + offset2_));
                    break;
                case FIELD::BOX:
                    boxes_.emplace_back(std::pair(j * gl::size + offset1_, i * gl::size + offset2_));
                    break;
                case FIELD::PLAYER:
                    x_ = j * gl::size + offset1_;
                    y_ = i * gl::size + offset2_;
                    img_["player"].setPosition(x_, y_);
                    break;
            }
        }
    }
}

void Player::movement(int pressed_key) noexcept
{    
    int dist, destination = 1, *ptr, *coord;
    Vector2i nextPos, behindNextPos;
    std::pair<int, int>* it;

    // player position before and after move
    int prevX = (x_ - offset1_) / gl::size, prevY = (y_ - offset2_) / gl::size;
    int currX, currY;

    // boxes positions before player's move
    std::vector<std::pair<int, int>> prevBoxesPos;
    for(const auto& box : boxes_) prevBoxesPos.emplace_back(
        std::pair((box.first - offset1_) / gl::size, (box.second - offset2_) / gl::size));
    
    switch(pressed_key)
    {
        case Keyboard::W: case Keyboard::Up:
            dist = (y_ - offset2_) % gl::size;
            nextPos = Vector2i(x_, y_ - speed_);
            behindNextPos = Vector2i(x_, y_ - gl::size - speed_);
            ptr = &y_; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->second);
            break;

        case Keyboard::A: case Keyboard::Left:
            dist = (x_ - offset1_) % gl::size;
            nextPos = Vector2i(x_ - speed_, y_);
            behindNextPos = Vector2i(x_ - gl::size - speed_, y_);
            ptr = &x_; destination = -1;
            it = checkBoxes(nextPos);
            coord = &(it->first);
            break;

        case Keyboard::S: case Keyboard::Down:
            dist = gl::size - (y_ - offset2_) % gl::size;
            nextPos = Vector2i(x_, y_ + gl::size + speed_);
            behindNextPos = Vector2i(x_, y_ + 2 * gl::size + speed_);
            ptr = &y_; it = checkBoxes(nextPos);
            coord = &(it->second);
            break;

        case Keyboard::D: case Keyboard::Right:
            dist = gl::size - (x_ - offset1_) % gl::size;
            nextPos = Vector2i(x_ + gl::size + speed_, y_);
            behindNextPos = Vector2i(x_ + 2 * gl::size + speed_, y_);
            ptr = &x_; it = checkBoxes(nextPos);
            coord = &(it->first);
            break;

        default: return;
    } 

    // this variable keep info if player moved or not
    int playerMoved = *ptr;
    
    if (checkPosition(nextPos) != FIELD::WALL)
    {
        if (it)
        {
            if (checkPosition(behindNextPos) != FIELD::WALL && 
                checkBoxes(behindNextPos) == nullptr)
            {
                (*ptr) += destination * speed_;
                (*coord) += destination * speed_;
            }
            else
            {
                (*ptr) += dist && dist <= speed_ ? destination * dist : 0;
                (*coord) = (*ptr) + destination * gl::size;
            }
        }
        else (*ptr) += destination * speed_;
    }
    else if (gl::size - dist) (*ptr) += destination * dist;

    currX = (x_ - offset1_) / gl::size; currY = (y_ - offset2_) / gl::size;

    if (currX != prevX || currY != prevY)
    {
        playerMoves_.push(std::pair(prevX, prevY));
        for(const auto& el : prevBoxesPos) boxesMoves_.push(el);
    }

    img_["player"].setPosition(x_, y_);
}

void Player::alignPlayer(int released_key, int param) noexcept 
{
    bool flag = false;
    const int next_ceil = 1.5 * gl::size;
    const int cell_through_next = 2.5 * gl::size;

    if (param == 1)
    {
        switch(released_key)
        {
            case Keyboard::W: case Keyboard::Up:
                y_ -= gl::size / 2;
                break;
            case Keyboard::A: case Keyboard::Left:
                x_ -= gl::size / 2;
                break;
            case Keyboard::S: case Keyboard::Down:
                if (checkPosition(x_, y_ + next_ceil) != FIELD::WALL) 
                {
                    auto it = checkBoxes(x_, y_ + next_ceil);
                    if (it)
                    {
                        if (checkPosition(x_, y_ + cell_through_next) != FIELD::WALL && 
                            !checkBoxes(x_, y_ + cell_through_next)) y_ += gl::size / 2;
                    }
                    else y_ += gl::size / 2; 
                }
                break;
            case Keyboard::D: case Keyboard::Right:
                if (checkPosition(x_ + next_ceil, y_) != FIELD::WALL) 
                {
                    auto it = checkBoxes(x_ + next_ceil, y_);
                    if (it)
                    {
                        if (checkPosition(x_ + cell_through_next, y_) != FIELD::WALL && 
                            !checkBoxes(x_ + cell_through_next, y_)) x_ += gl::size / 2;
                    }
                    else x_ += gl::size / 2;
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
            // here we know which cell is player closest to
            int dyUp = (y_ - offset2_) % gl::size;
            int dyDown = gl::size - dyUp;

            auto it1 = checkBoxes(x_, y_ - speed_);
            auto it2 = checkBoxes(x_, y_ + gl::size + speed_);

            dyUp < dyDown ? y_ -= dyUp : (y_ += dyDown, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::S || released_key == Keyboard::Down) 
                {
                    playerMoves_.push(
                        std::pair((x_ - offset1_) / gl::size, (y_ - offset2_) / gl::size - 1));
                    for(const auto& box : boxes_) boxesMoves_.push(
                        std::pair((box.first - offset1_) / gl::size, (box.second - offset2_) / gl::size));
                }
                else if ((released_key == Keyboard::W 
                    || released_key == Keyboard::Up) && dyDown != gl::size / 2)
                {
                    playerMoves_.pop();
                    for(int i = 0; i < boxes_.size(); i++) boxesMoves_.pop();
                }
            }

            // Here we should check if there is a box above or beneath player. 
            // And if there is, we will align it too
            if (it1) (*it1).second = y_ - gl::size; 
            else if (it2) (*it2).second = y_ + gl::size;

            break;
        }
        
        case Keyboard::A: case Keyboard::Left:
        case Keyboard::D: case Keyboard::Right:
        {
            int dxLeft = (x_ - offset1_) % gl::size;
            int dxRight = gl::size - dxLeft;

            auto it1 = checkBoxes(x_ - speed_, y_);
            auto it2 = checkBoxes(x_ + gl::size + speed_, y_);

            dxLeft < dxRight ? x_ -= dxLeft : (x_ += dxRight, flag = true);

            if (flag)
            {
                if (released_key == Keyboard::D || released_key == Keyboard::Right) 
                {
                    playerMoves_.push(
                        std::pair((x_ - offset1_) / gl::size - 1, (y_ - offset2_) / gl::size));
                    for(const auto& box : boxes_) boxesMoves_.push(
                        std::pair((box.first - offset1_) / gl::size, (box.second - offset2_) / gl::size));
                }
                else if ((released_key == Keyboard::A 
                    || released_key == Keyboard::Left) && dxRight != gl::size / 2) 
                {
                    playerMoves_.pop();
                    for(int i = 0; i < boxes_.size(); i++) boxesMoves_.pop();
                }
            }
            
            if (it1) (*it1).first = x_ - gl::size;
            else if (it2) (*it2).first = x_ + gl::size;

            break;
        }

        default: return;
    }

    img_["player"].setPosition(x_, y_);
}

std::vector<COORDINATE> Player::getBoxes() const noexcept { return boxes_; }

std::pair<bool, bool> Player::drawPlayer() noexcept
{
    static int prev_goals_counter = 0;
    int goals_counter = 0;

    window_->draw(img_["player"]);
    for(const auto& box : boxes_)
    {
        if (std::find(aims_.begin(), aims_.end(), box) == aims_.end()) 
        {
            img_["box"].setPosition(box.first, box.second);
            window_->draw(img_["box"]);
        }
        else
        {
            img_["gold_box"].setPosition(box.first, box.second);
            window_->draw(img_["gold_box"]);
            goals_counter++;
        }
    }

    window_->display();

    bool result = goals_counter > prev_goals_counter;
    prev_goals_counter = goals_counter;

    // check if all the boxes are in their positions
    return { goals_counter == aims_.size(), result };
}   

void Player::restartLevel() noexcept
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
                    aims_.emplace_back(std::pair(j * gl::size + offset1_, 
                        i * gl::size + offset2_));
                    break;
                case 4:
                    boxes_.emplace_back(std::pair(j * gl::size + offset1_, 
                        i * gl::size + offset2_));
                    break;
                case 5:
                    x_ = j * gl::size + offset1_;
                    y_ = i * gl::size + offset2_;
                    img_["player"].setPosition(x_, y_);
                    break;
            }
        }
    }

    while(!playerMoves_.empty()) playerMoves_.pop();
    while(!boxesMoves_.empty()) boxesMoves_.pop();
}

bool Player::cancelMove() noexcept
{
    if (!playerMoves_.empty())
    {
        x_ = playerMoves_.top().first * gl::size + offset1_;
        y_ = playerMoves_.top().second * gl::size + offset2_;

        img_["player"].setPosition(x_, y_);
        window_->draw(img_["player"]);

        for(int i = boxes_.size() - 1; i >= 0; i--)
        {
            boxes_[i].first = boxesMoves_.top().first * gl::size + offset1_;
            boxes_[i].second = boxesMoves_.top().second * gl::size + offset2_;

            img_["box"].setPosition(boxes_[i].first, boxes_[i].second);
            window_->draw(img_["box"]);

            boxesMoves_.pop();
        }

        playerMoves_.pop();
        return true;
    }
    return false;
}

size_t Player::checkPosition(int xPos, int yPos) noexcept
{
    return level_[(yPos - offset2_) / gl::size][(xPos - offset1_) / gl::size];
}

size_t Player::checkPosition(const Vector2i& vec) noexcept
{
    return level_[(vec.y - offset2_) / gl::size][(vec.x - offset1_) / gl::size];
}

std::pair<int, int>* Player::checkBoxes(int first, int second) noexcept
{
    for(auto& box : boxes_)
    {
        if (box.first == first && (box.second < second && second < box.second + gl::size) 
            || box.second == second && (box.first < first && first < box.first + gl::size))
            return &box;
    }
    return nullptr;
}

std::pair<int, int>* Player::checkBoxes(const Vector2i& vec) noexcept
{
    for(auto& box : boxes_)
    {
        if (box.first == vec.x && (box.second < vec.y && vec.y < box.second + gl::size) 
            || box.second == vec.y && (box.first < vec.x && vec.x < box.first + gl::size))
            return &box;
    }
    return nullptr;
}
