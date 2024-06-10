#include <SFML/Graphics.hpp>
#include <random>
#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "SucceedScreen.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_(), canUseSkill_(false)
{

}

GameScreen::GameScreen(sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor)
    : backgroundColor_(backgroundColor), gridEnabled_(gridEnabled), gridColor_(gridColor), snake_(), canUseSkill_(false)
{
    font_.loadFromFile("../../Fonts/game_over.ttf");
    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(24);
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setPosition(10, 10);

    skillText_.setFont(font_);
    skillText_.setCharacterSize(24);
    skillText_.setFillColor(sf::Color::Blue);
    skillText_.setPosition(10, 40);
    skillText_.setString("Press [SPACE] to activate invincibility skill!");

    
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
    snake_.handleInput(window);
    canUseSkill_ = snake_.canUseSkill();
}

void GameScreen::update(sf::Time delta)
{
    if(fruit_.size() == 0)
        initFruit(12);

    snake_.update(delta);
    snake_.checkFruitCollisions(fruit_);

    if (snake_.hitSelf())
        Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize(), backgroundColor_, gridEnabled_, gridColor_);

    scoreText_.setString("Score: " + std::to_string(snake_.getSize()));

    if (snake_.getSize() >= 64)
    {   
        Game::Screen = std::make_shared<SucceedScreen>(snake_.getSize(), backgroundColor_, gridEnabled_, gridColor_);
        return;
    }

}

void GameScreen::render(sf::RenderWindow& window)
{
    window.clear(backgroundColor_);

    if (gridEnabled_)
    {
        sf::RectangleShape line;
        line.setFillColor(gridColor_);

        // Draw vertical lines
        for (int x = 0; x < Game::Width; x += SnakeNode::Radius * 2)
        {
            line.setSize(sf::Vector2f(1, Game::Height));
            line.setPosition(x, 0);
            window.draw(line);
        }

        // Draw horizontal lines
        for (int y = 0; y < Game::Height; y += SnakeNode::Radius * 2)
        {
            line.setSize(sf::Vector2f(Game::Width, 1));
            line.setPosition(0, y);
            window.draw(line);
        }
    }

    snake_.render(window);

    for (auto& fruit : fruit_)
        fruit.render(window);

    window.draw(scoreText_);
    // window.display();
    if (canUseSkill_)
    {
        window.draw(skillText_);
    }
}


void GameScreen::initFruit(const unsigned short &fruitNum)
{
    fruit_.reserve(fruitNum);
    while (fruit_.size() < int(fruitNum * 0.25))
    {
        fruit_.push_back(Fruit(generateLocation(), FruitType::Black));
        fruit_.push_back(Fruit(generateLocation(), FruitType::Brown));
    }
    while (fruit_.size() < fruitNum)
    {
        fruit_.push_back(Fruit(generateLocation(), FruitType::Red));
        fruit_.push_back(Fruit(generateLocation(), FruitType::Blue));
        fruit_.push_back(Fruit(generateLocation(), FruitType::Green));
    }
}

const sf::Vector2f GameScreen::generateLocation()
{
    static std::default_random_engine engine(static_cast<unsigned int>(time(NULL)));
    static std::uniform_int_distribution<int> xDistribution(0, Game::Width - 2 * SnakeNode::Radius);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - 2 * SnakeNode::Radius);
    return sf::Vector2f(xDistribution(engine), yDistribution(engine));
}
