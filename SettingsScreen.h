#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"

namespace sfSnake
{
class SettingsScreen : public Screen
{
public:
    SettingsScreen();

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    sf::Color getBackgroundColor() const;
    bool isGridEnabled() const;
    sf::Color getGridColor() const;

private:
    void updateText();
    void handleMouseClick(sf::RenderWindow& window);

    sf::Font font_;
    sf::Text instructionsText_;
    sf::Text optionTexts_[8];

    sf::RectangleShape backgroundColorOptions_[3];
    sf::RectangleShape gridEnabledOptions_[2];
    sf::RectangleShape gridColorOptions_[3];

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    int backgroundColorIndex_;
    bool gridEnabled_;
    int gridColorIndex_;

    static const std::vector<sf::Color> Colors;
    static const std::vector<sf::Color> gridColors;
    static const std::vector<std::string> ColorNames;
};
}

#endif
