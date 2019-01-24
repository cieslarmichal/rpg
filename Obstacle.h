#pragma once

class Obstacle
{
public:
	Obstacle(bool tree = false);
	bool isTree() const;
private:
	bool tree;
};
