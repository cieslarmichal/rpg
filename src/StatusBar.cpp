#include "StatusBar.h"


StatusBar::StatusBar()
{
	sizeX = 34;
	sizeY = 5;
	offTextX = offRectX = 6;
	offTextY = -32;
	offRectY = -16;
	text.setCharacterSize(12);
}

StatusBar::StatusBar(int sx, int sy) : sizeX(sx), sizeY(sy)
{
	frameRect.setFillColor(sf::Color(0, 0, 0, 0));
	frameRect.setOutlineColor(sf::Color::Black);
	frameRect.setOutlineThickness(1);
	text.setCharacterSize(16);
}

void StatusBar::setDestroyed()
{
	destroyed = true;
}

bool StatusBar::isDestroyed() const
{
	return destroyed;
}

sf::RectangleShape & StatusBar::getValueRect()
{
	return valueRect;
}

sf::RectangleShape & StatusBar::getFrameRect()
{
	return frameRect;
}

const sf::Text & StatusBar::getText()
{
	return text;
}

sf::Text & StatusBar::getRefText()
{
	return text;
}

void StatusBar::updateStatusBar(int value, int maxValue, std::string label, sf::Vector2f position)
{
	if (!set) setup();

	text.setString(label);
	text.setPosition(position.x + offTextX, position.y + offTextY);
	valueRect.setPosition(position.x + offRectX, position.y + offRectY);
	if (value >= 0.7*maxValue)
	{
		valueRect.setFillColor(sf::Color::Green);
		text.setFillColor(sf::Color::Green);
	}
	else if (value >= 0.40*maxValue)
	{
		valueRect.setFillColor(sf::Color::Yellow);
		text.setFillColor(sf::Color::Yellow);
	}
	else if (value > 0.18*maxValue)
	{
		valueRect.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Red);
	}
	else if (value > 0)
	{
		valueRect.setFillColor(sf::Color(63, 0, 0, 255));
		text.setFillColor(sf::Color(63, 0, 0, 255));
	}

	if (value <= 0)
	{
		valueRect.setSize(sf::Vector2f(0, 0));
	}
	else
	{
		valueRect.setSize(sf::Vector2f((float)(value * sizeX / maxValue), (float)sizeY));
	}
}

void StatusBar::updateHUDStatusBar(int value, int maxValue, std::string label, sf::Vector2f position)
{
	if (!set) setup();
	text.setString(label);
	text.setPosition(position.x, position.y);
	valueRect.setPosition(position.x,position.y+20);
	valueRect.setSize(sf::Vector2f((float)(value * sizeX / maxValue), (float)sizeY));

	frameRect.setPosition(position.x, position.y+20);
	frameRect.setSize(sf::Vector2f((float)(sizeX), (float)sizeY));
}

void StatusBar::setup()
{
	//this function cant be in constructor, errors

	font.loadFromFile("../stuff/font.ttf");
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setFont(font);
	set = true;
}

StatusBar & StatusBar::operator=(const StatusBar & other)
{
	label = other.label;
	font = other.font;
	text = other.text;
	text.setFont(font);
	valueRect = other.valueRect;
	frameRect = other.frameRect;
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


