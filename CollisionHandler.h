#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include <iostream>

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class CollisionHandler
{
public:
	CollisionHandler();
	bool isIntersecting(Rect & r1, Rect & r2) const;
	bool playerWithObstacles(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	bool enemiesWithObstacles(enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	bool playerWithEnemies(std::unique_ptr<Wrapper> & player, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts);
	bool projectilesWithEnemies(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts);
	bool projectilesWithWalls(std::vector<std::unique_ptr<Wrapper>> & projectiles, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void setDamageMessage(int takenHp, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & texts);
	enum { OUT = -1, RESET = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
	int playerCantMove = RESET, enemyCantMove = RESET, enemyIndex = OUT;
private:
	sf::Clock clock1, clock2;
	sf::Time elapsed1, elapsed2;
};

