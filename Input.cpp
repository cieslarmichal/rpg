#include "Input.h"

Input::Input()
{
}

int * Input::read()
{
	pressedKeys[DIRECTION] = (int)Others::RESET;
	pressedKeys[ACTION] = (int)Others::RESET;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pressedKeys[DIRECTION] = (int)InputKeys::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pressedKeys[DIRECTION] = (int)InputKeys::DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pressedKeys[DIRECTION] = (int)InputKeys::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pressedKeys[DIRECTION] = (int)InputKeys::RIGHT;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		pressedKeys[ACTION] = (int)InputKeys::MOUSELEFT;
	}
	return pressedKeys;
}
