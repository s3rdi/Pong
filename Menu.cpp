#include "Menu.h"

Menu::Menu(float width, float height, sf::Font& font)
{
	m_menu[0].setFont(font);
	m_menu[0].setFillColor(mConfig::selectedColor);
	m_menu[0].setString("1 player!");
	m_menu[0].setPosition(sf::Vector2f(-m_menu[0].getGlobalBounds().getSize().x / 2.0f, -(height / 2.0f) + height / (mConfig::maxMenuItems + 1) * 1));

	m_menu[1].setFont(font);
	m_menu[1].setFillColor(gConfig::propsColor);
	m_menu[1].setString("2 players!");
	m_menu[1].setPosition(sf::Vector2f(-m_menu[1].getGlobalBounds().getSize().x / 2.0f, -(height / 2.0f) + height / (mConfig::maxMenuItems + 1) * 2));

	m_menu[2].setFont(font);
	m_menu[2].setFillColor(gConfig::propsColor);
	m_menu[2].setString("Quit");
	m_menu[2].setPosition(sf::Vector2f(-m_menu[2].getGlobalBounds().getSize().x / 2.0f, -(height / 2.0f) + height / (mConfig::maxMenuItems + 1) * 3));

	m_selectedItem = 0;
}

//drawing menu
void Menu::draw(sf::RenderWindow& window)
{
	for (auto& element : m_menu) {
		window.draw(element);
	}
}

//moving up in menu
void Menu::moveUp()
{
	if (m_selectedItem - 1 >= 0)
	{
		m_menu[m_selectedItem].setFillColor(gConfig::propsColor);
		--m_selectedItem;
		m_menu[m_selectedItem].setFillColor(mConfig::selectedColor);
	}
}

//moving down in menu
void Menu::moveDown()
{
	if (m_selectedItem + 1 < mConfig::maxMenuItems)
	{
		m_menu[m_selectedItem].setFillColor(gConfig::propsColor);
		++m_selectedItem;
		m_menu[m_selectedItem].setFillColor(mConfig::selectedColor);
	}
}