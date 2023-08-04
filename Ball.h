#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Ball
{
public:
	Ball(sf::Color color, float radius, sf::Vector2f position);
	~Ball() = default;

	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	void screenCollision(sf::View& view);
	void collidingBar(Platform& userBar, Platform& enemyBar);

private:
	sf::CircleShape m_body;
	sf::Vector2f m_velocity{0.0f, 0.0f};
	sf::Vector2f m_speed{-0.1f, 0.04f};
};


#endif