#ifndef MENU_H
#define MENU_H
#include <array>
#include <SFML/Graphics.hpp>
#include "Config.h"

namespace ConfigM {
	static constexpr int maxMenuItems{ 3 };
	static const sf::Color selectedColor{sf::Color(100, 100, 100)};
}

class Menu
{
public:
	Menu(float width, float height, sf::Font& font);
	~Menu() = default;

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedIndex() { return m_selectedItem; };

private:
	std::array<sf::Text, ConfigM::maxMenuItems> m_menu{};
	int m_selectedItem{};
};

#endif