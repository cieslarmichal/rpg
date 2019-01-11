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
#include "TimeHandler.h"
#include "Tile.h"
#include "Random.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Movement
{
public:
	Movement() = delete;
	static bool move(Rect & player, int direction);
	static bool movePlayer(Rect & player, int direction);
	static bool moveEnemy(Rect & enemy, Rect & player);
	static bool moveRandom(Rect & enemy);
	static void moveText(Text & text);
	static void moveProjectile(Rect & projectile, enemyPair & enemies);
	static TimeHandler enemyTimer, playerTimer;
};
