#include <iostream>
#include <string>
#include <string_view>
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
    static constexpr std::string_view winResult{ "You win!\n" };
    static constexpr std::string_view loseResult{ "You lose!\n" };

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
    if (!font.loadFromFile("./fonts/PublicPixel-z84yD.ttf")) {
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
    sf::Text t_userLives{std::to_string(Config::maxLives), font, Config::textSize};
    t_userLives.setFillColor(Config::propsColor);
    t_userLives.setOrigin(t_userLives.getGlobalBounds().getSize().x, 0.0f);
    t_userLives.setPosition(-Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);

    sf::Text t_enemyLives{std::to_string(Config::maxLives), font, Config::textSize};
    t_enemyLives.setFillColor(Config::propsColor);
    t_enemyLives.setPosition(Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);
    
    sf::Text t_gameResult{"", font, Config::textSize};
    t_gameResult.setFillColor(Config::propsColor);

    //smaller font by 20
    sf::Text playAgain{ "Move to continue!\n", font, Config::textSize-20};
    playAgain.setFillColor(Config::propsColor);
    //set lower (200.0f) for better look
    playAgain.setPosition(-playAgain.getGlobalBounds().getSize().x / 2.0f, 200.0f);

    //smaller font by 20
    sf::Text t_escToQuit{ "Esc to quit!\n", font, Config::textSize - 20};
    t_escToQuit.setFillColor(Config::propsColor);
    //set lower (250.0f) for better look
    t_escToQuit.setPosition(-t_escToQuit.getGlobalBounds().getSize().x / 2.0f, 250.0f);

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
                //handling instant new game
                if (userLives == 0 || enemyLives == 0) {
                    userLives = Config::maxLives;
                    enemyLives = Config::maxLives;
                    t_gameResult.setString("");
                }
                waitForInput = false;
            }
        }
        ball.collidingBar(userBar, enemyBar);
        ball.screenCollision(view, userLives, enemyLives, waitForInput);
        ball.update();

        //handling points
        t_userLives.setString(std::to_string(userLives));
        t_enemyLives.setString(std::to_string(enemyLives));

        //handling win and lose conditions
        if (userLives == 0) {
            t_gameResult.setString(static_cast<std::string>(Config::loseResult));
            //set higher (-100.0) for better look
            t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
        }
        else if (enemyLives == 0) {
            t_gameResult.setString(static_cast<std::string>(Config::winResult));
            //set higher (-100.0) for better look
            t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
        }

        //handling AI movement
        enemyBar.moveAI(ball, enemyBar);
        enemyBar.handleCollision(view);

        //handling user input
        userBar.update();
        userBar.handleCollision(view);

        //handling the window output
        window.clear(Config::bgColor);
        window.setView(view);
        window.draw(t_userLives);
        window.draw(t_enemyLives);
        window.draw(t_gameResult);
        userBar.draw(window);
        enemyBar.draw(window);
        if (waitForInput) {
            window.draw(playAgain);
            if (userLives == 0 || enemyLives == 0)
                window.draw(t_escToQuit);
        }
        ball.draw(window);
        window.display();
    }

    return 0;
}