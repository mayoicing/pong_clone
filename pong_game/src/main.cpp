#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "Paddle.h"

int main() {

    // CREATE WINDOW
    sf::VideoMode VM(1280, 720);                // Screen resolution (height, width)
    sf::RenderWindow window(VM, "Pong Clone");  // Create window for graphics

    // INITIALIZE VARIABLES
    ball myball(1280/2, 0);                     // Ball to be ping-ponged
    Paddle myPaddle(1280/2, 710);               // Paddle to ping-pong
    sf::Event event;                            // Event to be processed

    // TIME PROPERTIES
    sf::Time dt;                                // Time
    sf::Clock clock;                            // Clock for dt
    float bounceTimer = 0.10f;                  // Timer for bounce
    
    // FONT CHARACTERISTICS
    sf::Font font;
    sf::Text fontHUD;
    font.loadFromFile("src/fonts/pixel-emulator.ttf");
    fontHUD.setFont(font);
    fontHUD.setPosition(15, 10);
    fontHUD.setCharacterSize(30);
    fontHUD.setOutlineThickness(2);
    fontHUD.setFillColor(sf::Color::Red);
    fontHUD.setOutlineColor(sf::Color::White);

    // LIVES GAME COMPONENT
    int lives = 3;
    std::stringstream ss;
    ss << "Lives: " << lives; 
    fontHUD.setString(ss.str());


    // CHECK IF WINDOW WAS CREATED
    if (!window.isOpen()) {
        std::cout << "Failed to create window!" << std::endl;
        return -1;
    }

    // GAME LOOP
    while (window.isOpen()) {

        dt = clock.restart();           // Gets dt every second
        bounceTimer -= dt.asSeconds();  // Makes sure ball doesn't glitch out when bouncing off paddle

        // CHECK COLLISION
        if (myball.getPosition().intersects(myPaddle.getPosition())) {
            if (bounceTimer < 0) {
                myball.hitBall();
                bounceTimer = 0.10f;
            } 
        }

        // CLOSES WINDOW IF YOU PRESS 'ESC'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || lives < 0) {
            window.close();
        }

        // PADDLE MOVES LEFT WHEN YOU PRESS 'A
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            myPaddle.moveLeft();
        } else {
            myPaddle.stopLeft();
        }

        // PADDLE MOVES RIGHT WHEN YOU PRESS 'D'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            myPaddle.moveRight();
        } else {
            myPaddle.stopRight();
        }
        
        // IF PADDLE HITS LEFT SIDE OF WINDOW, IT STOPS
        if (myPaddle.getPosition().left < 0) {
            myPaddle.stopLeft();
        }

        // IF PADDLE HITS RIGHT SIDE OF WINDOW, IT STOPS
        if (myPaddle.getPosition().left + myPaddle.getPosition().width > 1280) {
            myPaddle.stopRight();
        }

        // CLOSES WINDOW WHEN YOU CLICK 'X'
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // HANDLE BALL BOUNCING OFF LEFT & RIGHT SIDES
        if (myball.getPosition().left < 0 || (myball.getPosition().left + myball.getPosition().width) > 1280) {
            myball.bounceSides();
        }

        // HANDLES BALL BOUNCING OFF TOP SIDE
        if (myball.getPosition().top < 0 && bounceTimer < 0) {
            myball.bounceTop();
            bounceTimer = 0.10f;
        }

        // HANDLES BALL BOUNCING OFF BOTTOM SIDE
        if ((myball.getPosition().top + myball.getPosition().height) > 720) {
            myball.missBottom();

            // HANDLES TEXT FOR LIVES
            ss.str("");                     // Clears entire string
            lives--;                        // Decrement lives
            ss << "Lives: " << lives;       // Rewrite lives
            fontHUD.setString(ss.str());    // Output
        }

        window.clear(); // Clears window
        myball.update(dt);                  // Updates ball position
        myPaddle.update(dt);                // Updates paddle position
        window.draw(myball.getShape());     // Draws ball
        window.draw(myPaddle.getShape());   // Draws paddle
        window.draw(fontHUD);               // Draws text
        window.display();                   // Updates window
    }

    return 0;
}