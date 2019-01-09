#include "Item.h"

Item::Item(int idd) : id(idd)
{
	destroyed = readyToPick = false;
	distanceFromPlayer = 1000;
	ItemFactory::makeItem(*this);
}

Item::Item()
{
	name = "";
}

Item & Item::operator=(Item other)
{
	this->name = other.name;
	this->pathName = other.pathName;
	this->id = other.id;
	this->type = other.type;
	this->damage = other.damage;
	this->armor = other.armor;
	this->restoringHp = other.restoringHp;
	this->sellValue = other.sellValue;
	this->destroyed = other.destroyed;
	this->readyToDrop = other.readyToDrop;
	this->readyToPick = other.readyToPick;
	this->distanceFromPlayer = other.distanceFromPlayer;

	return *this;
}

void Item::setName(std::string inp)
{
	name = inp;
}

void Item::setPathName(std::string inp)
{
	pathName = inp;
}

void Item::setId(int inp)
{
	id = inp;
}

void Item::setType(int inp)
{
	type = inp;
}

void Item::setDamage(int inp)
{
	damage = inp;
}

void Item::setArmor(int inp)
{
	armor = inp;
}

void Item::setRestoringHp(int inp)
{
	restoringHp = inp;
}

void Item::setSellValue(int inp)
{
	sellValue = inp;
}

void Item::setDestroyed(bool inp)
{
	destroyed = inp;
}

void Item::setReadyToPick(bool inp)
{
	readyToPick = inp;
}

void Item::setReadyToDrop(bool inp)
{
	readyToDrop = inp;
}

void Item::setDistanceFromPlayer(int inp)
{
	distanceFromPlayer = inp;
}

std::string Item::getName() const
{
	return name;
}

int Item::getId() const
{
	return id;
}

int Item::getType() const
{
	return type;
}

int Item::getDamage() const
{
	return damage;
}

int Item::getArmor() const
{
	return armor;
}

int Item::getRestoringHp() const
{
	return restoringHp;
}

int Item::getSellValue() const
{
	return sellValue;
}

bool Item::isDestroyed() const
{
	return destroyed;
}

bool Item::isReadyToPick() const
{
	return readyToPick;
}

bool Item::isReadyToDrop() const
{
	return readyToDrop;
}

int Item::getDistanceFromPlayer() const
{
	return distanceFromPlayer;
}

std::string Item::getPathName() const
{
	return pathName;
}

