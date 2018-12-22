#pragma once
#include <iostream>
#include <valarray>
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "Directions.h"
#include "Fight.h"
#include "Blocked.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class CollisionHandler
{
public:
	CollisionHandler();
	bool isIntersecting(Rect & r1, Rect & r2) const;
	void characterWithObstacles(std::unique_ptr<Wrapper> & character, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void enemiesWithObstacles(enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void playerWithEnemies(std::unique_ptr<Wrapper> & player, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts);
	void enemiesWithEnemies(enemyPair & enemies);
	void projectilesWithEnemies(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts);
	void projectilesWithWalls(std::vector<std::unique_ptr<Wrapper>> & projectiles, std::vector<std::unique_ptr<Wrapper>> & obstacles);
private:
	void setEnemyCollidingWithPlayer(std::vector<bool> & enemiesCollidingWithPlayer, int enemyIndex, bool isColliding);
	bool canUnclockPlayerDirection(const Blocked & blocked, bool * playerCollision);
	bool canUnlockEnemyDirection(const Blocked & blocked, bool enemyCollidingWithPlayer, int enemyIndex);
	void unlockBlockedCharacter(std::unique_ptr<Wrapper> & character, Blocked & blocked);
	bool topDistanceShortest(int * distances);
	bool botDistanceShortest(int * distances);
	bool leftDistanceShortest(int * distances);
	bool rightDistanceShortest(int * distances);
	enum { TOP = 0, BOT = 1, LEFT = 2, RIGHT = 3 };
	std::vector<Blocked> blockedCharacters;
	void setDamageMessage(int takenHp, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & texts); //to delete
};

