#include "Map.h"



Map::Map()
{
}

void Map::readTiles(std::vector<std::unique_ptr<Wrapper>> & walls)
{
	tiles.clear();

	for (auto & wall : walls)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)wall->rect->getPosition().x + 20, (int)wall->rect->getPosition().y + 20, true)));
	}
}

void Map::updateTiles(std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> & enemies)
{
	tiles.clear();

	for (auto & enemy : enemies)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)enemy.first->rect->getPosition().x + 20, (int)enemy.first->rect->getPosition().y + 20, true, true)));
	}
}
