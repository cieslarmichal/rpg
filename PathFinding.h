#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "SearchCell.h"

class PathFinding
{
public:
	PathFinding();
	~PathFinding();
	void initialize(sf::Vector2i currentPos, sf::Vector2i targetPos);
	sf::Vector2f nextPathPos();
	void clearOpenList() { openList.clear(); }
	void clearVisitedList() { visitedList.clear(); }
	void clearPathToGoal() { pathToGoal.clear(); }
	bool initializedStartGoal;
	bool foundGoal;
private:
	void initializeStartGoal(SearchCell start, SearchCell goal);
	void checkNeighbor(int x, int y, float newCost, SearchCell * parent);
	SearchCell * getNextCell();
	void iterate();

	SearchCell * startCell;
	SearchCell * goalCell;
	std::vector<SearchCell*> openList;
	std::vector<SearchCell*> visitedList;
	std::vector<sf::Vector2i*> pathToGoal;
};

