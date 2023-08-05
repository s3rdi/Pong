#include "Ball.h"

Ball::Ball(sf::Color color, float radius, sf::Vector2f position)
{
	m_body.setOrigin(radius, radius);
	m_body.setFillColor(color);
	m_body.setRadius(radius);
	m_body.setPosition(position);
}


//drawing the ball
void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

//ball movement
void Ball::update()
{
	m_velocity.x += m_speed.x;
	m_velocity.y += m_speed.y;

	m_body.setPosition(m_velocity.x, m_velocity.y);
}

//resetting the ball after scoring
void Ball::reset()
{
	m_velocity.x = Config::startPositionX;
	m_velocity.y = Config::startPositionY;
	m_speed.x = Config::startSpeedX;
	m_speed.x = Config::startSpeedY;
}

//collision screen
void Ball::screenCollision(sf::View& view, int& userLives, int& enemyLives, bool& waitForInput)
{
	if ((m_body.getPosition().y - m_body.getRadius()) < -view.getSize().y / 2.0f || 
		(m_body.getPosition().y + m_body.getRadius()) > view.getSize().y / 2.0f) {
		//inverting y-axis
		m_speed.y *= -1.0f;
	}

	if ((m_body.getPosition().x - m_body.getRadius()) < -view.getSize().x / 2.0f) {
		//losing a point
		reset();
		--userLives;
		waitForInput = true;
	}
	else if ((m_body.getPosition().x + m_body.getRadius()) > view.getSize().x / 2.0f) {
		//scoring a point
		reset();
		--enemyLives;
		waitForInput = true;
	}
}

//collision bar
void Ball::collidingBar(Platform& userBar, Platform& enemyBar) {
	//pixel of the ball colliding with user bar ||
	//pixel of the ball colliding with enemy bar
	if (userBar.getBounaries().contains(m_body.getPosition().x - m_body.getRadius(), m_body.getPosition().y) ||
		enemyBar.getBounaries().contains(m_body.getPosition().x + m_body.getRadius(), m_body.getPosition().y)) {
		m_speed.x *= -Config::bouncingAngle;
	}
}