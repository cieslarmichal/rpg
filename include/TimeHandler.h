#pragma once
#include <SFML/System/Clock.hpp>

class TimeHandler
{
public:
	TimeHandler();
	void reset();
	float getElapsedSeconds();
	float getElapsedAndReset();
private:
	sf::Clock clock;
	sf::Time elapsed;
};
