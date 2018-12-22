#include "SearchCell.h"



SearchCell::SearchCell(int xx, int yy, SearchCell * p) : x(xx), y(yy), parent(p), G(0), H(0)
{
	id = y * 1000 + x;
}

float SearchCell::getF()
{
	return G + H;
}

float SearchCell::manhattanDistance(SearchCell *nodeEnd)
{
	float x = (float)(fabs(this->x - nodeEnd->x));
	float y = (float)(fabs(this->y - nodeEnd->y));
	return x + y;
}
