#ifndef MENU_H
#define MENU_H
#include <array>
#include <SFML/Graphics.hpp>
#include "Config.h"

namespace mConfig {
	//number of items in menu
	static constexpr int maxMenuItems{ 3 };

	//color of the selected item
	static const sf::Color selectedColor{sf::Color(200, 200, 200, 100)};
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
	std::array<sf::Text, mConfig::maxMenuItems> m_menu{};
	int m_selectedItem{};
};
#endif