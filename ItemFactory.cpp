#include "ItemFactory.h"

void ItemFactory::makeItem(Item & item)
{
	std::vector<std::string> lines(File::getLines("stuff/items/itemStats.txt"));

	bool foundItem = false;

	for (auto line : lines)
	{
		std::size_t keyWordsPositions[5];
		keyWordsPositions[KeyWords::ID] = line.find("ID");
		keyWordsPositions[KeyWords::DMG] = line.find("DMG");
		keyWordsPositions[KeyWords::ARM] = line.find("ARM");
		keyWordsPositions[KeyWords::HP] = line.find("HP");
		keyWordsPositions[KeyWords::SELL] = line.find("SELL");

		try
		{
			checkKeyWords(keyWordsPositions);
		}
		catch (std::string error)
		{
			std::cerr << error << std::endl;
			break;
		}

		int correctItemID = stringToInt(line, keyWordsPositions[KeyWords::ID] + 2, keyWordsPositions[KeyWords::DMG]);
		if (correctItemID != item.getId()) continue;

		foundItem = true;

		item.setName(std::string(line.begin(), line.begin() + line.find(":")));
		item.setPathName("stuff/items/" + item.getName() + ".png");

		try
		{
			item.setType(specifyItemType(item.getName()));
		}
		catch (std::string error)
		{
			std::cerr << error << std::endl;
			break;
		}

		item.setDamage(stringToInt(line, keyWordsPositions[KeyWords::DMG] + 3, keyWordsPositions[KeyWords::ARM]));
		item.setArmor(stringToInt(line, keyWordsPositions[KeyWords::ARM] + 3, keyWordsPositions[KeyWords::HP]));
		item.setRestoringHp(stringToInt(line, keyWordsPositions[KeyWords::HP] + 2, keyWordsPositions[KeyWords::SELL]));
		item.setSellValue(stringToInt(line.begin() + keyWordsPositions[KeyWords::SELL] + 4, line.end()));
		break;
	}

	if (!foundItem)
	{
		std::cerr << "item " << item.getName() << " with ID = " << item.getId() << " not found" << std::endl;
	}
}

int ItemFactory::specifyItemType(std::string itemName)
{
	if (itemName.size() < 5) throw ("incorrect item name, name = " + itemName);

	int endTypePosition = 0;
	for (auto charName : itemName)
	{
		if (charName == '_')
		{
			break;
		}
		endTypePosition++;
	}

	std::string type(itemName.begin(), itemName.begin() + endTypePosition);

	if (type == "melee")
	{
		return Item::Type::MELEE_WEAPON;
	}
	else if (type == "distance")
	{
		return Item::Type::DISTANCE_WEAPON;
	}
	else if (type == "shield")
	{
		return Item::Type::SHIELD;
	}
	else if (type == "necklace")
	{
		return Item::Type::NECKLACE;
	}
	else if (type == "ring")
	{
		return Item::Type::RING;
	}
	else if (type == "helmet")
	{
		return Item::Type::HELMET;
	}
	else if (type == "boots")
	{
		return Item::Type::BOOTS;
	}
	else if (type == "armor")
	{
		return Item::Type::ARMOR;
	}
	else if (type == "gloves")
	{
		return Item::Type::GLOVES;
	}
	else if (type == "food")
	{
		return Item::Type::FOOD;
	}
	else if (type == "coin")
	{
		return Item::Type::COIN;
	}
	else if (type == "potion")
	{
		return Item::Type::HEALTH_POTION;
	}

	throw ("no suitable type for this item, item name = " + type);
	return -1;
}

void ItemFactory::checkKeyWords(size_t * keyWordPositions)
{
	if (keyWordPositions[KeyWords::ID] == std::string::npos || keyWordPositions[KeyWords::DMG] == std::string::npos ||
		keyWordPositions[KeyWords::ARM] == std::string::npos || keyWordPositions[KeyWords::HP] == std::string::npos ||
		keyWordPositions[KeyWords::SELL] == std::string::npos)
	{
		throw ("ID, DMG, ARM, HP or SELL words not found in file: \"stuff/items/itemStats.txt\"");
	}
}

int ItemFactory::stringToInt(std::string text, size_t startPosition, size_t endPosition)
{
	return std::stoi(std::string(text.begin() + startPosition, text.begin() + endPosition));
}

int ItemFactory::stringToInt(std::string::iterator start, std::string::iterator end)
{
	return std::stoi(std::string(start, end));
}
