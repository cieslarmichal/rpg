#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Text
{
public:
	Text(std::string message, sf::Vector2f pos, sf::Color color, bool move = true, bool mid = false, int FontSize = 16);
	//setters
	void setDestroyed();
	//getters
	sf::Text & getText();
	float getMovementSpeed() const;
	bool isDestroyed() const;
	//etc
	void update(sf::View);
	Text & operator=(Text other); //necassary
private:
	std::string message;
	sf::Vector2f position;
	sf::Text text;
	sf::Font font;
	sf::Color color;
	int fontSize;
	float movementSpeed;
	int lifetime, lifeCounter;
	bool destroyed, set = false;
	bool moving;
	bool positionMid;
	void setup();
};
