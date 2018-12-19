#include "Animation.h"

Animation::Animation(Sprite & spr, int num) : sprite(spr) 
{
	staticSprite = false;
	currentSprite = 0;
	numOfSprites = num;
	if (sprite.getPathName() == "C:\\Users\\Micha³\\Desktop\\cpp\\SFML\\RPG\\RPG\\stuff\\skeleton.png")
	{
		spriteChangingOrder[0] = 3;
		spriteChangingOrder[1] = 0; 
		spriteChangingOrder[2] = 1; 
		spriteChangingOrder[3] = 2;
		delayEachFrame = 0.06;
	}
}

Animation::Animation(Sprite & spr) :sprite(spr)
{

	staticSprite = true;
}

Animation::Animation(Animation & other) : sprite(other.sprite)
{
	spriteChangingOrder[0] = other.spriteChangingOrder[0];
	spriteChangingOrder[1] = other.spriteChangingOrder[1];
	spriteChangingOrder[2] = other.spriteChangingOrder[2];
	spriteChangingOrder[3] = other.spriteChangingOrder[3];
	currentSprite = other.currentSprite;
	numOfSprites = other.numOfSprites;
	clock = other.clock;
	elapsed = other.elapsed;
	delayEachFrame = other.delayEachFrame;
	staticSprite = other.staticSprite;
}

Animation & Animation::operator=(Animation other)
{
	sprite = other.sprite;
	spriteChangingOrder[0] = other.spriteChangingOrder[0];
	spriteChangingOrder[1] = other.spriteChangingOrder[1];
	spriteChangingOrder[2] = other.spriteChangingOrder[2];
	spriteChangingOrder[3] = other.spriteChangingOrder[3];
	currentSprite = other.currentSprite;
	numOfSprites = other.numOfSprites;
	clock = other.clock;
	elapsed = other.elapsed;
	delayEachFrame = other.delayEachFrame;
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
			if (elapsed.asSeconds() >= delayEachFrame)
			{
				clock.restart();
				if (direction == UP)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() *spriteChangingOrder[0], sprite.getSpriteX(), sprite.getSpriteY());
				}
				else if (direction == DOWN)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * spriteChangingOrder[1], sprite.getSpriteX(), sprite.getSpriteY());
				}
				else if (direction == LEFT)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY()*spriteChangingOrder[2], sprite.getSpriteX(), sprite.getSpriteY());

				}
				else if (direction == RIGHT)
				{
					sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * spriteChangingOrder[3], sprite.getSpriteX(), sprite.getSpriteY());
				}
				currentSprite++;
				if (currentSprite >= numOfSprites)
					currentSprite = 0;
			}
		}
	}
}



