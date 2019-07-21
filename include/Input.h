#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Input
{
public:
	Input();
	int * read();
	enum { DIRECTION = 0, ACTION = 1 };
private:
	int pressedKeys[2];
};
