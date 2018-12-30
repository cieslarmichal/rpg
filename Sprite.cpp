#include "Sprite.h"

Sprite::Sprite(std::string path, int sx, int sy, int dimx, int dimy) : spriteX(sx), spriteY(sy), pathName(path)
{
	offByRectX = offByRectY = 0;
	if (!texture.loadFromFile(pathName)) 
		std::cerr << "error reading sprite from file\n";
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(dimx, dimy, spriteX, spriteY));

	if (path == "stuff/player.png")
	{
		offByRectX = -11;
		offByRectY = -20;
	}
	else if (path == "stuff/skeleton.png")
	{
		offByRectX = 0;
		offByRectY = -4;
	}
	else if (path == "stuff/dragon.png")
	{
		offByRectX = -30;
		offByRectY = -34;
	}
}

void Sprite::setTextureRect(int dimx, int dimy, int sx, int sy)
{
	sprite.setTextureRect(sf::IntRect(dimx, dimy, sx, sy));
}

void Sprite::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f((float)(x + offByRectX), (float)(y + offByRectY)));
}

void Sprite::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position.x + (float)offByRectX, position.y + (float)offByRectY);
}

//getters

std::string Sprite::getPathName()
{
	return pathName;
}

int Sprite::getSpriteX() const
{
	return spriteX;
}

int Sprite::getSpriteY() const
{
	return spriteY;
}

sf::Sprite & Sprite::getSprite()
{
	return sprite;
}

sf::Texture & Sprite::getTexture()
{
	return texture;
}

sf::Vector2f Sprite::getPosition() const
{
	return sprite.getPosition();
}

sf::Vector2i Sprite::calculateProjectileSprite(bool positiveX, bool positiveY, double angle)
{
	sf::Vector2i dimension = { 0,0 };

	if (positiveX)
	{
		if (!positiveY)
		{
			if (angle >= 0 && angle <= 0.45) dimension.y = 4 * 64;
			else if (angle > 0.45 && angle <= 1.1) dimension.y = 3 * 64;
			else dimension.y = 2 * 64;
		}
		else if (positiveY)
		{
			if (angle >= 0 && angle <= 0.45) dimension.y = 4 * 64;
			else if (angle > 0.45 && angle <= 1.1) dimension.y = 5 * 64;
			else dimension.y = 6 * 64;
		}
	}
	else if (!positiveX)
	{
		if (!positiveY)
		{
			if (angle >= 0 && angle <= 0.45) dimension.y = 0;
			else if (angle > 0.45 && angle <= 1.1) dimension.y = 1 * 64;
			else dimension.y = 2 * 64;
		}
		else if (positiveY)
		{
			if (angle >= 0 && angle <= 0.45) dimension.y = 0;
			else if (angle > 0.45 && angle <= 1.1) dimension.y = 7 * 64;
			else dimension.y = 6 * 64;
		}
	}

	return dimension;
}