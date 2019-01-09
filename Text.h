#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Text
{
public:
	Text(sf::Color color, std::string type, int FontSize = 16);
	Text(std::string message, sf::Vector2f pos, sf::Color color, bool move = true, int FontSize = 16);
	void setDestroyed();
	sf::Text & getText();
	std::string getHUDtype() const;
	float getMovementSpeed() const;
	bool isDestroyed() const;
	void update(sf::Vector2f position);
	void updateHUDInformation(sf::Vector2f position, int value, int valueMax = -1);
	Text & operator=(Text other); //necassary
private:
	std::string message;
	std::string HUDtype;
	sf::Vector2f position;
	sf::Text text;
	sf::Font font;
	sf::Color color;
	int fontSize;
	float movementSpeed;
	int lifetime, lifeCounter;
	bool destroyed, set = false;
	bool moving;
	void setup();
};
