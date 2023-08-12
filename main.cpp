#include <iostream>
#include <string>
#include <string_view>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Menu.h"
#include "Platform.h"
#include "Config.h"

namespace Config {
    //user's window size
    static constexpr float viewWidth{ 1280.0f };
    static constexpr float viewHeight{ 720.0f };

    //max points for both players
    static constexpr int maxPoints{ 5 };

    //ball radius
    static constexpr float ballRadius{ 8.0f };

    //bar size and starting position
    static constexpr float barHalfSize{ 10.0f };
    static constexpr float barPosition{ 600.0f };

    //text config
    //text size, score position, win and lose frazes
    static constexpr int textSize{ 50 };
    static constexpr float scorePosition{ 50.0f };
    static constexpr std::string_view winResult{ "You win!\n" };
    static constexpr std::string_view loseResult{ "You lose!\n" };
    //two players frazes
    static constexpr std::string_view win1Result{ "Player 1 wins!\n" };
    static constexpr std::string_view win2Result{ "Player 2 wins!\n" };
}

//scaling the game to resized UI
void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio{ static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) };
    view.setSize(sf::Vector2f(Config::viewHeight * aspectRatio, Config::viewHeight));
}

int main()
{
    //initialize config
    initConfig();

    //creating window and view
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(Config::viewWidth), static_cast<unsigned int>(Config::viewHeight)), "Pong", sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(Config::viewWidth, Config::viewHeight));

    //handling icon loading
    sf::Image icon{};
    if (!icon.loadFromFile("./icon.png")) {
        std::cout << "TXT-ERR: Failed to load the icon!\n";
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //handling font loading
    sf::Font font{};
    if (!font.loadFromFile("./fonts/PublicPixel-z84yD.ttf")) {
        std::cout << "FNT-ERR: Failed to load the font!\n";
        return EXIT_FAILURE;
    }

    //creating objects for the game
    Menu menu(Config::viewWidth, Config::viewHeight, font);
    //bars on the opposite sides of the window
    Platform userBar(-Config::barHalfSize, -Config::barPosition);
    Platform enemyBar(Config::barHalfSize, Config::barPosition);
    Ball ball(Config::ballRadius);
    int userPoints{ 0 };
    int enemyPoints{ 0 };

    //creating text
    //user score
    sf::Text t_userLives{std::to_string(0), font, Config::textSize};
    t_userLives.setFillColor(gConfig::propsColor);
    t_userLives.setOrigin(t_userLives.getGlobalBounds().getSize().x, 0.0f);
    t_userLives.setPosition(-Config::scorePosition, -Config::viewHeight / 2.0f + 10.0f); //top margin 10

    //enemy score
    sf::Text t_enemyLives{std::to_string(0), font, Config::textSize};
    t_enemyLives.setFillColor(gConfig::propsColor);
    t_enemyLives.setPosition(Config::scorePosition, -Config::viewHeight / 2.0f + 10.0f); //top margin 10
    
    //game result fraze
    sf::Text t_gameResult{"", font, Config::textSize};
    t_gameResult.setFillColor(gConfig::propsColor);

    //play again prompt
    //lowering textSize by 20
    sf::Text playAgain{ "Enter to continue!\n", font, Config::textSize-20};
    playAgain.setFillColor(gConfig::propsColor);
    //positioning text 200px under the ball
    playAgain.setPosition(-playAgain.getGlobalBounds().getSize().x / 2.0f, 200.0f);

    //esc to quit prompt
    //lowering textSize by 20
    sf::Text t_escToQuit{ "Esc to quit!\n", font, Config::textSize - 20};
    t_escToQuit.setFillColor(gConfig::propsColor);
    //positioning text 50px under playAgain
    t_escToQuit.setPosition(-t_escToQuit.getGlobalBounds().getSize().x / 2.0f, 250.0f);


    //creating all sounds
    //game won sound
    sf::SoundBuffer s_sbWinGame{};
    if (!s_sbWinGame.loadFromFile("./sounds/won_game.wav")) {
        std::cout << "SND-ERR: Failed to load won_game.wav!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_winGame{};
    s_winGame.setBuffer(s_sbWinGame);

    //game lost sound
    sf::SoundBuffer s_sbLoseGame{};
    if (!s_sbLoseGame.loadFromFile("./sounds/lost_game.wav")) {
        std::cout << "SND-ERR: Failed to load lost_game.wav!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_loseGame{};
    s_loseGame.setBuffer(s_sbLoseGame);

    //ball hit sound
    sf::SoundBuffer s_sbBallHit{};
    if (!s_sbBallHit.loadFromFile("./sounds/ball_hit.wav")) {
        std::cout << "SND-ERR: Failed to load ball_hit.wav!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_ballHit{};
    s_ballHit.setBuffer(s_sbBallHit);

    //score sound
    sf::SoundBuffer s_sbScore{};
    if (!s_sbScore.loadFromFile("./sounds/won_point.wav")) {
        std::cout << "SND-ERR: Failed to load won_point.wav!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_scoredPoint{};
    s_scoredPoint.setBuffer(s_sbScore);

    //point lost sound
    sf::SoundBuffer s_sbAIScore{};
    if (!s_sbAIScore.loadFromFile("./sounds/lost_point.wav")) {
        std::cout << "SND-ERR: Failed to load lost_point.wav!\n";
        return EXIT_FAILURE;
    }
    sf::Sound s_lostPoint{};
    s_lostPoint.setBuffer(s_sbAIScore);


    //whether player wants to play
    bool isPlaying{ false };

    //did the player start new game
    bool isNewGame{ false };

    //did the round/game reset
    bool waitForInput{ true };

    //is it 2 players mode
    bool isTwoPlayers{ false };

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
                    isTwoPlayers = false;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    //whether in menu either paused or not playing
                    if (!isPlaying) {
                        menu.moveUp();
                        s_ballHit.play();
                    }
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    //whether in menu either paused or not playing
                    if (!isPlaying) {
                        menu.moveDown();
                        s_ballHit.play();
                    }
                    break;
                case sf::Keyboard::Return:
                case sf::Keyboard::Space:
                    if (!isPlaying) {
                        switch (menu.getSelectedIndex()) {
                        case 0:
                            //play
                            s_scoredPoint.play();
                            isNewGame = true;
                            isPlaying = true;
                            break;
                        case 1:
                            //2 players mode
                            isTwoPlayers = true;
                            isNewGame = true;
                            isPlaying = true;
                            break;
                        case 2:
                            //quit
                            window.close();
                            break;
                        }
                        break;
                    }
                }
                break;
            }
        }

        //if player is in the game
        if (isPlaying) {
            if (waitForInput) {
                //move to continue prompt, skip if it's new game
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || isNewGame) {
                    userBar.reset(-Config::barPosition, 0.0f);
                    enemyBar.reset(Config::barPosition, 0.0f);
                    ball.randStart();
                    //handling instant new game
                    if (userPoints == Config::maxPoints || enemyPoints == Config::maxPoints) {
                        userPoints = 0;
                        enemyPoints = 0;
                        t_gameResult.setString("");
                    }
                    waitForInput = false;
                }
            }
            else {
                isNewGame = false;

                //handling ball movement
                if (ball.collidingBar(userBar, enemyBar, dt)) {
                    s_ballHit.play();
                }
                switch (ball.screenCollision(view)) {
                case 2:
                    s_ballHit.play();
                    break;
                case -1:
                    if (isTwoPlayers)
                        s_scoredPoint.play();
                    else 
                        s_lostPoint.play();
                    ++enemyPoints;
                    waitForInput = true;
                    break;
                case 1:
                    s_scoredPoint.play();
                    ++userPoints;
                    waitForInput = true;
                    break;
                case 0:
                    break;
                }
                ball.update(dt);

                //handling points
                t_userLives.setString(std::to_string(userPoints));
                t_enemyLives.setString(std::to_string(enemyPoints));

                //handling win-lose conditions
                if (enemyPoints == Config::maxPoints) {
                    if (isTwoPlayers) {
                        t_gameResult.setString(static_cast<std::string>(Config::win2Result));
                        t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
                        s_winGame.play();
                    }
                    else {
                        t_gameResult.setString(static_cast<std::string>(Config::loseResult));
                        //set higher (-100.0) for better look
                        t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
                        s_loseGame.play();
                    }
                }
                else if (userPoints == Config::maxPoints) {
                    if (isTwoPlayers) {
                        t_gameResult.setString(static_cast<std::string>(Config::win1Result));
                        t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
                        s_winGame.play();
                    }
                    else {
                        t_gameResult.setString(static_cast<std::string>(Config::winResult));
                        //set higher (-100.0) for better look
                        t_gameResult.setPosition(-t_gameResult.getGlobalBounds().getSize().x / 2.0f, -100.0f);
                        s_winGame.play();
                    }
                }

                //handling AI movement
                if (isTwoPlayers) {
                    enemyBar.update(dt, isTwoPlayers, true);
                }
                else {
                    enemyBar.moveAI(ball, dt);
                }
                enemyBar.handleCollision(view);

                //handling user input
                userBar.update(dt, isTwoPlayers, false);
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

                //drawing when game is over
                if (waitForInput) {
                    window.draw(playAgain);
                    window.draw(t_escToQuit);
                }

                window.display();
            }
        }
        //if not playing display the menu
        if (!isPlaying) {
            window.clear(gConfig::bgColor);
            window.setView(view);
            menu.draw(window);
            window.display();
        }
    }
    return 0;
}