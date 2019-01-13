#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Directions.h"

class Text
{
public:
	Text(sf::Color color, std::string type, int FontSize = 16, std::string message = "");
	Text(std::string message, sf::Vector2f pos, sf::Color color, bool move = true, int FontSize = 16, bool staticPosition = false, bool shortLifeTime = false);
	void setDestroyed();
	sf::Text & getText();
	std::string getHUDtype() const;
	float getMovementSpeed() const;
	bool isDestroyed() const;
	void update(sf::Vector2f position);
	void updateHUDInformation(sf::Vector2f position, int value = (int)Others::RESET, int valueMax = (int)Others::RESET);
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
	bool destroyed, set, staticPosition, shortLifeTime = false;
	bool moving;
	void setup();
};
