#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

// const float SnakeNode::Width = 10.f;
// const float SnakeNode::Height = 10.f;
const float SnakeNode::Radius = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Green);
	shape_.setRadius(SnakeNode::Radius);
	shape_.setOrigin(SnakeNode::Radius, SnakeNode::Radius); 

    // 初始化矩形花纹
    stripe_.setSize(sf::Vector2f(Radius / 2 + 4, 2 * Radius - 4)); // 设置矩形的宽度为圆的半径，高度为圆的直径
	stripe_.setFillColor(sf::Color::Black);
	stripe_.setOrigin((Radius / 2) / 2, (2 * Radius - 4) / 2); // 设置矩形的中心为原点
	stripe_.setPosition(position_);
	stripe_.setRotation(90.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
	stripe_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
	stripe_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset, float rotationAngle)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
	stripe_.setPosition(position_);
	stripe_.setRotation(rotationAngle);

	// stripe_.setRotation(rotationAngle+90.f);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

const float SnakeNode::getRotation() const
{
    return stripe_.getRotation();
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
	window.draw(stripe_);
}