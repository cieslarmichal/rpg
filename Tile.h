#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(int x, int y, bool obstacle = false, bool enemy = false);
	int x, y;
	int width = 40, height = 40;
	bool isObstacle = false;
	bool enemy = false;
	bool isEnemy();
};
