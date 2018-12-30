#include "Tile.h"

Tile::Tile(int xx, int yy, bool obstacle, bool enemy) :x(xx),y(yy), isObstacle(obstacle), enemy(enemy) {}

bool Tile::isEnemy() 
{
	return enemy;
}