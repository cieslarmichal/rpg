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
	Movement() = delete;
	static bool move(Rect & player, int dirc);
	static bool moveEnemy(Rect & enemy, Rect & player);
	static bool moveRandom(Rect & enemy);
	static void moveText(Text & text);
	static void moveProjectile(Rect & projectile, enemyPair & enemies);
};
