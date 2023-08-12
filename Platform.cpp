#include "Platform.h"

Platform::Platform(float size, float position)
{
	m_body.setPointCount(4);
	m_body.setPoint(0, sf::Vector2f(pConfig::width / 2.0f - size, 0.0f));
	m_body.setPoint(1, sf::Vector2f(pConfig::width / 2.0f + size, pConfig::height * 1.0f/3.0f));
	m_body.setPoint(2, sf::Vector2f(pConfig::width / 2.0f + size, pConfig::height * 2.0f/3.0f));
	m_body.setPoint(3, sf::Vector2f(pConfig::width / 2.0f - size, pConfig::height));
	m_body.setOrigin(pConfig::width / 2.0f, pConfig::height / 2.0f);
	m_body.setPosition(position, 0.0f);
	m_body.setFillColor(gConfig::propsColor);
}

//drawing the platform
void Platform::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

//moving player's bar
void Platform::update(float dt, bool isTwoPlayers, bool isPlayerTwo)
{
	if (isTwoPlayers) {
		if (isPlayerTwo) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_body.move(0.0f, -pConfig::moveSpeed * dt);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_body.move(0.0f, pConfig::moveSpeed * dt);
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				m_body.move(0.0f, -pConfig::moveSpeed * dt);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				m_body.move(0.0f, pConfig::moveSpeed * dt);
			}
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_body.move(0.0f, -pConfig::moveSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_body.move(0.0f, pConfig::moveSpeed * dt);
		}
	}
}

//handling AI
void Platform::moveAI(Ball& ball, float dt)
{
	if (m_body.getPosition().x - ball.getBallPosition().x < pConfig::AIresponse) {
		if (m_body.getPosition().y < ball.getBallPosition().y) {
			m_body.move(0.0f, pConfig::moveSpeed * dt);
		}
		else if (m_body.getPosition().y > ball.getBallPosition().y) {
			m_body.move(0.0f, -pConfig::moveSpeed * dt);
		}
	}
}

//handle screen collision
void Platform::handleCollision(sf::View& view)
{
	float halfPlatform{ 60 };
	if (m_body.getPosition().y - halfPlatform < -view.getSize().y / 2.0f) {
		m_body.setPosition(m_body.getPosition().x, -view.getSize().y / 2.0f + halfPlatform);
	}
	else if (m_body.getPosition().y + halfPlatform > view.getSize().y / 2.0f) {
		m_body.setPosition(m_body.getPosition().x, view.getSize().y / 2.0f - halfPlatform);
	}
}

//resetting bar position
void Platform::reset(float positionX, float positionY)
{
	m_body.setPosition(positionX, positionY);
}