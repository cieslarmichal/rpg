#pragma once
#include "Rect.h"
#include "Text.h"
#include "Projectile.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Directions.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Movement
{
public:
	Movement();
	bool move(Rect & player, int dirc);
	bool moveEnemy(Rect & enemy, Rect & player);
	bool moveRandom(Rect & enemy);
	void moveText(Text & text);
	void moveProjectile(Rect & projectile, enemyPair & enemies);
};

