#include <SFML/Graphics.hpp>
#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
    font_.loadFromFile("../../Fonts/game_over.ttf");
    backgroundTexture_.loadFromFile("../../img/newBackground.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    text_.setFont(font_);
    text_.setString(
        "\n\n\n\n\n\n\n\n\nPress [SPACE] to go to settings"
        "\n\nPress [ESC] to quit");

    // snakeText_.setFont(font_);
    // snakeText_.setString("Snake!");
    // snakeText_.setFillColor(sf::Color::Green);
    // snakeText_.setCharacterSize(64);
    // snakeText_.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2);
    // text_.setPosition(Game::Width / 2, Game::Height / 2);
    text_.setPosition(Game::Width / 2, Game::Height/2 + 240);

    // sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
    // snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
    //     snakeTextBounds.top + snakeTextBounds.height / 2);
    // snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<SettingsScreen>();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void MenuScreen::update(sf::Time delta)
{
}

void MenuScreen::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite_);
    window.draw(text_);
    window.draw(snakeText_);
    // window.display();
}
