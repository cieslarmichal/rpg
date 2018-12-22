#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Sprite
{
public:
	Sprite(std::string path, int sx, int sy, int dimx = 0, int dimy = 0);
	//setters
	void setTextureRect(int dimx, int dimy, int spriteX, int spriteY);
	void setPosition(sf::Vector2f position);
	void setPosition(int x, int y);
	//getters
	std::string getPathName();
	int getSpriteX() const;
	int getSpriteY() const;
	sf::Sprite & getSprite();
	sf::Texture & getTexture();
	sf::Vector2f getPosition() const;
	//etc
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string pathName;
	int spriteX, spriteY;
	int offByRectX, offByRectY;
};