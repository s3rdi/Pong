#include "Platform.h"

Platform::Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	m_body.setFillColor(color);
	m_body.setSize(size);
	m_body.setOrigin(size / 2.0f);
	m_body.setPosition(position);
}

void Platform::draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}
