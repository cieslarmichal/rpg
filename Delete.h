#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Delete
{
public:
	Delete();
	void removeEnemies(enemyPair & characters);
	void removeText(std::vector < std::unique_ptr<Text>> & texts);
	void removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles);
};

