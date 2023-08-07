#include <iostream>
#include <string>
#include <string_view>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Config.h"
#include "Menu.h"
#include "Platform.h"

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
}

//scaling the game to user resized UI
void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio{ static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) };
    view.setSize(sf::Vector2f(Config::viewHeight * aspectRatio, Config::viewHeight));
}

int main()
{
    //creating window and view
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(Config::viewWidth), static_cast<unsigned int>(Config::viewHeight)), "Pong", sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(Config::viewWidth, Config::viewHeight));

    //handling icon loading
    sf::Image icon{};
    if (!icon.loadFromFile("./icon.png")) {
        std::cout << "Failed to load the icon!\n";
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //handling font loading
    sf::Font font{};
    if (!font.loadFromFile("./fonts/PublicPixel-z84yD.ttf")) {
        std::cout << "Failed to load the font!\n";
        return EXIT_FAILURE;
    }

    //creating objects
    Platform userBar(gConfig::propsColor, Config::barSize, sf::Vector2f(-Config::barPosition, 0.0f));
    Platform enemyBar(gConfig::propsColor, Config::barSize, sf::Vector2f(Config::barPosition, 0.0f));
    Ball ball(gConfig::propsColor, Config::ballRadius);
    Menu menu(Config::viewWidth, Config::viewHeight, font);
    int userLives{ Config::maxLives };
    int enemyLives{ Config::maxLives };

    //creating text
    sf::Text t_userLives{std::to_string(Config::maxLives), font, Config::textSize};
    t_userLives.setFillColor(gConfig::propsColor);
    t_userLives.setOrigin(t_userLives.getGlobalBounds().getSize().x, 0.0f);
    t_userLives.setPosition(-Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);

    sf::Text t_enemyLives{std::to_string(Config::maxLives), font, Config::textSize};
    t_enemyLives.setFillColor(gConfig::propsColor);
    t_enemyLives.setPosition(Config::textAxisX, -Config::viewHeight / 2.0f + Config::textMargin);
    
    sf::Text t_gameResult{"", font, Config::textSize};
    t_gameResult.setFillColor(gConfig::propsColor);

    //creating sounds

    //game won sound
    sf::SoundBuffer s_soundBufferWinGame{};
    if (!s_soundBufferWinGame.loadFromFile("./sounds/won_game.wav")) {
        std::cout << "Failed to load the winning sound!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_winGame{};
    s_winGame.setBuffer(s_soundBufferWinGame);

    //game lost sound
    sf::SoundBuffer s_soundBufferLoseGame{};
    if (!s_soundBufferLoseGame.loadFromFile("./sounds/lost_game.wav")) {
        std::cout << "Failed to load the losing sound!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_loseGame{};
    s_loseGame.setBuffer(s_soundBufferLoseGame);

    //ball hit sound
    sf::SoundBuffer s_soundBufferBallHit{};
    if (!s_soundBufferBallHit.loadFromFile("./sounds/ball_hit.wav")) {
        std::cout << "Failed to load the hitting sound!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_ballHit{};
    s_ballHit.setBuffer(s_soundBufferBallHit);

    //score sound
    sf::SoundBuffer s_soundBufferScore{};
    if (!s_soundBufferScore.loadFromFile("./sounds/won_point.wav")) {
        std::cout << "Failed to load the scoring a point sound!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_scoredPoint{};
    s_scoredPoint.setBuffer(s_soundBufferScore);

    //point lost sound
    sf::SoundBuffer s_soundBufferAIScore{};
    if (!s_soundBufferAIScore.loadFromFile("./sounds/lost_point.wav")) {
        std::cout << "Failed to load the losing a point sound!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_lostPoint{};
    s_lostPoint.setBuffer(s_soundBufferAIScore);



    //smaller font (-20)
    sf::Text playAgain{ "Move to continue!\n", font, Config::textSize-20};
    playAgain.setFillColor(gConfig::propsColor);
    //set lower (200.0f) for better look
    playAgain.setPosition(-playAgain.getGlobalBounds().getSize().x / 2.0f, 200.0f);

    //smaller font (-20)
    sf::Text t_escToQuit{ "Esc to quit!\n", font, Config::textSize - 20};
    t_escToQuit.setFillColor(gConfig::propsColor);
    //set lower (250.0f) for better look
    t_escToQuit.setPosition(-t_escToQuit.getGlobalBounds().getSize().x / 2.0f, 250.0f);

    //checking whether player wants to play
    bool isPlaying{ false };
    bool isNewGame{ false };

    //did the round/game reset
    bool waitForInput{ true };

    //clock for dt
    sf::Clock deltaClock{};
    float dt{};

    //game running
    while (window.isOpen()) {
        dt = deltaClock.restart().asSeconds();
        sf::Event evnt{};

        //handling all events
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                break;
            case sf::Event::KeyReleased:
                switch (evnt.key.code) {
                case sf::Keyboard::Escape:
                    isPlaying = false;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    menu.moveUp();
                    if (waitForInput)
                        s_ballHit.play();
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    if (waitForInput)
                        s_ballHit.play();
                    menu.moveDown();
                    break;
                case sf::Keyboard::Return:
                case sf::Keyboard::Space:
                    switch (menu.getSelectedIndex()) {
                    case 0:
                        s_scoredPoint.play();
                        isNewGame = true;
                        isPlaying = true;
                        break;
                    case 1:
                        //options
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            }
        }

        if (isPlaying) {
            if (waitForInput) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || isNewGame) {
                    //handling instant new game
                    if (userLives == 0 || enemyLives == 0) {
                        userLives = Config::maxLives;
                        enemyLives = Config::maxLives;
                        userBar.reset(-Config::barPosition, 0.0f);
                        enemyBar.reset(Config::barPosition, 0.0f);
                        t_gameResult.setString("");
                    }
                    waitForInput = false;
                }
            }
            else {
                isNewGame = false;
                //handling ball movement
                ball.collidingBar(userBar, enemyBar, s_ballHit);
                ball.screenCollision(view, userLives, enemyLives, waitForInput, s_scoredPoint, s_lostPoint, s_ballHit);
                ball.update(dt);

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
                enemyBar.moveAI(ball, enemyBar, dt);
                enemyBar.handleCollision(view);

                //handling user input
                userBar.update(dt);
                userBar.handleCollision(view);

                //handling the window output
                window.clear(gConfig::bgColor);
                window.setView(view);
                window.draw(t_userLives);
                window.draw(t_enemyLives);
                window.draw(t_gameResult);
                userBar.draw(window);
                enemyBar.draw(window);
                ball.draw(window);

                //win-lose and play again conditions
                if (waitForInput) {
                    window.draw(playAgain);
                    if (userLives == 0) {
                        s_loseGame.play();
                        window.draw(t_escToQuit);
                    }
                    else if (enemyLives == 0) {
                        s_winGame.play();
                        window.draw(t_escToQuit);
                    }
                }

                window.display();
            }
        }

        if (!isPlaying) {
            window.clear(gConfig::bgColor);
            window.setView(view);
            menu.draw(window);
            window.display();
        }
    }
    return 0;
}