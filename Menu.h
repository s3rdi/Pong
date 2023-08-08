#ifndef MENU_H
#define MENU_H
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

namespace mConfig {
	//number of items in menu
	static constexpr int maxMenuItems{ 3 };

	//color of the selected item
	static const sf::Color selectedColor{sf::Color(100, 100, 100)};
}

class Menu
{
public:

	Menu(float width, float height, sf::Font& font);
	~Menu() = default;

	//config variables
	sf::Color m_propsColor{};
	sf::Color m_bgColor{};

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void initConfig();
	int getSelectedIndex() { return m_selectedItem; };

private:
	std::array<sf::Text, mConfig::maxMenuItems> m_menu{};
	int m_selectedItem{};
};
#endif