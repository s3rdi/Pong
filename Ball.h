#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "Platform.h"

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
	sf::Vector2f getBallPosition() { return m_body.getPosition(); };

private:
	sf::CircleShape m_body;
	sf::Vector2f m_velocity{0.0f, 0.0f};
	sf::Vector2f m_speed{-0.1f, 0.05f};
};
#endif