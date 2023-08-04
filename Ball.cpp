#include "Ball.h"

Ball::Ball(sf::Color color, float radius, sf::Vector2f position)
{
	m_body.setOrigin(radius, radius);
	m_body.setFillColor(color);
	m_body.setRadius(radius);
	m_body.setPosition(position);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

//ball movement
void Ball::update(float deltaTime)
{
	m_velocity.x += m_speed.x;
	m_velocity.y += m_speed.y;

	m_body.setPosition(m_velocity.x, m_velocity.y);
}

//collision screen
void Ball::screenCollision(sf::View& view)
{
	if ((m_body.getPosition().y - m_body.getRadius()) < -view.getSize().y / 2.0f || 
		(m_body.getPosition().y + m_body.getRadius()) > view.getSize().y / 2.0f) {
		m_speed.y *= -1;
	}
}

//collision bar
void Ball::collidingBar(Platform& userBar, Platform& enemyBar) {
	//pixel of the ball colliding with user bar
	sf::Vector2f uPC {m_body.getPosition().x - m_body.getRadius(), m_body.getPosition().y};
	//pixel of the ball coliding with enemy bar
	sf::Vector2f ePC {m_body.getPosition().x + m_body.getRadius(), m_body.getPosition().y};
	if (userBar.getBounaries().contains(uPC) || enemyBar.getBounaries().contains(ePC)) {
		m_speed.x *= -1;
	}
}