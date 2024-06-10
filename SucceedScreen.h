#ifndef SUCCEED_SCREEN_H
#define SUCCEED_SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"

namespace sfSnake
{
class SucceedScreen : public Screen
{
public:
    SucceedScreen(std::size_t score, sf::Color backgroundColor, bool gridEnabled, sf::Color gridColor);
    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    std::size_t score_;
    sf::Color backgroundColor_;
    bool gridEnabled_;
    sf::Color gridColor_;

    sf::Font font_;
    sf::Text succeedText_;
    sf::Text instructionsText_;
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    sf::SoundBuffer succbffer;
    sf::Sound succsound;
};
}

#endif
