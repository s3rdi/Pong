#include "Menu.h"

Menu::Menu(float width, float height, sf::Font& font)
{
	initConfig();
	m_menu[0].setFont(font);
	m_menu[0].setFillColor(mConfig::selectedColor);
	m_menu[0].setString("1 player!");
	m_menu[0].setPosition(sf::Vector2f(-m_menu[0].getGlobalBounds().getSize().x / 2.0f, -(height / 2.0f) + height / (mConfig::maxMenuItems + 1) * 1));

	m_menu[1].setFont(font);
	m_menu[1].setFillColor(m_propsColor);
	m_menu[1].setString("2 players!");
	m_menu[1].setPosition(sf::Vector2f(-m_menu[1].getGlobalBounds().getSize().x / 2.0f, -(height / 2.0f) + height / (mConfig::maxMenuItems + 1) * 2));

	m_menu[2].setFont(font);
	m_menu[2].setFillColor(m_propsColor);
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
		m_menu[m_selectedItem].setFillColor(m_propsColor);
		--m_selectedItem;
		m_menu[m_selectedItem].setFillColor(mConfig::selectedColor);
	}
}

//moving down in menu
void Menu::moveDown()
{
	if (m_selectedItem + 1 < mConfig::maxMenuItems)
	{
		m_menu[m_selectedItem].setFillColor(m_propsColor);
		++m_selectedItem;
		m_menu[m_selectedItem].setFillColor(mConfig::selectedColor);
	}
}

//load config from config.txt file
void Menu::initConfig()
{
	std::ifstream ifs("./config/config.ini");

	std::string tempProp{};
	std::string tempBg{};

	if (!ifs) {
		std::cout << "INI-ERR: Couldn't open config.ini file!\n";
	}
	else {
		if (ifs.is_open()) {
			std::getline(ifs, tempProp);
			if (tempProp.at(0) == '#') {
				std::getline(ifs, tempProp);
			}
			std::getline(ifs, tempBg);
			if (tempBg.at(0) == '#') {
				std::getline(ifs, tempBg);
			}
		}
		ifs.close();

		if (tempProp == "white")
			m_propsColor = sf::Color::White;
		else if (tempProp == "black")
			m_propsColor = sf::Color::Black;
		else if (tempProp == "blue")
			m_propsColor = sf::Color::Blue;
		else if (tempProp == "cyan")
			m_propsColor = sf::Color::Cyan;
		else if (tempProp == "green")
			m_propsColor = sf::Color::Green;
		else if (tempProp == "magenta")
			m_propsColor = sf::Color::Magenta;
		else if (tempProp == "red")
			m_propsColor = sf::Color::Red;
		else if (tempProp == "yellow")
			m_propsColor = sf::Color::Yellow;
		else {
			std::cout << "CFG-ERR: Wrong props color input!\n";
		}

		if (tempBg == "white")
			m_bgColor = sf::Color::White;
		else if (tempBg == "black")
			m_bgColor = sf::Color::Black;
		else if (tempBg == "blue")
			m_bgColor = sf::Color::Blue;
		else if (tempBg == "cyan")
			m_bgColor = sf::Color::Cyan;
		else if (tempBg == "green")
			m_bgColor = sf::Color::Green;
		else if (tempBg == "magenta")
			m_bgColor = sf::Color::Magenta;
		else if (tempBg == "red")
			m_bgColor = sf::Color::Red;
		else if (tempBg == "yellow")
			m_bgColor = sf::Color::Yellow;
		else {
			std::cout << "CFG-ERR: Wrong bg color input!\n";
		}
	}
}