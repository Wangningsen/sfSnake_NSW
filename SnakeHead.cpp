#include "SnakeHead.h"
#include<iostream>

using namespace sfSnake;

const float SnakeHead::Radius = 10.f;

SnakeHead::SnakeHead(sf::Vector2f position)
: position_(position)
{
    if (!texture_.loadFromFile("../../img/newnewhead.png"))
    {
        std::cerr << "Failed to load image \"Texture.png\". Reason: Unable to open file" << std::endl;
    }
    else
    {
        std::cout << "Texture loaded successfully. Size: " 
                  << texture_.getSize().x << "x" << texture_.getSize().y << std::endl;
    }
    
    headNode_.setPosition(position_);
    headNode_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2); 
}

void SnakeHead::setPosition(sf::Vector2f position)
{
    position_ = position;
    headNode_.setPosition(position_);
}

void SnakeHead::setPosition(float x, float y)
{
    position_.x = x;
    position_.y = y;
    headNode_.setPosition(position_);
}

void SnakeHead::move(float xOffset, float yOffset, float rotationAngle)
{
    position_.x += xOffset;
    position_.y += yOffset;
    headNode_.setPosition(position_);
    headNode_.setRotation(rotationAngle); // 设置旋转角度
}

sf::Vector2f SnakeHead::getPosition() const
{
    return position_;
}

sf::FloatRect SnakeHead::getBounds() const
{
    return headNode_.getGlobalBounds();
}

void SnakeHead::render(sf::RenderWindow& window)
{
    headNode_.setTexture(texture_);
    float scale = (2.0f * SnakeHead::Radius) / texture_.getSize().x; //just for newhead
    headNode_.setScale(scale, scale);
    window.draw(headNode_);
}
