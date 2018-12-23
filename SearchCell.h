#pragma once
#include <cmath>


class SearchCell
{
public:
	SearchCell() : parent(nullptr) {}
	SearchCell(int x, int y, SearchCell * parent = nullptr);
	~SearchCell() {}
public:
	float getF();
	float manhattanDistance(SearchCell *nodeEnd);
	int x, y;
	int id;
	SearchCell * parent;
	float G;
	float H;

};
