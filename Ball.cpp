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
void Ball::screenCollision(sf::View& view, int& userLives, int& enemyLives, bool& waitForInput, sf::Sound& winSound, sf::Sound& loseSound, sf::Sound& sound)
{
	if ((m_body.getPosition().y - m_body.getRadius()) < -view.getSize().y / 2.0f || 
		(m_body.getPosition().y + m_body.getRadius()) > view.getSize().y / 2.0f) {
		//inverting y-axis speed
		sound.play();
		m_speed.y *= -1.0f;
	}

	if ((m_body.getPosition().x - m_body.getRadius()) < -view.getSize().x / 2.0f) {
		//losing a point
		loseSound.play();
		reset();
		--userLives;
		waitForInput = true;
	}
	else if ((m_body.getPosition().x + m_body.getRadius()) > view.getSize().x / 2.0f) {
		//scoring a point
		winSound.play();
		reset();
		--enemyLives;
		waitForInput = true;
	}
}

//collision bar
void Ball::collidingBar(Platform& userBar, Platform& enemyBar, sf::Sound& sound) {
	//pixel of the ball colliding with user bar ||
	//pixel of the ball colliding with enemy bar
	if (userBar.getBounaries().contains(m_body.getPosition().x - m_body.getRadius(), m_body.getPosition().y) ||
		enemyBar.getBounaries().contains(m_body.getPosition().x + m_body.getRadius(), m_body.getPosition().y)) {
		sound.play();
		m_speed.x *= -ConfigB::incSpeed;
		m_speed.y += -ConfigB::bouncingAngle;
	}
}