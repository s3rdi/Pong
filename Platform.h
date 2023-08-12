#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Ball.h"
#include "Config.h"

namespace pConfig {
	//speed of bars
	static constexpr float moveSpeed{ 700.0f };

	//x-axis distance of AI's bar responding to the ball
	static constexpr float AIresponse{ 500.0f };

	//bar height
	static constexpr float height{ 120.0f };

	//bar width
	static constexpr float width{ 20.0f };
}

//forward declaring ball for moveAI function
class Ball;

class Platform
{
public:
	Platform(float size, float position);
	~Platform() = default;

	void draw(sf::RenderWindow& window);
	void update(float dt, bool isTwoPlayers, bool isPlayerTwo);
	void moveAI(Ball& ball, float dt);
	void handleCollision(sf::View& view);
	void reset(float positionX, float positionY);
	auto getBounaries() { return m_body.getGlobalBounds(); };

private:
	sf::ConvexShape m_body{};
};
#endif
