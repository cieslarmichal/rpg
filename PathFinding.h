#pragma once
#include "Node.h"
#include "Tile.h"
#include "Directions.h"
#include <list>
#include <iostream>

class PathFinding
{
	public:
	PathFinding();
	~PathFinding();
	sf::Vector2i solveAStar();
	void initializeStartEnd(sf::Vector2f startPosition, sf::Vector2f endPosition);
	void initializeLogicMap(std::vector<std::unique_ptr<Tile>> & mapTiles);
	void updateLogicMap(std::vector<std::unique_ptr<Tile>> & mapTiles);
	void debugDrawMap(sf::RenderWindow & window);
	static std::vector<Node> nodes;
	Node * nodeStart = nullptr;
	Node * nodeEnd = nullptr;
};

