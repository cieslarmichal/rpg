#pragma once
#include <random>

class Random
{
public:
	Random() = delete;
	static int getRandomNumber(int rangeStart, int rangeEnd);
private:
	static std::random_device rd;
	static std::mt19937 mt;
};

