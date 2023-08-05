#include "Platform.h"

Platform::Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	m_body.setFillColor(color);
	m_body.setSize(size);
	m_body.setOrigin(size / 2.0f);
	m_body.setPosition(position);
}


//drawing the platform
void Platform::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

//moving player's bar
void Platform::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_body.move(0.0f, -ConfigP::moveSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_body.move(0.0f, ConfigP::moveSpeed);
	}
}

//handling AI
void Platform::moveAI(Ball& ball, Platform& enemyBar)
{
	if (abs(m_body.getPosition().x - ball.getBallPosition().x) < ConfigP::AIresponse) {
		if (m_body.getPosition().y < ball.getBallPosition().y) {
			m_body.move(0.0f, ConfigP::moveSpeed);
		}
		else if (m_body.getPosition().y > ball.getBallPosition().y) {
			m_body.move(0.0f, -ConfigP::moveSpeed);
		}
	}
}

//collision screen
void Platform::handleCollision(sf::View& view)
{
	float halfPlatform{ m_body.getSize().y / 2.0f };
	if (m_body.getPosition().y - halfPlatform < -view.getSize().y / 2.0f) {
		m_body.setPosition(m_body.getPosition().x, -view.getSize().y / 2.0f + halfPlatform);
	}
	else if (m_body.getPosition().y + halfPlatform > view.getSize().y / 2.0f) {
		m_body.setPosition(m_body.getPosition().x, view.getSize().y / 2.0f - halfPlatform);
	}
}
