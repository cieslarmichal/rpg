#pragma once
#include <SFML/Graphics.hpp>
#include "Directions.h"

class Input
{
public:
	Input();
	int * read();
	int pressedKeys[2];
	enum { DIRECTION = 0, ACTION = 1 };
};
