#pragma once
#include <SFML/Graphics.hpp>
#include "Wrapper.h"
class StatusBar
{
public:
	StatusBar();
	//setters
	void setDestroyed();
	//getters
	sf::RectangleShape & getRect();
	sf::Text & getText();
	bool isDestroyed() const;
	//etc
	void update(std::unique_ptr<Wrapper> & character);
	StatusBar & operator=(StatusBar other); //necessary
private:
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;
	std::string label;
	int max;
	int sizeX, sizeY;
	int offTextX, offTextY, offRectX, offRectY;
	bool set = false, destroyed = false;
	void setup(std::unique_ptr<Wrapper> & character);
};
