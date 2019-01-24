#pragma once
#include "Tile.h"
#include "Wrapper.h"
#include "StatusBar.h"

using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, std::unique_ptr<StatusBar>>>;

class Map
{
public:
	Map() = delete;
	static void readTiles(std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & trees);
	static void updateTiles(std::unique_ptr<Wrapper> & player, vectorOfCharacters & enemies, vectorOfCharacters & npcs);
	static std::vector<std::unique_ptr<Tile>> tiles;
	static std::vector<std::unique_ptr<Tile>> precisePositions;
};

