#include <SFML/Graphics.hpp>
#include <iostream>
#include "SucceedScreen.h"
#include "Game.h"
#include "MenuScreen.h"

using namespace sfSnake;

SucceedScreen::SucceedScreen(std::size_t score, sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor)
    : score_(score), backgroundColor_(backgroundColor), gridEnabled_(gridEnabled), gridColor_(gridColor)
{
    font_.loadFromFile("../../Fonts/game_over.ttf");

    succeedText_.setFont(font_);
    succeedText_.setString("Congratulations! You Win!\nScore: " + std::to_string(score_));
    succeedText_.setCharacterSize(48);
    succeedText_.setFillColor(sf::Color::Green);
    succeedText_.setPosition(Game::Width / 2 - succeedText_.getGlobalBounds().width / 2, Game::Height / 2 - 400);

    instructionsText_.setFont(font_);
    instructionsText_.setString("Press [SPACE] to return to menu\nPress [ESC] to exit");
    instructionsText_.setCharacterSize(24);
    instructionsText_.setFillColor(sf::Color::White);
    instructionsText_.setPosition(Game::Width / 2 - instructionsText_.getGlobalBounds().width / 2, Game::Height / 2 + 400);

     if (!backgroundTexture_.loadFromFile("../../img/succeedBackground.png"))
    {
        // Handle loading error
    }
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale(
        float(Game::Width) / backgroundTexture_.getSize().x,
        float(Game::Height) / backgroundTexture_.getSize().y);
    succbffer.loadFromFile("../../Sounds/mamba_out.wav");
    succsound.setBuffer(succbffer);
    succsound.setVolume(100);
    succsound.play();
}

void SucceedScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game::Screen = std::make_shared<MenuScreen>();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }
}

void SucceedScreen::update(sf::Time delta)
{
    // No game state update needed for this screen
}

void SucceedScreen::render(sf::RenderWindow& window)
{
    window.clear(backgroundColor_);

    // if (gridEnabled_)
    // {
    //     sf::RectangleShape line;
    //     line.setFillColor(gridColor_);

    //     // Draw vertical lines
    //     for (int x = 0; x < Game::Width; x += 20)
    //     {
    //         line.setSize(sf::Vector2f(1, Game::Height));
    //         line.setPosition(x, 0);
    //         window.draw(line);
    //     }

    //     // Draw horizontal lines
    //     for (int y = 0; y < Game::Height; y += 20)
    //     {
    //         line.setSize(sf::Vector2f(Game::Width, 1));
    //         line.setPosition(0, y);
    //         window.draw(line);
    //     }
    // }

    window.draw(backgroundSprite_);
    window.draw(succeedText_);
    window.draw(instructionsText_);
   
    // window.display();
}
