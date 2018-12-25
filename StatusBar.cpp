#include "StatusBar.h"


StatusBar::StatusBar()
{
	max = 0;
	sizeX = 34;
	sizeY = 5;
	offTextX = offRectX = 0;
	offTextY = -32;
	offRectY = -16;
}

//setters
void StatusBar::setDestroyed()
{
	destroyed = true;
}

//getters
bool StatusBar::isDestroyed() const
{
	return destroyed;
}

sf::RectangleShape & StatusBar::getRect()
{
	return rect;
}

sf::Text & StatusBar::getText()
{
	return text;
}

//etc
void StatusBar::updateStatusBar(std::unique_ptr<Wrapper> & character)
{
	if(!set) setup(character);

	text.setPosition(character->rect->getPosition().x + offTextX, character->rect->getPosition().y + offTextY);
	rect.setPosition(character->rect->getPosition().x + offRectX, character->rect->getPosition().y + offRectY);
	if (character->rect->character->getCurrentHp() >= 0.7*max)
	{
		rect.setFillColor(sf::Color::Green);
		text.setFillColor(sf::Color::Green);
	}
	else if (character->rect->character->getCurrentHp() >= 0.40*max)
	{
		rect.setFillColor(sf::Color::Yellow);
		text.setFillColor(sf::Color::Yellow);
	}
	else if (character->rect->character->getCurrentHp() > 0.18*max)
	{
		rect.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Red);
	}
	else if (character->rect->character->getCurrentHp() > 0)
	{
		rect.setFillColor(sf::Color(63, 0, 0, 255));
		text.setFillColor(sf::Color(63, 0, 0, 255));
	}

	if (character->rect->character->getCurrentHp() <= 0)
	{
		rect.setSize(sf::Vector2f(0, 0));
	}
	else
	{
		rect.setSize(sf::Vector2f((float)(character->rect->character->getCurrentHp() * sizeX / max), (float)sizeY));
	}
}

void StatusBar::setup(std::unique_ptr<Wrapper> & character)
{
	max = character->rect->character->getMaxHp();
	font.loadFromFile("stuff/font.ttf");
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	text.setFont(font);
	text.setCharacterSize(12);
	text.setString((character->rect->character->getName()));

	if (character->sprite->getPathName() == "stuff/skeleton.png")
	{
		offTextX = 6;
		offTextY = -21;
		offRectX = 8;
		offRectY = -5;
	}
	set = true;
}

StatusBar & StatusBar::operator=(StatusBar other)
{
	font = other.font;
	text = other.text;
	text.setFont(font);
	rect = other.rect;
	max = other.max;
	sizeX = other.sizeX;
	sizeY = other.sizeY;
	offTextX = other.offTextX;
	offTextY = other.offTextY;
	offRectX = other.offRectX;
	offRectY = other.offRectY;
	set = other.set;
	destroyed = other.destroyed;
	return *this;
}
