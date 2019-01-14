#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Node
{
public:
	Node();
	~Node();
	bool obstacle = false;
	bool visited = false;
	float globalGoal; //dist to goal so far
	float localGoal; //dist to goal if alternative
	bool notChanging = false;
	int x, y;
	Node * parent;
	std::vector<Node *> neighbours;
	sf::RectangleShape rect;
};

