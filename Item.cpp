#include "Item.h"

Item::Item(int idd) : id(idd)
{
	collected = readyToPick = false;
	distanceFromPlayer = 1000;
	ItemFactory::makeItem(*this);
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

std::string Item::getPathName() const
{
	return pathName;
}


//void Item::setStatsByID()
//{
//	std::fstream file("stuff/items/itemStats.txt", std::ios::in);
//	if (!file.is_open()) throw "cant open txt file";
//
//	std::string line = "";
//	while (file.good() && std::getline(file, line))
//	{
//		std::size_t idPosition = line.find("ID");
//		std::size_t damagePosition = line.find("DMG");
//		int possibleID = std::stoi(std::string(line.begin() + idPosition + 2, line.begin() + damagePosition));
//
//		if (possibleID != id) continue;
//
//		std::size_t armorPosition = line.find("ARM");
//		std::size_t hpPosition = line.find("HP");
//		std::size_t sellPosition = line.find("SELL");
//		std::size_t doorPosition = line.find("OPEN");
//
//		if (damagePosition == std::string::npos || armorPosition == std::string::npos || hpPosition == std::string::npos ||
//			sellPosition == std::string::npos || doorPosition == std::string::npos || idPosition == std::string::npos)
//		{
//			throw " error while reading file ";
//		}
//
//		int testType = specifyType(std::string(line.begin(), line.begin() + line.find(":")-4));
//		if (testType != -1) type = testType;
//
//		name = std::string(line.begin(), line.begin() + line.find(":"));
//		pathName = "stuff/items/" + name + ".png";
//
//		damage = std::stoi(std::string(line.begin() + damagePosition + 3, line.begin() + armorPosition));
//		armor = std::stoi(std::string(line.begin() + armorPosition + 3, line.begin() + hpPosition));
//		restoringHp = std::stoi(std::string(line.begin() + hpPosition + 2, line.begin() + sellPosition));
//		sellValue = std::stoi(std::string(line.begin() + sellPosition + 4, line.begin() + doorPosition));
//		break;
//	}
//
//	file.close();
//}



