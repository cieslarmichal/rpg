#pragma once
#include "Tile.h"
#include "Wrapper.h"
#include "StatusBar.h"

class Map
{
public:
	Map() = delete;
	static void readTiles(std::vector<std::unique_ptr<Wrapper>> & walls);
	static void updateTiles(std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> & enemies);
	static std::vector<std::unique_ptr<Tile>> tiles;
};

