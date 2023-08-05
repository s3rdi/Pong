#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"

namespace Config {
    //user's view size
    static constexpr float viewWidth{ 1280.0f };
    static constexpr float viewHeight{ 720.0f };

    //max lives for both players
    static constexpr int maxLives{ 3 };

    //ball config
    static constexpr float ballRadius{ 10.0f };

    //bar config
    static const sf::Vector2f barSize{ 20.0f, 200.0f };
    static constexpr float barPosition{ 450.0f };

    //text config
    static constexpr int textSize{ 50 };
    static constexpr float textMargin{ 10.0f };
    static constexpr float textAxisX{ 50.0f };

    //game color
    static const sf::Color propsColor{ sf::Color::White };
    static const sf::Color bgColor{ sf::Color::Black };

}

//scaling the game to user resized UI
void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio{ static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) };
    view.setSize(sf::Vector2f(Config::viewHeight * aspectRatio, Config::viewHeight));
}

int main()
{
    //creating window view and font
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(Config::viewWidth), static_cast<unsigned int>(Config::viewHeight)), "Pong", sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(Config::viewWidth, Config::viewHeight));
    sf::Font font{};

    //handling font loading
    if (!font.loadFromFile("./fonts/Rushbold.ttf")) {
        std::cout << "Failed to load the font!\n";
        return EXIT_FAILURE;
    }

    //creating objects
    Platform userBar(Config::propsColor, Config::barSize, sf::Vector2f(-Config::barPosition, 0.0f));
    Platform enemyBar(Config::propsColor, Config::barSize, sf::Vector2f(Config::barPosition, 0.0f));
    Ball ball(Config::propsColor, Config::ballRadius, sf::Vector2f(ConfigB::startPositionX, ConfigB::startPositionY));
    int userLives{ Config::maxLives };
    int enemyLives{ Config::maxLives };
    bool waitForInput{ false };

    //creating text
    sf::Text userLivesT{std::to_string(Config::maxLives), font, Config::textSize};
    userLivesT.setFillColor(Config::propsColor);
    userLivesT.setOrigin(userLivesT.getGlobalBounds().getSize().x, 0);
    userLivesT.setPosition(-Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);
    sf::Text enemyLivesT{std::to_string(Config::maxLives), font, Config::textSize};
    enemyLivesT.setFillColor(Config::propsColor);
    enemyLivesT.setPosition(Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);

    //game running
    while (window.isOpen()) {
        sf::Event evnt{};

        //handling all events
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
        userLivesT.setString(std::to_string(userLives));
        enemyLivesT.setString(std::to_string(enemyLives));

        //handling AI movement
        enemyBar.moveAI(ball, enemyBar);
        enemyBar.handleCollision(view);

        //handling user input
        userBar.update();
        userBar.handleCollision(view);

        //handling the window output
        window.clear(Config::bgColor);
        window.setView(view);
        window.draw(userLivesT);
        window.draw(enemyLivesT);
        userBar.draw(window);
        enemyBar.draw(window);
        ball.draw(window);
        window.display();
    }

    return 0;
}