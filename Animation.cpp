#include "Animation.h"

Animation::Animation(Sprite & spr, int num) : sprite(spr), numOfSprites(num)
{
	staticSprite = false;
	if (sprite.getPathName() == "stuff/skeleton.png")
	{
		spriteChangingOrder[0] = 3;
		spriteChangingOrder[1] = 0;
		spriteChangingOrder[2] = 1;
		spriteChangingOrder[3] = 2;
		delayEachFrame = 0.06f;
	}
}

Animation::Animation(Sprite & spr) :sprite(spr)
{
	staticSprite = true;
}

void Animation::update(int direction)
{
	if (staticSprite) return;

	if (timing.getElapsedSeconds() >= delayEachFrame)
	{
		timing.reset();

		switch (direction)
		{
		case (int)Directions::UP:
			sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() *spriteChangingOrder[0], sprite.getSpriteX(), sprite.getSpriteY());
			break;
		case (int)Directions::DOWN:
			sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * spriteChangingOrder[1], sprite.getSpriteX(), sprite.getSpriteY());
			break;
		case (int)Directions::LEFT:
			sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY()*spriteChangingOrder[2], sprite.getSpriteX(), sprite.getSpriteY());
			break;
		case (int)Directions::RIGHT:
			sprite.setTextureRect(sprite.getSpriteX() * currentSprite, sprite.getSpriteY() * spriteChangingOrder[3], sprite.getSpriteX(), sprite.getSpriteY());
			break;
		}

		currentSprite++;
		if (currentSprite >= numOfSprites)
		{
			currentSprite = 0;
		}
	}
}
