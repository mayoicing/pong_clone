#pragma once
#include <SFML/Graphics.hpp>

class ball {
    private:
        sf::Vector2f m_Position;
        sf::RectangleShape m_BallShape;
    
        float m_Speed = 500;
        float m_DirectionX = 1.0f;
        float m_DirectionY = 1.0f;
    
    public:
        // Constructor
        ball(float startX, float startY);

        // Getter methods
        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        float getXVelocity();

        // Bounce ball logic
        void bounceSides();
        void bounceTop();
        void missBottom();
    
        // Game loop 
        void hitBall();
        void update(sf::Time dt);
};