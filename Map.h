#pragma once
#include "Tile.h"
#include "Wrapper.h"
#include "StatusBar.h"

class Map
{
public:
	Map();
	void readTiles(std::vector<std::unique_ptr<Wrapper>> & walls);
	void updateTiles(std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> & enemies);
	std::vector<std::unique_ptr<Tile>> tiles;
};

