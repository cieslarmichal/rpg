#pragma once
#include <SFML/Graphics.hpp>
#include "Wrapper.h"
class StatusBar
{
public:
	StatusBar();
	void setDestroyed();
	sf::RectangleShape & getRect();
	sf::Text & getText();
	bool isDestroyed() const;
	void updateStatusBar(std::unique_ptr<Wrapper> & character, int enemyIndex);
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
	void setup(std::unique_ptr<Wrapper> & character, int enemyIndex);
};
