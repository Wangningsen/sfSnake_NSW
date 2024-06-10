#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, FruitType type): type_(type)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	// shape_.setFillColor(sf::Color::Red);
	switch (type_)
    {
    case FruitType::Black:
        shape_.setFillColor(sf::Color::Black);
		shape_.setOutlineColor(sf::Color::White);
		shape_.setOutlineThickness(-1.f);
        break;
    case FruitType::Brown:
        shape_.setFillColor(sf::Color(139, 69, 19)); // 棕色
        break;
    case FruitType::Red:
        shape_.setFillColor(sf::Color::Red);
        break;
    case FruitType::Blue:
        shape_.setFillColor(sf::Color::Blue);
        break;
    case FruitType::Green:
        shape_.setFillColor(sf::Color::Green);
        break;
    }
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

void Fruit::setPosition(sf::Vector2f position)
{
    shape_.setPosition(position);
}

FruitType Fruit::getType() const
{
    return type_;
}