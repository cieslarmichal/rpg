#include "Animation.h"
#include <iostream>

Animation::Animation(Sprite &spr, int num) : sprite(spr) 
{
	staticSprite = false;
	currentSprite = 0;
	numOfSprites = num;
	if (sprite.getPathName() == "C:\\Users\\Micha³\\Desktop\\cpp\\SFML\\RPG\\RPG\\stuff\\skeleton.png")
	{
		tab[0] = 3; tab[1] = 0; tab[2] = 1; tab[3] = 2;
		delay = 0.06;
	}
}

Animation::Animation(Sprite & spr) :sprite(spr)
{

	staticSprite = true;
}

Animation::Animation(Animation & other) : sprite(other.sprite)
{
	tab[0] = other.tab[0];
	currentSprite = other.currentSprite;
	numOfSprites = other.numOfSprites;
	clock = other.clock;
	elapsed = other.elapsed;
	delay = other.delay;
	staticSprite = other.staticSprite;
}

Animation & Animation::operator=(Animation other)
{
	sprite = other.sprite;
	tab[0] = other.tab[0];
	currentSprite = other.currentSprite;
	numOfSprites = other.numOfSprites;
	clock = other.clock;
	elapsed = other.elapsed;
	delay = other.delay;
	staticSprite = other.staticSprite;
	return *this;
}

void Animation::update(int direction)
{
	if (!staticSprite)
	{
		elapsed = clock.getElapsedTime();

		if (direction >= 1 && direction <= 4)
		{
			if (elapsed.asSeconds() >= delay)
			{
				clock.restart();
				if (direction == UP)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() *tab[0], sprite.getSpriteX(), sprite.getSpriteY());
				}
				else if (direction == DOWN)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * tab[1], sprite.getSpriteX(), sprite.getSpriteY());
				}
				else if (direction == LEFT)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY()*tab[2], sprite.getSpriteX(), sprite.getSpriteY());

				}
				else if (direction == RIGHT)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * tab[3], sprite.getSpriteX(), sprite.getSpriteY());
				}
				currentSprite++;
				if (currentSprite >= numOfSprites)
					currentSprite = 0;
			}
		}
	}
}



