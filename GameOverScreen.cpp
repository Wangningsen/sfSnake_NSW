// #include <SFML/Graphics.hpp>

// #include <iostream>
// #include <memory>

// #include "Game.h"
// #include "GameScreen.h"
// #include "GameOverScreen.h"

// using namespace sfSnake;

// GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
// {
// 	font_.loadFromFile("../../Fonts/game_over.ttf");
// 	text_.setFont(font_);
// 	text_.setString("Your score: " + std::to_string(score) + "!"
// 		"\n\nPress [SPACE] to retry"
// 		"\n\nPress [ESC] to quit");
// 	text_.setFillColor(sf::Color::Red);

// 	sf::FloatRect textBounds = text_.getLocalBounds();
// 	text_.setOrigin(textBounds.left + textBounds.width / 2,
// 		textBounds.top + textBounds.height / 2);
// 	text_.setPosition(Game::Width / 2, Game::Height / 2);
// }

// GameOverScreen::GameOverScreen(std::size_t score, sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor)
//     : score_(score), backgroundColor_(backgroundColor), gridEnabled_(gridEnabled), gridColor_(gridColor)
// {
//     font_.loadFromFile("../../Fonts/game_over.ttf");
//     text_.setFont(font_);
//     text_.setString("Your score: " + std::to_string(score) + "!"
//         "\n\nPress [SPACE] to retry"
//         "\n\nPress [ESC] to quit");
//     text_.setFillColor(sf::Color::Red);

//     sf::FloatRect textBounds = text_.getLocalBounds();
//     text_.setOrigin(textBounds.left + textBounds.width / 2,
//         textBounds.top + textBounds.height / 2);
//     text_.setPosition(Game::Width / 2, Game::Height / 2);
// }

// void GameOverScreen::handleInput(sf::RenderWindow& window)
// {
// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
// 		Game::Screen = std::make_shared<GameScreen>(backgroundColor_, gridEnabled_, gridColor_);
// 	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
// 		window.close();
// }

// void GameOverScreen::update(sf::Time delta)
// {

// }

// void GameOverScreen::render(sf::RenderWindow& window)
// {
// 	window.draw(text_);
// }

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
    font_.loadFromFile("../../Fonts/game_over.ttf");
    backgroundTexture_.loadFromFile("../../img/gameoverBackground.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    text_.setFont(font_);
    text_.setString("Your score: " + std::to_string(score) + "!"
        "\n\nPress [SPACE] to retry"
        "\n\nPress [ESC] to quit");
    text_.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height - 400); // 移动到窗口底部
}

GameOverScreen::GameOverScreen(std::size_t score, sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor)
    : score_(score), backgroundColor_(backgroundColor), gridEnabled_(gridEnabled), gridColor_(gridColor)
{
    font_.loadFromFile("../../Fonts/game_over.ttf");
    backgroundTexture_.loadFromFile("../../img/gameoverBackground.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    text_.setFont(font_);
    text_.setString("Your score: " + std::to_string(score) + "!"
        "\n\nPress [SPACE] to retry"
        "\n\nPress [ESC] to quit");
    text_.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height - 200); // 移动到窗口底部
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<GameScreen>(backgroundColor_, gridEnabled_, gridColor_);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void GameOverScreen::update(sf::Time delta)
{
}

void GameOverScreen::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite_);
    window.draw(text_);
    // window.display();
}
