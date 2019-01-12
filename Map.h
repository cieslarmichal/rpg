#pragma once
#include "Tile.h"
#include "Wrapper.h"
#include "StatusBar.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Map
{
public:
	Map() = delete;
	static void readTiles(std::vector<std::unique_ptr<Wrapper>> & walls);
	static void updateTiles(std::unique_ptr<Wrapper> & player, enemyPair & enemies);
	static std::vector<std::unique_ptr<Tile>> tiles;
	static std::vector<std::unique_ptr<Tile>> precisePositions;
};

