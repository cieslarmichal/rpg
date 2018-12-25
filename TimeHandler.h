#pragma once
#include <SFML/Graphics.hpp>

class TimeHandler
{
public:
	TimeHandler();
	void reset();
	float getElapsedSeconds();
private:
	sf::Clock clock;
	sf::Time elapsed;
};
