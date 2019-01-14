#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "Constants.h"
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
private:
	static TimeHandler enemyTimer, playerTimer;
};
