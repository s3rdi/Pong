#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Platform.h"

namespace bConfig {
	//angle of bouncing ball
	static constexpr float bouncingAngle{ 1.3f };

	//increasing speed multiplier
	static constexpr float incSpeed{ 1.05f };
}

//forward declaring platform for collidingBar function
class Platform;

class Ball
{
public:
	Ball(float radius);
	~Ball() = default;

	void draw(sf::RenderWindow& window);
	void update(float dt);
	int screenCollision(sf::View& view);
	bool collidingBar(Platform& userBar, Platform& enemyBar);
	void reset();
	void randStart();
	sf::Vector2f getBallPosition() { return m_body.getPosition(); };

private:
	sf::CircleShape m_body{};
	sf::Vector2f m_velocity{ 0.0f, 0.0f };
	sf::Vector2f m_speed{};
};
#endif