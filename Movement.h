#pragma once
#include "Rect.h"
#include "Text.h"
#include "Projectile.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Movement
{
public:
	Movement();
	bool move(Rect & character, int dirc);
	bool moveRandom(Rect & character);
	bool moveText(Text & text);
	void moveProjectile(Rect & projectile, enemyPair & enemies);
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };

};

