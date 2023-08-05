#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "Platform.h"

namespace Config {
	//ball starting position
	static constexpr float startPositionX{ 0.0f };
	static constexpr float startPositionY{ 0.0f };

	//ball starting speed
	static constexpr float startSpeedX{ -0.1f };
	static constexpr float startSpeedY{ 0.05f };

	//angle of bouncing ball
	static constexpr float bouncingAngle{ 1.2f };
}

class Platform;

class Ball
{
public:
	Ball(sf::Color color, float radius, sf::Vector2f position);
	~Ball() = default;

	void draw(sf::RenderWindow& window);
	void update();
	void screenCollision(sf::View& view, int& userLives, int& enemyLives, bool& waitForInput);
	void collidingBar(Platform& userBar, Platform& enemyBar);
	void reset();
	sf::Vector2f getBallPosition() { return m_body.getPosition(); };

private:
	sf::CircleShape m_body;
	sf::Vector2f m_velocity{ Config::startPositionX, Config::startPositionY };
	sf::Vector2f m_speed{ Config::startSpeedX, Config::startSpeedX };
};
#endif