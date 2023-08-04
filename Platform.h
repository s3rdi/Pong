#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>

//platform maker
class Platform
{
public:
	Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position);
	~Platform() = default;

	void draw(sf::RenderWindow& window);
	void update();
	void handleCollision(sf::View& view);

private:
	sf::RectangleShape m_body;

};

#endif