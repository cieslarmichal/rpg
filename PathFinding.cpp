#include "PathFinding.h"

std::vector<Node > PathFinding::nodes(MAP_WIDTH*MAP_HEIGHT);


PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

sf::Vector2i PathFinding::solveAStar()
{
	if (nodeStart == nullptr || nodeEnd == nullptr) return sf::Vector2i(-1, -1);
	//reset nodes
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (nodes.size() > 0)
			{
				nodes[y*MAP_WIDTH + x].visited = false;
				nodes[y*MAP_WIDTH + x].globalGoal = INFINITY;
				nodes[y*MAP_WIDTH + x].localGoal = INFINITY;
				nodes[y*MAP_WIDTH + x].parent = nullptr;
			}
		}
	}

	auto distance = [](Node *a, Node *b)
	{
		return sqrtf(((float)(a->x - b->x))*((float)(a->x - b->x)) + ((float)(a->y - b->y))*(float)((a->y - b->y)));
	};

	auto heuristic = [distance](Node *a, Node *b)
	{
		return distance(a, b);
	};

	//start conditions
	Node * nodeCurrent = nullptr;
	if (nodeStart != nullptr)
	{
		Node * nodeCurrent = nodeStart;
		nodeStart->localGoal = 0.0f;
		nodeStart->globalGoal = heuristic(nodeStart, nodeEnd);
	}

	//not visited list
	std::list<Node*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	//algorithm
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)
	{
		//sorting
		listNotTestedNodes.sort([](const Node * lhs, const Node * rhs) { return lhs->globalGoal < rhs->globalGoal; });
		//visited nodes
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->visited)
			listNotTestedNodes.pop_front();

		//if no more nodes to visit end
		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->visited = true; // only explore a node once

		for (auto nodeNeighbour : nodeCurrent->neighbours)
		{
			//if neighbour is not visited, is not obstacle add to not tested
			if (!nodeNeighbour->visited && !nodeNeighbour->obstacle)
				listNotTestedNodes.push_back(nodeNeighbour);

			//neighbours potential lowest parentt distance
			float possiblyLowerGoal = nodeCurrent->localGoal + distance(nodeCurrent, nodeNeighbour);

			//if choosing to path through this node is a lower distance than what
			// the neighbour currently has set, update the neighbour to use this node 
			if (possiblyLowerGoal < nodeNeighbour->localGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->localGoal = possiblyLowerGoal;

				//the best path length to the neibour being tested has changed so update global score
				nodeNeighbour->globalGoal = nodeNeighbour->localGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}
	}

	sf::Vector2i nextPosition = { -1,-1 };

	if (nodeEnd != nullptr)
	{
		Node *previous = nodeEnd;
		if (previous != nullptr)
		{
			while (previous->parent != nodeStart)
			{
				if (previous->parent != nullptr)
				{
					previous = previous->parent;
				}

			}
			nextPosition.x = previous->x * 40;
			nextPosition.y = previous->y * 40;

		}
	}

	return nextPosition;
}

void PathFinding::initializeStartEnd(sf::Vector2f startPosition, sf::Vector2f endPosition)
{
	int startIndex = -1;
	int endIndex = -1;

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (x == (((int)startPosition.x + 20) / 40) && y == (((int)startPosition.y + 20)) / 40)
			{
				startIndex = MAP_WIDTH * y + x;

			}
			else if (x == (((int)endPosition.x + 20) / 40) && y == (((int)endPosition.y + 20)) / 40)
			{
				if (!nodes[MAP_WIDTH *y + x].obstacle) {
					endIndex = MAP_WIDTH * y + x;
				}
				else endIndex = -1;
			}
		}
	}
	if (nodes.size() > 0 && endIndex >= 0 && startIndex >= 0)
	{
		nodeStart = &nodes[startIndex];
		nodeEnd = &nodes[endIndex];
	}
	else
	{
		nodeStart = nullptr;
		nodeEnd = nullptr;
	}
}

void PathFinding::initializeLogicMap(std::vector<std::unique_ptr<Tile>> & mapTiles)
{
	//connections
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (y > 0)
			{
				nodes[y*MAP_WIDTH + x].neighbours.push_back(&nodes[(y - 1)*MAP_WIDTH + (x + 0)]);
			}
			if (y < MAP_HEIGHT - 1)
			{
				nodes[y*MAP_WIDTH + x].neighbours.push_back(&nodes[(y + 1)*MAP_WIDTH + (x + 0)]);
			}
			if (x > 0)
			{
				nodes[y*MAP_WIDTH + x].neighbours.push_back(&nodes[(y + 0)*MAP_WIDTH + (x - 1)]);
			}
			if (x < MAP_WIDTH - 1)
			{
				nodes[y*MAP_WIDTH + x].neighbours.push_back(&nodes[(y + 0)*MAP_WIDTH + (x + 1)]);
			}
		}
	}

	//read walls into nodes
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			int tileIndex = 0;
			bool foundTileIndex = false;
			for (auto & tile : mapTiles)
			{
				if (tile->x / tile->width == x && tile->y / tile->width == y)
				{
					foundTileIndex = true;
					break;
				}
				tileIndex++;
			}

			nodes[y*MAP_WIDTH + x].x = x;
			nodes[y*MAP_WIDTH + x].y = y;
			if (foundTileIndex)
			{
				nodes[y*MAP_WIDTH + x].obstacle = mapTiles.at(tileIndex)->isObstacle;
				nodes[y*MAP_WIDTH + x].notChanging = true;
			}
			else nodes[y*MAP_WIDTH + x].obstacle = false;
			nodes[y*MAP_WIDTH + x].parent = nullptr;
			nodes[y*MAP_WIDTH + x].visited = false;
			nodes[y*MAP_WIDTH + x].rect.setPosition((float)40 * x, (float)40 * y);
		}
	}

}
void PathFinding::updateLogicMap(std::vector<std::unique_ptr<Tile>> & mapTiles)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (nodes.size() > 0)
			{
				if (!nodes[y*MAP_WIDTH + x].notChanging)
				{
					int tileIndex = 0;
					bool foundTileIndex = false;
					for (auto & tile : mapTiles)
					{
						if (tile->x / tile->width == x && tile->y / tile->width == y)
						{
							foundTileIndex = true;
							break;
						}
						tileIndex++;
					}

					nodes[y*MAP_WIDTH + x].x = x;
					nodes[y*MAP_WIDTH + x].y = y;
					if (foundTileIndex)
					{
						nodes[y*MAP_WIDTH + x].obstacle = mapTiles.at(tileIndex)->isObstacle;
					}
					else nodes[y*MAP_WIDTH + x].obstacle = false;
					nodes[y*MAP_WIDTH + x].parent = nullptr;
					nodes[y*MAP_WIDTH + x].visited = false;
					nodes[y*MAP_WIDTH + x].rect.setPosition((float)40 * x, (float)40 * y);
				}
			}
		}
	}
}

void PathFinding::debugDrawMap(sf::RenderWindow & window)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (&nodes[y * MAP_WIDTH + x] == nodeEnd)
			{
				nodes[y * MAP_WIDTH + x].rect.setFillColor(sf::Color::Red);
				window.draw(nodes[y * MAP_WIDTH + x].rect);

			}
			else if (&nodes[y * MAP_WIDTH + x] == nodeStart)
			{
				nodes[y * MAP_WIDTH + x].rect.setFillColor(sf::Color::Green);
				window.draw(nodes[y * MAP_WIDTH + x].rect);

			}
			else if (nodes[y * MAP_WIDTH + x].visited)
			{
				nodes[y * MAP_WIDTH + x].rect.setFillColor(sf::Color::Blue);
			}
			else if (!nodes[y * MAP_WIDTH + x].obstacle)
			{
				nodes[y * MAP_WIDTH + x].rect.setFillColor(sf::Color(65, 105, 225, 255));
			}
			else
			{
				window.draw(nodes[y * MAP_WIDTH + x].rect);
				nodes[y * MAP_WIDTH + x].rect.setFillColor(sf::Color(105, 105, 105, 255));
			}
		}
	}

	if (nodeEnd != nullptr)
	{
		bool notFirst = false;
		Node *previous = nodeEnd;
		while (previous->parent != nullptr)
		{
			previous->rect.setFillColor(sf::Color::Yellow);
			if (notFirst) window.draw(previous->rect);
			previous = previous->parent;
			notFirst = true;
		}
	}
}
