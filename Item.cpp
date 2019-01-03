#include "Item.h"

Item::Item(int typee, int amountt) : type(typee), amount(amountt)
{
	collected = readyToPick = false;
	distanceFromPlayer = 1000;
}

void Item::setCollected(bool inp)
{
	collected = inp;
}

void Item::setReadyToPick(bool inp)
{
	readyToPick = inp;
}

void Item::setDistanceFromPlayer(int inp)
{
	distanceFromPlayer = inp;
}

int Item::getType() const
{
	return type;
}

int Item::getAmount() const
{
	return amount;
}

bool Item::isCollected() const
{
	return collected;
}

bool Item::isReadyToPick() const
{
	return readyToPick;
}

int Item::getDistanceFromPlayer() const
{
	return distanceFromPlayer;
}
