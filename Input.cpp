#include "Input.h"



Input::Input()
{
}


int Input::read()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		return UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		return DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		return LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		return RIGHT;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return MOUSELEFT;
	}
	return 0;
}
