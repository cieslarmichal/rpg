#include "Text.h"


Text::Text(sf::Color col, std::string type, int font, std::string msg)
	: color(col), fontSize(font), HUDtype(type), message(msg)
{
}

Text::Text(std::string msg, sf::Vector2f pos, sf::Color col, bool move, int font, bool staticp, bool shortLife)
	: message(msg), position(pos), color(col), fontSize(font), moving(move), staticPosition(staticp), shortLifeTime(shortLife)
{
	if (moving)
	{
		movementSpeed = 1;
		lifetime = 40;
	}
	else
	{
		movementSpeed = 0;
		lifetime = 150;
	}

	if (shortLifeTime)
	{
		lifetime = 1;
	}

	lifeCounter = 0;
	destroyed = false;
}

void Text::setDestroyed()
{
	destroyed = true;
}

float Text::getMovementSpeed() const
{
	return movementSpeed;
}

bool Text::isDestroyed() const
{
	return destroyed;
}

sf::Text & Text::getText()
{
	return text;
}

std::string Text::getHUDtype() const
{
	return HUDtype;
}

void Text::update(sf::Vector2f pos)
{
	if (!set) setup();

	if (!moving)
	{
		text.setPosition(pos);
	}

	if (staticPosition)
	{
		text.setPosition(position);
	}

	if (lifeCounter >= lifetime)
	{
		destroyed = true;
	}
	lifeCounter++;
}

void Text::updateHUDInformation(sf::Vector2f position, int value, int valueMax)
{
	if (!set) setup();

	text.setPosition(position);

	std::string msg = "";

	if (value == (int)Others::RESET)
	{
		msg = HUDtype;
	}
	else
	{
		msg = (valueMax != (int)Others::RESET) ? (HUDtype + " : " + std::to_string(value) + "/" + std::to_string(valueMax)) : (HUDtype + " " + std::to_string(value));
	}

	if (HUDtype == "MISSION")
	{
		msg = message;
	}
	else if (HUDtype == "PROGRESS")
	{
		msg = std::to_string(value) + "/" + std::to_string(valueMax);
	}

	text.setString(msg);
}

void Text::setup()
{
	font.loadFromFile("../stuff/font.ttf");
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setFont(font);
	text.setFillColor(color);
	text.setCharacterSize(fontSize);
	text.setPosition(position);
	text.setString(message);
	set = true;
}


Text & Text::operator=(Text other)
{
	font = other.font;
	text = other.text;
	text.setFont(font);
	set = other.set;
	destroyed = other.destroyed;
	message = other.message;
	position = other.position;
	color = other.color;
	fontSize = other.fontSize;
	movementSpeed = other.movementSpeed;
	lifetime = other.lifetime;
	lifeCounter = other.lifeCounter;
	moving = other.moving;
	return *this;
}

