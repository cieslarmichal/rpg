#pragma once
#include "Sprite.h"
#include "Directions.h"

class Animation
{
public:
	Animation(Sprite & sprite, int num);
	Animation(Sprite & staticSprite);
	void update(int direction);
private:
	Sprite & sprite;
	int spriteChangingOrder[4] = { 0,2,1,3 }; 
	int currentSprite = 0;
	int numOfSprites;
	sf::Clock clock;
	sf::Time elapsed;
	float delayEachFrame = 0.018f;
	bool staticSprite;
};

