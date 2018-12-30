#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Directions.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Mark
{
public:
	Mark() = delete;
	static void markTarget(int key, std::unique_ptr<Wrapper> & player, enemyPair & enemies, sf::RenderWindow & window);
};
