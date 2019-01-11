#include "Random.h"
std::random_device Random::rd;
std::mt19937 Random::mt(rd());


int Random::getRandomNumber(int rangeStart, int rangeEnd)
{
	std::uniform_int_distribution<int> dist(rangeStart, rangeEnd);
	return dist(mt);
}
