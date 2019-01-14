#pragma once
#include <SFML/Graphics.hpp>

class TimeHandler
{
public:
	TimeHandler();
	void reset();
	void reset2();
	float getElapsedSeconds();
	float getElapsedSeconds2();
private:
	sf::Clock clock, clock2;
	sf::Time elapsed, elapsed2;
};
