#include "Map.h"

std::vector<std::unique_ptr<Tile>> Map::tiles;
std::vector<std::unique_ptr<Tile>> Map::precisePositions;

void Map::readTiles(std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & trees)
{
	tiles.clear();
	precisePositions.clear();

	for (auto & wall : walls)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)wall->rect->getPosition().x + 20, (int)wall->rect->getPosition().y + 20, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)wall->rect->getPosition().x, (int)wall->rect->getPosition().y, true)));
	}

	for (auto & tree : trees)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)tree->rect->getPosition().x + 20, (int)tree->rect->getPosition().y + 20, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)tree->rect->getPosition().x, (int)tree->rect->getPosition().y, true)));
	}
}

void Map::updateTiles(std::unique_ptr<Wrapper>& player, vectorOfCharacters & enemies, vectorOfCharacters & npcs)
{
	tiles.clear();
	precisePositions.clear();

	for (auto & enemy : enemies)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)enemy.first->rect->getPosition().x + 20, (int)enemy.first->rect->getPosition().y + 20, true, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)enemy.first->rect->getPosition().x, (int)enemy.first->rect->getPosition().y, true, true)));
	}

	for (auto & npc : npcs)
	{
		tiles.push_back(std::unique_ptr<Tile>(new Tile((int)npc.first->rect->getPosition().x + 20, (int)npc.first->rect->getPosition().y + 20, true, true)));
		precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)npc.first->rect->getPosition().x, (int)npc.first->rect->getPosition().y, true, true)));
	}

	precisePositions.push_back(std::unique_ptr<Tile>(new Tile((int)player->rect->getPosition().x, (int)player->rect->getPosition().y, true, true)));
}


