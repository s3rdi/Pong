#include "Ball.h"

Ball::Ball(sf::Color color, float radius)
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
	m_speed.x = ConfigB::startSpeedX;
	m_speed.y = ConfigB::startSpeedY;
}

//collision screen
int Ball::screenCollision(sf::View& view, int& userLives, int& enemyLives, bool& waitForInput)
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
		--userLives;
		waitForInput = true;
		return -1;
	}
	else if ((m_body.getPosition().x + m_body.getRadius()) > view.getSize().x / 2.0f) {
		//scoring a point
		reset();
		--enemyLives;
		waitForInput = true;
		return 1;
	}
	return 0;
}

//collision bar
bool Ball::collidingBar(Platform& userBar, Platform& enemyBar) {
	//pixel of the ball colliding with user bar ||
	//pixel of the ball colliding with enemy bar
	if (userBar.getBounaries().contains(m_body.getPosition().x - m_body.getRadius(), m_body.getPosition().y) ||
		enemyBar.getBounaries().contains(m_body.getPosition().x + m_body.getRadius(), m_body.getPosition().y)) {
		m_speed.x *= -ConfigB::incSpeed;
		m_speed.y += -ConfigB::bouncingAngle;
		return true;
	}
	return false;
}