#include "Item.h"

Item::Item(int typee, int which) : type(typee), whichInOrder(which)
{
	try
	{
		setPathName(type, whichInOrder);
		setStats();
	}
	catch (const char * error)
	{
		std::cerr << error << std::endl;
	}
	collected = readyToPick = false;
	distanceFromPlayer = 1000;
}

Item::Item(int idd) : id(idd)
{
	try
	{
		setStatsByID();
	}
	catch (const char * error)
	{
		std::cerr << error << std::endl;
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl;
	}
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

int Item::getAmountRestoringHp() const
{
	return amountRestoringHp;
}

int Item::getSellValue() const
{
	return sellValue;
}

bool Item::getOpensDoor() const
{
	return opensDoor;
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

void Item::setPathName(int type, int which)
{
	pathName = "stuff/items/";
	switch (type)
	{
	case Type::MELEE_WEAPON:
		if (which == WhichInOrder::FIRST) name = "melee__00";
		else if (which == WhichInOrder::SECOND) name = "melee__01";
		else if (which == WhichInOrder::THIRD) name = "melee__02";
		else if (which == WhichInOrder::FOURTH) name = "melee__03";
		break;
	case Type::DISTANCE_WEAPON:
		if (which == WhichInOrder::FIRST) name = "distance__00";
		break;
	case Type::SHIELD:
		if (which == WhichInOrder::FIRST) name = "shield__00";
		break;
	case Type::NECKLACE:
		if (which == WhichInOrder::FIRST) name = "neclance__00";
		else if (which == WhichInOrder::SECOND) name = "neclance__01";
		break;
	case Type::RING:
		if (which == WhichInOrder::FIRST) name = "ring__00";
		else if (which == WhichInOrder::SECOND) name = "ring__01";
		break;
	case Type::HELMET:
		if (which == WhichInOrder::FIRST) name = "helmet__00";
		else if (which == WhichInOrder::SECOND) name = "helmet__01";
		break;
	case Type::BOOTS:
		if (which == WhichInOrder::FIRST) name = "boots__00";
		else if (which == WhichInOrder::SECOND) name = "boots__01";
		break;
	case Type::ARMOR:
		if (which == WhichInOrder::FIRST) name = "armor__00";
		else if (which == WhichInOrder::SECOND) name = "armor__01";
		break;
	case Type::GLOVES:
		if (which == WhichInOrder::FIRST) name = "gloves__00";
		else if (which == WhichInOrder::SECOND) name = "gloves__01";
		break;
	case Type::FOOD:
		if (which == WhichInOrder::FIRST) name = "food__00";
		else if (which == WhichInOrder::SECOND) name = "food__01";
		else if (which == WhichInOrder::THIRD) name = "food__02";
		else if (which == WhichInOrder::FOURTH) name = "food__03";
		break;
	case Type::COIN:
		if (which == WhichInOrder::FIRST) name = "coin__00";
		break;
	case Type::HEALTH_POTION:
		if (which == WhichInOrder::FIRST) name = "potion__00";
		break;
	case Type::KEY:
		if (which == WhichInOrder::FIRST) name = "key__00";
		break;
	}
	pathName += name + ".png";
	if (pathName == "stuff/items/.png") throw "invalid item type";
}

void Item::setStats()
{
	std::fstream file("stuff/items/itemStats.txt", std::ios::in);
	if (!file.is_open()) throw "cant open txt file";

	std::string line = "";
	while (file.good() && std::getline(file, line))
	{
		if (line.find(name) == std::string::npos)
		{
			continue;
		}

		std::size_t idPosition = line.find("ID");
		std::size_t damagePosition = line.find("DMG");
		std::size_t armorPosition = line.find("ARM");
		std::size_t hpPosition = line.find("HP");
		std::size_t sellPosition = line.find("SELL");
		std::size_t doorPosition = line.find("OPEN");

		if (damagePosition == std::string::npos || armorPosition == std::string::npos || hpPosition == std::string::npos ||
			sellPosition == std::string::npos || doorPosition == std::string::npos || idPosition == std::string::npos)
		{
			throw " error while reading file ";
		}

		id = std::stoi(std::string(line.begin() + idPosition + 2, line.begin() + damagePosition));
		damage = std::stoi(std::string(line.begin() + damagePosition + 3, line.begin() + armorPosition));
		armor = std::stoi(std::string(line.begin() + armorPosition + 3, line.begin() + hpPosition));
		amountRestoringHp = std::stoi(std::string(line.begin() + hpPosition + 2, line.begin() + sellPosition));
		sellValue = std::stoi(std::string(line.begin() + sellPosition + 4, line.begin() + doorPosition));
		opensDoor = std::stoi(std::string(line.begin() + doorPosition + 4, line.end()));
		break;
	}

	file.close();
}

void Item::setStatsByID()
{
	std::fstream file("stuff/items/itemStats.txt", std::ios::in);
	if (!file.is_open()) throw "cant open txt file";

	std::string line = "";
	while (file.good() && std::getline(file, line))
	{
		std::size_t idPosition = line.find("ID");
		std::size_t damagePosition = line.find("DMG");
		int possibleID = std::stoi(std::string(line.begin() + idPosition + 2, line.begin() + damagePosition));

		if (possibleID != id) continue;

		std::size_t armorPosition = line.find("ARM");
		std::size_t hpPosition = line.find("HP");
		std::size_t sellPosition = line.find("SELL");
		std::size_t doorPosition = line.find("OPEN");

		if (damagePosition == std::string::npos || armorPosition == std::string::npos || hpPosition == std::string::npos ||
			sellPosition == std::string::npos || doorPosition == std::string::npos || idPosition == std::string::npos)
		{
			throw " error while reading file ";
		}

		int testType = specifyType(std::string(line.begin(), line.begin() + line.find(":")-4));
		if (testType != -1) type = testType;

		int testWhich = specifyWhichInOrder(std::string(line.begin()+line.find(":")-1, line.begin() + line.find(":")));
		if (testWhich != -1) whichInOrder = testWhich;

		name = std::string(line.begin(), line.begin() + line.find(":"));
		pathName = "stuff/items/" + name + ".png";

		damage = std::stoi(std::string(line.begin() + damagePosition + 3, line.begin() + armorPosition));
		armor = std::stoi(std::string(line.begin() + armorPosition + 3, line.begin() + hpPosition));
		amountRestoringHp = std::stoi(std::string(line.begin() + hpPosition + 2, line.begin() + sellPosition));
		sellValue = std::stoi(std::string(line.begin() + sellPosition + 4, line.begin() + doorPosition));
		opensDoor = std::stoi(std::string(line.begin() + doorPosition + 4, line.end()));
		break;
	}

	file.close();
}

int Item::specifyType(std::string pType)
{
	if (pType == "melee")
	{
		return Type::MELEE_WEAPON;
	}
	else if (pType == "distance")
	{
		return Type::DISTANCE_WEAPON;
	}
	else if (pType == "shield")
	{
		return Type::SHIELD;
	}
	else if (pType == "necklace")
	{
		return Type::NECKLACE;
	}
	else if (pType == "ring")
	{
		return Type::RING;
	}
	else if (pType == "helmet")
	{
		return Type::HELMET;
	}
	else if (pType == "boots")
	{
		return Type::BOOTS;
	}
	else if (pType == "armor")
	{
		return Type::ARMOR;
	}
	else if (pType == "gloves")
	{
		return Type::GLOVES;
	}
	else if (pType == "food")
	{
		return Type::FOOD;
	}
	else if (pType == "coin")
	{
		return Type::COIN;
	}
	else if (pType == "potion")
	{
		return Type::HEALTH_POTION;
	}
	else if (pType == "key")
	{
		return Type::KEY;
	}

	std::string errorMsg = "no suitable type for this item, item name = " + pType;
	throw errorMsg;
	return -1;
}

int Item::specifyWhichInOrder(std::string pWhich)
{
	int testWhich = std::stoi(pWhich);
	if (testWhich < 0 || testWhich>3) throw "whichInOrder<0 || whichOrder>3";
	return testWhich;
}
