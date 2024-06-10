#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score);
	GameOverScreen(std::size_t score, sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text text_;
	sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

	unsigned score_;

	sf::Color backgroundColor_;
    bool gridEnabled_;
    sf::Color gridColor_;
};
}

#endif