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
	int getMovementSpeed() const;
	bool isDestroyed() const;
	//etc
	void update(sf::View);
	Text & operator=(Text other);
private:
	std::string message;
	sf::Vector2f position;
	sf::Text text;
	sf::Font font;
	sf::Color color;
	int fontSize;
	int movementSpeed;
	int lifetime, counter;
	bool destroyed, set = false;
	bool moving;
	bool positionMid;
	void setup();
};
