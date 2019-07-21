#include "Random.h"
std::random_device Random::rd;
std::mt19937 Random::mt(rd());


int Random::getRandomNumber(int rangeStart, int rangeEnd)
{
	std::uniform_int_distribution<int> dist(rangeStart, rangeEnd);
	return dist(mt);
}

bool Random::isSuccessful(double probability)
{
	int numberOfTens = 0;
	while (probability <= 100)
	{
		probability *= 10.0f;
		numberOfTens++;
	}

	int randomNumber = getRandomNumber(1, (int)pow(10, numberOfTens));
	if (randomNumber > 0 && randomNumber <= probability) return true;
	return false;
}

