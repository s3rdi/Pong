#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"

namespace Config {
    //height of user's view
    static constexpr float g_viewHeight{ 1024.0f };

    //max lives for both players
    static constexpr int maxLives{ 3 };

    //ball config
    static constexpr float ballRadius{ 10.0f };

    //bar config
    static const sf::Vector2f barSize{ 20.0f, 200.0f };
    static constexpr float barPosition{ 400.0f };

    //game color
    static const sf::Color gameColor{ sf::Color::White };
}

//scaling the game to user resized UI
void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio{ static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) };
    view.setSize(sf::Vector2f(Config::g_viewHeight * aspectRatio, Config::g_viewHeight));
}

int main()
{
    //creating window and view
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Pong", sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024.0f, Config::g_viewHeight));

    //creating objects
    Platform userBar(Config::gameColor, Config::barSize, sf::Vector2f(-Config::barPosition, 0.0f));
    Platform enemyBar(Config::gameColor, Config::barSize, sf::Vector2f(Config::barPosition, 0.0f));
    Ball ball(Config::gameColor, Config::ballRadius, sf::Vector2f(ConfigB::startPositionX, ConfigB::startPositionY));
    int userLives{ Config::maxLives };
    int enemyLives{ Config::maxLives };
    bool waitForInput{ false };

    //game running
    while (window.isOpen()) {
        sf::Event evnt;

        //handling user calls
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
            }
        }

        //handling ball movement
        while (waitForInput) {
            //move to start
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                waitForInput = false;
            }
        }
        ball.collidingBar(userBar, enemyBar);
        ball.screenCollision(view, userLives, enemyLives, waitForInput);
        ball.update();

        //handling AI movement
        enemyBar.moveAI(ball, enemyBar);
        enemyBar.handleCollision(view);

        //handling user input
        userBar.update();
        userBar.handleCollision(view);

        //handling the window output
        window.clear(sf::Color::Black);
        window.setView(view);
        userBar.draw(window);
        enemyBar.draw(window);
        ball.draw(window);
        window.display();
    }

    return 0;
}