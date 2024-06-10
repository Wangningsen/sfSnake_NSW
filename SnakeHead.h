#ifndef SNAKE_HEAD_H
#define SNAKE_HEAD_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeHead
{
public:
    SnakeHead(sf::Vector2f position = sf::Vector2f(0.f, 0.f));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset, float rotationAngle);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

    static const float Radius;

private:
    sf::Sprite headNode_;
    sf::Texture texture_;
    sf::Vector2f position_;
};


}

#endif