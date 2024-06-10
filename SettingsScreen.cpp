#include <SFML/Graphics.hpp>
#include "SettingsScreen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const std::vector<sf::Color> SettingsScreen::gridColors = { sf::Color(93, 94, 94), sf::Color(70, 71, 71), sf::Color(139, 69, 19) };
const std::vector<sf::Color> SettingsScreen::Colors = { sf::Color(210, 212, 212), sf::Color::Black, sf::Color(139, 69, 19) }; // White, Black, Brown
const std::vector<std::string> SettingsScreen::ColorNames = { "WHITE", "BLACK", "BROWN" };

SettingsScreen::SettingsScreen()
    : backgroundColorIndex_(0), gridEnabled_(false), gridColorIndex_(0)
{
    font_.loadFromFile("../../Fonts/game_over.ttf");

    backgroundTexture_.loadFromFile("../../img/settingBackground.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    instructionsText_.setFont(font_);
    instructionsText_.setString("Press [SPACE] to start game\nPress [ESC] to go back\nUse mouse to select options");
    instructionsText_.setCharacterSize(24);
    instructionsText_.setPosition(Game::Width / 2 - instructionsText_.getGlobalBounds().width / 2, Game::Height - 100);

    // Set positions and styles for color and grid options
    for (auto i = 0; i < 3; ++i)
    {
        backgroundColorOptions_[i].setSize(sf::Vector2f(30.f, 30.f));
        backgroundColorOptions_[i].setFillColor(Colors[0]);
        backgroundColorOptions_[i].setPosition(350.f + i * 200.f, 310.f);
        optionTexts_[i].setFont(font_);
        optionTexts_[i].setString(ColorNames[i]);
        optionTexts_[i].setCharacterSize(24);
        optionTexts_[i].setPosition(350.f + i * 200.f + 40.f, 310.f);
        optionTexts_[i].setFillColor(sf::Color(210, 212, 212));
    }

    gridEnabledOptions_[0].setSize(sf::Vector2f(30.f, 30.f));
    gridEnabledOptions_[0].setFillColor(Colors[0]);
    gridEnabledOptions_[0].setPosition(480.f, 510.f);
    optionTexts_[3].setFont(font_);
    optionTexts_[3].setString("YES");
    optionTexts_[3].setCharacterSize(24);
    optionTexts_[3].setPosition(520.f, 510.f);
    optionTexts_[3].setFillColor(sf::Color(210, 212, 212));

    gridEnabledOptions_[1].setSize(sf::Vector2f(30.f, 30.f));
    gridEnabledOptions_[1].setFillColor(Colors[0]);
    gridEnabledOptions_[1].setPosition(680.f, 510.f);
    optionTexts_[4].setFont(font_);
    optionTexts_[4].setString("NO");
    optionTexts_[4].setCharacterSize(24);
    optionTexts_[4].setPosition(720.f, 510.f);
    optionTexts_[4].setFillColor(sf::Color(210, 212, 212));

    for (auto i = 0; i < 3; ++i)
    {
        gridColorOptions_[i].setSize(sf::Vector2f(30.f, 30.f));
        gridColorOptions_[i].setFillColor(Colors[0]);
        gridColorOptions_[i].setPosition(350.f + i * 200.f, 710.f);
        optionTexts_[5 + i].setFont(font_);
        optionTexts_[5 + i].setString(ColorNames[i]);
        optionTexts_[5 + i].setCharacterSize(24);
        optionTexts_[5 + i].setPosition(350.f + i * 200.f + 40.f, 710.f);
        optionTexts_[5 + i].setFillColor(sf::Color(210, 212, 212));
    }

    updateText();
}

void SettingsScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<GameScreen>(getBackgroundColor(), isGridEnabled(), getGridColor());
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        Game::Screen = std::make_shared<MenuScreen>();
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        handleMouseClick(window);
}

void SettingsScreen::handleMouseClick(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    for (auto i = 0; i < 3; ++i)
    {
        if (backgroundColorOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            backgroundColorIndex_ = i;
            updateText();
        }

        if (gridColorOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            gridColorIndex_ = i;
            updateText();
        }
    }

    for (auto i = 0; i < 2; ++i)
    {
        if (gridEnabledOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            gridEnabled_ = (i == 0);
            updateText();
        }
    }
}

void SettingsScreen::updateText()
{
    // Highlight selected options
    for (auto i = 0; i < 3; ++i)
    {
        if (i == backgroundColorIndex_)
            backgroundColorOptions_[i].setOutlineThickness(3.f);
        else
            backgroundColorOptions_[i].setOutlineThickness(0.f);

        if (i == gridColorIndex_)
            gridColorOptions_[i].setOutlineThickness(3.f);
        else
            gridColorOptions_[i].setOutlineThickness(0.f);
    }

    for (auto i = 0; i < 2; ++i)
    {
        if ((gridEnabled_ && i == 0) || (!gridEnabled_ && i == 1))
            gridEnabledOptions_[i].setOutlineThickness(3.f);
        else
            gridEnabledOptions_[i].setOutlineThickness(0.f);
    }
}

void SettingsScreen::update(sf::Time delta) {}

void SettingsScreen::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite_);

    window.draw(instructionsText_);

    for (const auto& option : backgroundColorOptions_)
        window.draw(option);

    for (const auto& option : gridEnabledOptions_)
        window.draw(option);

    for (const auto& option : gridColorOptions_)
        window.draw(option);

    for (const auto& text : optionTexts_)
        window.draw(text);

    // window.display();
}

sf::Color SettingsScreen::getBackgroundColor() const
{
    return Colors[backgroundColorIndex_];
}

bool SettingsScreen::isGridEnabled() const
{
    return gridEnabled_;
}

sf::Color SettingsScreen::getGridColor() const
{
    return gridColors[gridColorIndex_];
}
