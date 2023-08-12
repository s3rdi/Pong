#ifndef CONFIG_H
#define CONFIG_H
#include <SFML/Graphics.hpp>

namespace gConfig {
	//color of all props
	inline sf::Color propsColor{};

	//color of the background
	inline sf::Color bgColor{};
}

void initConfig();
#endif