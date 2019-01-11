#include "Input.h"

Input::Input()
{
}

int * Input::read()
{
	pressedKeys[DIRECTION] = (int)Others::RESET;
	pressedKeys[ACTION] = (int)Others::RESET;
	//directions
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
	//actions
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		pressedKeys[ACTION] = (int)InputKeys::MOUSELEFT;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		pressedKeys[ACTION] = (int)InputKeys::MOUSERIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		pressedKeys[ACTION] = (int)InputKeys::E;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		pressedKeys[ACTION] = (int)InputKeys::TAB;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		pressedKeys[ACTION] = (int)InputKeys::Q;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		pressedKeys[ACTION] = (int)InputKeys::X;
	}
	return pressedKeys;
}
