#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>
#include <random>
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;
const sf::Time Snake::SkillDuration = sf::seconds(5);
const int Snake::SkillScoreMultiplier = 16;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false), firstUpdate_(true), skillActive_(false), scoreSinceLastSkill_(0), directionVector_(sf::Vector2f(0.f, -1.f))
{
    initNodes();
    pickupBuffer_.loadFromFile("../../Sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("../../Sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes()
{
    head_.setPosition(sf::Vector2f(Game::Width / 2, Game::Height / 2));
    for (auto i = 0; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width / 2, Game::Height / 2 + (2 * SnakeNode::Radius * (i + 1)))));
        nodes_[i].move(0.f, 0.f, 90.f);
    }
}

bool canUpdateDirection(const sf::Vector2f& currentDirection, const sf::Vector2f& newDirection)
{
    if (currentDirection == sf::Vector2f(0.f, 0.f) || newDirection == sf::Vector2f(0.f, 0.f))
        return true;

    float currentAngle = std::atan2(currentDirection.y, currentDirection.x) * 180.f / 3.14159265f;
    float newAngle = std::atan2(newDirection.y, newDirection.x) * 180.f / 3.14159265f;
    float angleDifference = std::abs(newAngle - currentAngle);

    if (angleDifference > 180.f)
        angleDifference = 360.f - angleDifference;

    return angleDifference <= 120.f || angleDifference >= 240.f;
}

void Snake::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sf::Vector2f newDirection(0.f, -1.f);
        if (canUpdateDirection(directionVector_, newDirection))
        {
            direction_ = Direction::Up;
            directionVector_ = newDirection;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sf::Vector2f newDirection(0.f, 1.f);
        if (canUpdateDirection(directionVector_, newDirection))
        {
            direction_ = Direction::Down;
            directionVector_ = newDirection;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sf::Vector2f newDirection(-1.f, 0.f);
        if (canUpdateDirection(directionVector_, newDirection))
        {
            direction_ = Direction::Left;
            directionVector_ = newDirection;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sf::Vector2f newDirection(1.f, 0.f);
        if (canUpdateDirection(directionVector_, newDirection))
        {
            direction_ = Direction::Right;
            directionVector_ = newDirection;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canUseSkill())
    {
        std::cout << "Skill activated" << std::endl;
        skillActive_ = true;
        skillClock_.restart();
        scoreSinceLastSkill_ = 0; // 重置累计得分
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f snakePosition = head_.getPosition();
        sf::Vector2f newDirection(mousePosition.x - snakePosition.x, mousePosition.y - snakePosition.y);

        float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
        newDirection.x /= length;
        newDirection.y /= length;

        if (canUpdateDirection(directionVector_, newDirection))
        {
            directionVector_ = newDirection;
            direction_ = Direction::None;
        }
    }
}

void Snake::update(sf::Time delta)
{
    move();
    checkEdgeCollisions();

    if (!skillActive_) // 技能激活时无敌，不检查自身碰撞
    {
        checkSelfCollisions();
    }

    if (skillActive_ && skillClock_.getElapsedTime() >= SkillDuration)
    {
        skillActive_ = false;
    }
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
    decltype(fruits.begin()) toRemove = fruits.end();
    int growLength = 0;

    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if (it->getBounds().intersects(head_.getBounds()))
        {
            toRemove = it;
            switch (it->getType())
            {
            case FruitType::Black:
            case FruitType::Brown:
                growLength = 0;
                break;
            case FruitType::Red:
                growLength = 3;
                break;
            case FruitType::Blue:
                growLength = 2;
                break;
            case FruitType::Green:
                growLength = 1;
                break;
            }
        }
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        grow(growLength);
        relocateFruit(*toRemove);

        // 更新累计得分
        scoreSinceLastSkill_ += growLength;
    }
}

void Snake::grow(int length)
{
    if (length <= 0) return;

    SnakeNode& tailNode = nodes_.back();
    sf::Vector2f tailPosition = tailNode.getPosition();

    for (auto i = 0; i < length; ++i)
    {
        nodes_.push_back(SnakeNode(tailPosition));
    }
}

void Snake::relocateFruit(Fruit& fruit)
{
    fruit.setPosition(generateLocation());
}

const sf::Vector2f Snake::generateLocation()
{
    static std::default_random_engine engine(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(0, sfSnake::Game::Width - 2 * SnakeNode::Radius);
    static std::uniform_int_distribution<int> yDistribution(0, sfSnake::Game::Height - 2 * SnakeNode::Radius);
    return sf::Vector2f(xDistribution(engine), yDistribution(engine));
}

unsigned Snake::getSize() const
{
    return nodes_.size();
}

bool Snake::hitSelf() const
{
    return hitSelf_;
}

void Snake::checkSelfCollisions()
{
    if (firstUpdate_)
    {
        firstUpdate_ = false;
        return;
    }
    for (auto i = 3; i < nodes_.size(); ++i)
    {
        if (head_.getBounds().intersects(nodes_[i].getBounds()))
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
            break;
        }
    }
}

void Snake::checkEdgeCollisions()
{
    sf::Vector2f headPosition = head_.getPosition();
    if (headPosition.x < 0)
        head_.setPosition(Game::Width, headPosition.y);
    else if (headPosition.x >= Game::Width)
        head_.setPosition(0, headPosition.y);
    else if (headPosition.y < 0)
        head_.setPosition(headPosition.x, Game::Height);
    else if (headPosition.y >= Game::Height)
        head_.setPosition(headPosition.x, 0);
}

void Snake::move()
{
    float moveDistance = 2*SnakeNode::Radius; // 每次移动的距离

    if (skillActive_)
    {
        // 技能激活时，蛇分两步移动
        for (auto step = 0; step < 2; ++step)
        {
            float angle;
            sf::Vector2f oldHeadPosition = head_.getPosition();

            if (direction_ != Direction::None)
            {
                switch (direction_)
                {
                case Direction::Up:
                    angle = 0.f;
                    head_.move(0, -moveDistance, angle);
                    break;
                case Direction::Down:
                    angle = 180.f;
                    head_.move(0, moveDistance, angle);
                    break;
                case Direction::Left:
                    angle = -90.f;
                    head_.move(-moveDistance, 0, angle);
                    break;
                case Direction::Right:
                    angle = 90.f;
                    head_.move(moveDistance, 0, angle);
                    break;
                }
            }
            else
            {
                head_.move(directionVector_.x * moveDistance, directionVector_.y * moveDistance, std::atan2(directionVector_.y, directionVector_.x) * 180 / 3.14159265f);
                angle = std::atan2(directionVector_.y, directionVector_.x) * 180 / 3.14159265f;
            }

            std::vector<sf::Vector2f> newPositions(nodes_.size());
            std::vector<float> newAngles(nodes_.size());

            newPositions[0] = oldHeadPosition;
            newAngles[0] = angle;
            if(direction_ != Direction::None)
                newAngles[0] += 90.f;

            for (size_t i = 1; i < nodes_.size(); ++i)
            {
                newPositions[i] = nodes_[i - 1].getPosition();
                newAngles[i] = nodes_[i - 1].getRotation();
            }

            for (size_t i = 0; i < nodes_.size(); ++i)
            {
                nodes_[i].setPosition(newPositions[i]);
                nodes_[i].move(0, 0, newAngles[i]);
            }

        }
    }
    else
    {
        // 正常情况下的移动
        float angle;
        sf::Vector2f oldHeadPosition = head_.getPosition();

        if (direction_ != Direction::None)
        {
            switch (direction_)
            {
            case Direction::Up:
                angle = 0.f;
                head_.move(0, -2 * SnakeNode::Radius, angle);
                break;
            case Direction::Down:
                angle = 180.f;
                head_.move(0, 2 * SnakeNode::Radius, angle);
                break;
            case Direction::Left:
                angle = -90.f;
                head_.move(-2 * SnakeNode::Radius, 0, angle);
                break;
            case Direction::Right:
                angle = 90.f;
                head_.move(2 * SnakeNode::Radius, 0, angle);
                break;
            }
        }
        else
        {
            head_.move(directionVector_.x * 2 * SnakeNode::Radius, directionVector_.y * 2 * SnakeNode::Radius, std::atan2(directionVector_.y, directionVector_.x) * 180 / 3.14159265f);
            angle = std::atan2(directionVector_.y, directionVector_.x) * 180 / 3.14159265f;
        }

        float previousNodeAngle = angle;

        for (auto i = nodes_.size() - 1; i > 0; --i)
        {
            previousNodeAngle = nodes_[i - 1].getRotation();
            nodes_[i].setPosition(nodes_[i - 1].getPosition());
            nodes_[i].move(0, 0, previousNodeAngle);
        }

        if (!nodes_.empty())
        {
            nodes_[0].setPosition(oldHeadPosition);
            if (direction_ == Direction::None)
                nodes_[0].move(0, 0, angle);
            else
                nodes_[0].move(0, 0, angle + 90.f);
        }
    }
}



bool Snake::canUseSkill() const
{
    return scoreSinceLastSkill_ >= SkillScoreMultiplier;
}

void Snake::render(sf::RenderWindow& window)
{
    head_.render(window);
    for (auto node : nodes_)
        node.render(window);
}
