#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

enum class FruitType
{
    Black,
    Brown,
    Red,
    Blue,
    Green
};

class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), FruitType type = FruitType::Red);

	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	void setPosition(sf::Vector2f position);
	FruitType getType() const;

private:
	sf::CircleShape shape_;
	FruitType type_;

	static const float Radius;
};
}

#endif