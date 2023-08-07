#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "Ball.h"

namespace ConfigP {
	//speed of bars
	static constexpr float moveSpeed{ 500.0f };

	//x-axis distance of AI's bar responding to the ball
	static constexpr float AIresponse{ 500.0f };
}

class Ball;

//platform maker
class Platform
{
public:
	Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position);
	~Platform() = default;

	void draw(sf::RenderWindow& window);
	void update(float dt);
	void moveAI(Ball& ball, Platform& enemyBar, float dt);
	void handleCollision(sf::View& view);
	void reset(float positionX, float positionY);
	auto getBounaries() { return m_body.getGlobalBounds(); };

private:
	sf::RectangleShape m_body{};

};

#endif