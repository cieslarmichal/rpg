#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Sprite
{
public:
	Sprite(std::string path, int sx, int sy, int dimx = 0, int dimy = 0);
	void setTextureRect(int dimx, int dimy, int spriteX, int spriteY);
	void setPosition(sf::Vector2f position);
	void setPosition(int x, int y);
	std::string getPathName();
public:
	int getSpriteX() const;
	int getSpriteY() const;
	sf::Sprite & getSprite();
	sf::Texture & getTexture();
	sf::Vector2f getPosition() const;
	static sf::Vector2i calculateProjectileSprite(bool positiveX, bool positiveY, double angle);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string pathName;
	int spriteX, spriteY;
	int offByRectX, offByRectY;
};
