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
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 }; //directions
	//tab keeps information about ordering sprite, default with human order
	int tab[4] = { 0,2,1,3 }; 
	int currentSprite;
	int numOfSprites;
	sf::Clock clock;
	sf::Time elapsed;
	float delay=0.018; // delay for each frame in ms
	bool staticSprite;
};

