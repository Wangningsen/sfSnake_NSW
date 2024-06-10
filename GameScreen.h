#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();
	GameScreen(sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor);
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	// void generateFruit();
	void initFruit(const unsigned short &fruitNum);
	const sf::Vector2f generateLocation();
private:
	Snake snake_;
	std::vector<Fruit> fruit_;

	sf::Color backgroundColor_;
    bool gridEnabled_;
    sf::Color gridColor_;
	bool canUseSkill_;

	sf::Font font_;
	sf::Text scoreText_;
	sf::Text skillText_;  // 新增的提示文本

	
};
}

#endif