#pragma once
#include "Sprite.h"

class Animation
{
public:
	Animation(Sprite & sprite, int num);
	Animation(Sprite & staticSprite);
	Animation(Animation & other);
	Animation & operator=(Animation other);
	void update(int direction);
private:
	Sprite & sprite;
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
	int spriteChangingOrder[4] = { 0,2,1,3 }; 
	int currentSprite;
	int numOfSprites;
	sf::Clock clock;
	sf::Time elapsed;
	float delayEachFrame=0.018;
	bool staticSprite;
};

