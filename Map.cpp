#include "Map.h"

std::vector<std::unique_ptr<Tile>> Map::tiles;
std::vector<std::unique_ptr<Tile>> Map::precisePositions;

void Map::readTiles(std::vector<std::unique_ptr<Wrapper>> & walls)
{
	tiles.clear();
	precisePositions.clear();

	for (auto & wall : walls)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)wall->rect->getPosition().x + 20, (int)wall->rect->getPosition().y + 20, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)wall->rect->getPosition().x, (int)wall->rect->getPosition().y, true)));
	}
}

void Map::updateTiles(std::unique_ptr<Wrapper> & player, enemyPair & enemies)
{
	tiles.clear();
	precisePositions.clear();

	for (auto & enemy : enemies)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)enemy.first->rect->getPosition().x + 20, (int)enemy.first->rect->getPosition().y + 20, true, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)enemy.first->rect->getPosition().x, (int)enemy.first->rect->getPosition().y, true, true)));
	}

	precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)player->rect->getPosition().x, (int)player->rect->getPosition().y, true, true)));
}
