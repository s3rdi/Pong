#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Config.h"

//load config from config.ini file
void initConfig()
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
			gConfig::propsColor = sf::Color::White;
		else if (tempProp == "black")
			gConfig::propsColor = sf::Color::Black;
		else if (tempProp == "blue")
			gConfig::propsColor = sf::Color::Blue;
		else if (tempProp == "cyan")
			gConfig::propsColor = sf::Color::Cyan;
		else if (tempProp == "green")
			gConfig::propsColor = sf::Color::Green;
		else if (tempProp == "magenta")
			gConfig::propsColor = sf::Color::Magenta;
		else if (tempProp == "red")
			gConfig::propsColor = sf::Color::Red;
		else if (tempProp == "yellow")
			gConfig::propsColor = sf::Color::Yellow;
		else {
			std::cout << "CFG-ERR: Wrong props color input!\n";
		}

		if (tempBg == "white")
			gConfig::bgColor = sf::Color::White;
		else if (tempBg == "black")
			gConfig::bgColor = sf::Color::Black;
		else if (tempBg == "blue")
			gConfig::bgColor = sf::Color::Blue;
		else if (tempBg == "cyan")
			gConfig::bgColor = sf::Color::Cyan;
		else if (tempBg == "green")
			gConfig::bgColor = sf::Color::Green;
		else if (tempBg == "magenta")
			gConfig::bgColor = sf::Color::Magenta;
		else if (tempBg == "red")
			gConfig::bgColor = sf::Color::Red;
		else if (tempBg == "yellow")
			gConfig::bgColor = sf::Color::Yellow;
		else {
			std::cout << "CFG-ERR: Wrong bg color input!\n";
		}
	}
}