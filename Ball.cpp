#include <random>
#include "Ball.h"

Ball::Ball(float radius, sf::Color& color)
{
	m_body.setOrigin(radius, radius);
	m_body.setFillColor(color);
	m_body.setRadius(radius);
	m_body.setPosition(0.0f, 0.0f);
}

//drawing the ball
void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

//ball movement
void Ball::update(float dt)
{
	m_velocity.x += m_speed.x * dt;
	m_velocity.y += m_speed.y * dt;

	m_body.setPosition(m_velocity.x, m_velocity.y);
}

//resetting the ball after scoring
void Ball::reset()
{
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
}

//checking screen collison
int Ball::screenCollision(sf::View& view)
{
	if ((m_body.getPosition().y - m_body.getRadius()) < -view.getSize().y / 2.0f || 
		(m_body.getPosition().y + m_body.getRadius()) > view.getSize().y / 2.0f) {
		//inverting y-axis speed
		m_speed.y *= -1.0f;
		return 2;
	}

	if ((m_body.getPosition().x - m_body.getRadius()) < -view.getSize().x / 2.0f) {
		//losing a point
		reset();
		return -1;
	}
	else if ((m_body.getPosition().x + m_body.getRadius()) > view.getSize().x / 2.0f) {
		//scoring a point
		reset();
		return 1;
	}
	return 0;
}

//checking bar collision
bool Ball::collidingBar(Platform& userBar, Platform& enemyBar) {
	//pixel of the ball colliding with user bar ||
	//pixel of the ball colliding with enemy bar
	if (userBar.getBounaries().intersects(m_body.getGlobalBounds()) ||
		enemyBar.getBounaries().intersects(m_body.getGlobalBounds())) {
		m_speed.x *= -bConfig::incSpeed;
		m_speed.y += bConfig::bouncingAngle;
		return true;
	}
	return false;
}

//randomize first ball move
void Ball::randStart()
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution dRandomizer{ 1, 2 };
	auto tempX = (dRandomizer(mt) == 1) ?  -1 : 1;
	auto tempY = (dRandomizer(mt) == 1) ? -1 : 1;

	m_speed.x = 500.0f * tempX;
	m_speed.y = 300.0f * tempY;
}