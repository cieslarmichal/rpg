#include "Node.h"


Node::Node()
{
	rect.setSize(sf::Vector2f((float)40, (float)40));
	rect.setFillColor(sf::Color::Blue);

}

Node::~Node()
{
	for (auto & node : neighbours)
	{
		if (parent != nullptr) delete parent;
		node->parent = nullptr;
	}
	neighbours.clear();
	parent = nullptr;
}

