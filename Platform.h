#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Config.h"

namespace pConfig {
	//speed of bars
	static constexpr float moveSpeed{ 700.0f };

	//x-axis distance of AI's bar responding to the ball
	static constexpr float AIresponse{ 500.0f };
}

//forward declaring ball for moveAI function
class Ball;

class Platform
{
public:
	Platform(sf::Vector2f size, sf::Vector2f position);
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