#include "Tile.h"

Tile::Tile(int xx, int yy, bool obstacle, bool enemy) :x(xx),y(yy), obstacle(obstacle), enemy(enemy)
{
}

Tile::Tile(sf::Vector2f position, bool obstacle, bool enemy) : x(position.x), y(position.y), obstacle(obstacle), enemy(enemy)
{
}

bool Tile::isEnemy() 
{
	return enemy;
}

bool Tile::isObstacle() 
{
	return obstacle;
}

sf::Vector2f Tile::getPosition() const
{
	return sf::Vector2f((float)x, (float)y);
}

int Tile::getX() const
{
	return x;
}

int Tile::getY() const
{
	return y;
}

int Tile::getWidth() const
{
	return width;
}

int Tile::getHeight() const
{
	return height;
}
