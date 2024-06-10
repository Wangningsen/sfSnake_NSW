#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "SnakeNode.h"
#include "Fruit.h"
#include "SnakeHead.h"

namespace sfSnake
{
    enum class Direction
    {
        Left, Right, Up, Down, None
    };

    class Snake
    {
    public:
        Snake();
        void handleInput(sf::RenderWindow& window);
        void update(sf::Time delta);
        void render(sf::RenderWindow& window);
        void checkFruitCollisions(std::vector<Fruit>& fruits);
        bool hitSelf() const;
        unsigned getSize() const;
        void relocateFruit(Fruit& fruit);
        const sf::Vector2f generateLocation();
		bool canUseSkill() const;

    private:
        void move();
        void grow(int growlength);
        void checkEdgeCollisions();
        void checkSelfCollisions();
        void initNodes();
       

        bool hitSelf_;
        bool firstUpdate_;
        bool skillActive_;
        sf::Time skillDuration_;
        sf::Clock skillClock_;
        int scoreSinceLastSkill_;

        sf::Vector2f position_;
        Direction direction_;
        sf::Vector2f directionVector_;

        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;

        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;

        std::vector<SnakeNode> nodes_;
        SnakeHead head_;

        static const int InitialSize;
        static const sf::Time SkillDuration;
        static const int SkillScoreMultiplier;
    };
}

#endif

