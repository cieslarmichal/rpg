#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Create.h"
#include <cmath>
#include "Directions.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Shoot
{
public:
	static void shootEnemy(std::unique_ptr<Wrapper>& player, enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles);
	static int findTargetEnemy(enemyPair & enemies);
	static int calculateSpriteDimension(int flagX, int flagY, double angle);
};
