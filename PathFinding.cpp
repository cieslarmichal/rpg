//#include "PathFinding.h"
//
//
//
//PathFinding::PathFinding()
//{
//	initializedStartGoal = false;
//	foundGoal = false;
//}
//
//
//PathFinding::~PathFinding()
//{
//}
//
//void PathFinding::initialize(sf::Vector2i currentPos, sf::Vector2i targetPos)
//{
//	pathState = INITIALIZE;
//
//	openList.clear();
//	visitedList.clear();
//	pathToGoal.clear();
//
//	//initialize start
//	SearchCell start;
//	start.x = currentPos.x/32;
//	start.y = currentPos.y/32;
//
//	//initialize goal
//	SearchCell goal;
//	goal.x = targetPos.x/32;
//	goal.y = targetPos.y/32;
//
//	initializeStartGoal(start, goal);
//	pathState = SEARCHING;
//
//}
//
//void PathFinding::initializeStartGoal(SearchCell start, SearchCell goal)
//{
//	if (!startCell)
//	{
//		startCell = new SearchCell(start.x, start.y, nullptr);
//	}
//	if (!goalCell)
//	{
//		goalCell = new SearchCell(goal.x, goal.y, &goal);
//	}
//
//	startCell->x = start.x;
//	startCell->y = start.y;
//	startCell->id = start.y * 1000 + start.x;
//	startCell->G = 0;
//	startCell->H = startCell->manhattanDistance(goalCell);
//	startCell->parent = 0;
//
//	goalCell->x = goal.x;
//	goalCell->y = goal.y;
//	goalCell->id = goal.y * 1000 + goal.x;
//
//	openList.push_back(startCell);
//}
//
//void PathFinding::iterate()
//{
//	if (openList.empty())
//	{
//		return;
//	}
//
//	SearchCell * currentCell = getNextCell();
//
//	if (currentCell->id == goalCell->id)
//	{
//		goalCell->parent = currentCell->parent;
//		SearchCell * getPath;
//
//		for (getPath = goalCell; getPath != nullptr; getPath = getPath->parent)
//		{
//			pathToGoal.push_back(new sf::Vector2i(getPath->x* 32, getPath->y*32));
//		}
//		foundGoal = true;
//		return;
//	}
//	else
//	{
//		//rightSide
//		checkNeighbor(currentCell->x + 1, currentCell->y, currentCell->G + 1, currentCell->parent);
//		//leftSide
//		checkNeighbor(currentCell->x - 1, currentCell->y, currentCell->G + 1, currentCell->parent);
//		//up
//		checkNeighbor(currentCell->x, currentCell->y - 1, currentCell->G + 1, currentCell->parent);
//		//down
//		checkNeighbor(currentCell->x, currentCell->y + 1, currentCell->G + 1, currentCell->parent);
//
//		for (int i = 0; i < openList.size(); i++)
//		{
//			if (currentCell->id == openList[i]->id)
//			{
//				openList.erase(openList.begin() + 1);
//			}
//		}
//	}
//}
//
//
//SearchCell * PathFinding::getNextCell()
//{
//	float bestF = 999999.0f;
//	int cellIndex = -1;
//	SearchCell * nextCell = nullptr;
//
//	for (int i = 0; openList.size(); i++)
//	{
//		if (openList[i]->getF() < bestF)
//		{
//			bestF = openList[i]->getF();
//			cellIndex = i;
//		}
//	}
//
//	if (cellIndex >= 0)
//	{
//		nextCell = openList[cellIndex];
//		visitedList.push_back(nextCell);
//		openList.erase(openList.begin() + cellIndex);
//	}
//	return nextCell;
//}
//
//
//void PathFinding::checkNeighbor(int x, int y, float newCost, SearchCell * parent)
//{
//	/*if (CELL_BLOCKED)
//	{
//		return;
//	}*/
//
//	int id = y * 1000 + x;
//	for (int i = 0; i < visitedList.size(); i++)
//	{
//		if (id == visitedList[i]->id)
//		{
//			return;
//		}
//	}
//
//	SearchCell * newChild = new SearchCell(x, y, parent);
//	newChild->G = newCost;
//	newChild->H = parent->manhattanDistance(goalCell);
//
//	for (int i = 0; i < openList.size(); i++)
//	{
//		if (id == openList[i]->id)
//		{
//			float newF = newChild->G + newCost + openList[i]->H;
//
//			if (openList[i]->getF() > newF)
//			{
//				openList[i]->G = newChild->G + newCost;
//				openList[i]->parent = newChild;
//			}
//			else // if the F is not better
//			{
//				delete newChild;
//				return;
//			}
//		}
//	}
//
//	openList.push_back(newChild);
//}
//
//
//
//
//sf::Vector2f PathFinding::nextPathPos()
//{
//	int index = 1;
//	sf::Vector2i nextPos;
//	nextPos.x = pathToGoal[pathToGoal.size() - index]->x;
//	nextPos.y = pathToGoal[pathToGoal.size() - index]->y;
//
//	sf::Vector2i distance = nextPos - pos;
//	if (index < pathToGoal.size())
//	{
//		if (distance.() < radius)
//		{
//			pathToGoal.erase(pathToGoal.end() - index);
//		}
//	}
//
//	return nextPos;
//}
//
//
//
