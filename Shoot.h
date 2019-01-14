#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Create.h"
#include <cmath>
#include "Constants.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Shoot
{
public:
	Shoot() = delete;
	static void shootEnemy(std::unique_ptr<Wrapper>& player, enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles);
	static int findTargetEnemy(enemyPair & enemies);
};
