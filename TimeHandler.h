#pragma once
#include <SFML/Graphics.hpp>

class TimeHandler
{
public:
	TimeHandler();
	void reset();
	int getElapsedSeconds();
private:
	sf::Clock clock;
	sf::Time elapsed;
};
