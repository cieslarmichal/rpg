#include "Sprite.h"



Sprite::Sprite(std::string path, int sx, int sy, int dimx, int dimy) : spriteX(sx), spriteY(sy), pathName(path)
{
	offByRectX = offByRectY = 0;
	texture.loadFromFile(pathName);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(dimx, dimy, spriteX, spriteY));

	if (path == "C:\\Users\\Micha³\\Desktop\\cpp\\SFML\\RPG\\RPG\\stuff\\player.png")
	{
		offByRectX = -16;
		offByRectY = -20;
	}
}

Sprite::Sprite(Sprite & other)
{
	sprite = other.sprite;
	texture = other.texture;
	spriteX = other.spriteX;
	spriteY = other.spriteY;
	offByRectX = other.offByRectX;
	offByRectY = other.offByRectY;
	pathName = other.pathName;
}

Sprite & Sprite::operator=(Sprite & other)
{
	sprite = other.sprite;
	texture = other.texture;
	spriteX = other.spriteX;
	spriteY = other.spriteY;
	offByRectX = other.offByRectX;
	offByRectY = other.offByRectY;
	pathName = other.pathName;
	return *this;
}



void Sprite::setTextureRect(int dimx, int dimy, int sx, int sy)
{
	sprite.setTextureRect(sf::IntRect(dimx, dimy, sx, sy));
}

void Sprite::setPosition(int x, int y)
{
	sprite.setPosition(sf::Vector2f(x + offByRectX, y + offByRectY));
}

void Sprite::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position.x + offByRectX, position.y + offByRectY);
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