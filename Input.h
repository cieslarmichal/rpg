#pragma once
#include <SFML/Graphics.hpp>
class Input
{
public:
	Input();
	int read();
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, MOUSELEFT = 5 };
};

