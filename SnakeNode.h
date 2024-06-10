#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset, float rotationAngle);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
	const float getRotation() const;

	// static const float Width;
	// static const float Height;
	static const float Radius;

private:
	sf::CircleShape shape_;
	sf::RectangleShape stripe_;
	sf::Vector2f position_;
};
}

#endif