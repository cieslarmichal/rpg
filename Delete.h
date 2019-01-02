#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "Blocked.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Delete
{
public:
	Delete() = delete;
	static void removeEnemies(enemyPair & characters);
	static void removeText(std::vector < std::unique_ptr<Text>> & texts);
	static void removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles);
	static void setCharacterDead(std::unique_ptr<Wrapper> & character);
	static void setProjectileToDestroy(std::unique_ptr<Wrapper> & object);
	static void setBlockedToDestroy(Blocked & blocked);
	static void removeBlocked(std::vector<Blocked> & blockedCharacters);
};
