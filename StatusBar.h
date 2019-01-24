#pragma once
#include <SFML/Graphics.hpp>

class StatusBar
{
public:
	StatusBar();
	StatusBar(int sizeX, int sizeY);
	void setDestroyed();
	sf::RectangleShape & getValueRect();
	sf::RectangleShape & getFrameRect();
	const sf::Text & getText();
	sf::Text & getRefText();
	bool isDestroyed() const;
	void updateStatusBar(int value, int maxValue, std::string label, sf::Vector2f position);
	void updateHUDStatusBar(int value, int maxValue, std::string label, sf::Vector2f position);
	StatusBar & operator=(const StatusBar & other); //necessary
private:
	sf::RectangleShape valueRect;
	sf::RectangleShape frameRect;
	sf::Text text;
	sf::Font font;
	std::string label;
	int sizeX, sizeY;
	int offTextX, offTextY, offRectX, offRectY;
	bool set = false, destroyed = false;
	void setup();
};
