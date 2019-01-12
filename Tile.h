#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(int x, int y, bool obstacle = false, bool enemy = false);
	Tile(sf::Vector2i position, bool obstacle = false, bool enemy = false);
	bool isEnemy();
	bool isObstacle();
	sf::Vector2i getPosition() const;
	int getWidth() const;
	int getHeight() const;
private:
	int x, y;
	int width = 40, height = 40;
	bool obstacle = false;
	bool enemy = false;
};
