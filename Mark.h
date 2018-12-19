#pragma once
#include "Wrapper.h"
#include "StatusBar.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Mark
{
public:
	Mark();
	void markEnemy(int key, enemyPair & enemies, sf::RenderWindow & window);
	enum {LEFTMOUSE = 5};
};

