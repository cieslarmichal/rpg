#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Create.h"
#include <cmath>

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Shoot
{
public:
	Shoot();
	void shootEnemy(std::unique_ptr<Wrapper>& player, enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles);
	int findTargetEnemy(enemyPair & enemies);
	int calculateSpriteDimension(int flagX, int flagY, double angle);
private:
	Create creator;
	enum { OUT = -1 };
	sf::Clock clock;
	sf::Time elapsed;
};

