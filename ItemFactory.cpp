#include "ItemFactory.h"

void ItemFactory::makeItem(Item & item)
{
	std::vector<std::string> lines(File::getLines("stuff/items/itemStats.txt"));

	bool foundItem = false;

	for (auto line : lines)
	{
		std::string keyWords[5] = { "ID","DMG","ARM","HP","SELL" };
		std::size_t keyWordsPositions[5];
		keyWordsPositions[KeyWord::ID] = line.find(keyWords[KeyWord::ID]);
		keyWordsPositions[KeyWord::DMG] = line.find(keyWords[KeyWord::DMG]);
		keyWordsPositions[KeyWord::ARM] = line.find(keyWords[KeyWord::ARM]);
		keyWordsPositions[KeyWord::HP] = line.find(keyWords[KeyWord::HP]);
		keyWordsPositions[KeyWord::SELL] = line.find(keyWords[KeyWord::SELL]);

		try
		{
			checkKeyWords(keyWordsPositions);
		}
		catch (std::string error)
		{
			std::cerr << error << std::endl;
			break;
		}

		int correctItemID = stringToInt(line, keyWordsPositions[KeyWord::ID] + keyWords[KeyWord::ID].size(), keyWordsPositions[KeyWord::DMG]);
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

		item.setDamage(stringToInt(line, keyWordsPositions[KeyWord::DMG] + keyWords[KeyWord::DMG].size(), keyWordsPositions[KeyWord::ARM]));
		item.setArmor(stringToInt(line, keyWordsPositions[KeyWord::ARM] + keyWords[KeyWord::ARM].size(), keyWordsPositions[KeyWord::HP]));
		item.setRestoringHp(stringToInt(line, keyWordsPositions[KeyWord::HP] + keyWords[KeyWord::HP].size(), keyWordsPositions[KeyWord::SELL]));
		item.setSellValue(stringToInt(line.begin() + keyWordsPositions[KeyWord::SELL] + keyWords[KeyWord::SELL].size(), line.end()));
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
	if (keyWordPositions[KeyWord::ID] == std::string::npos || keyWordPositions[KeyWord::DMG] == std::string::npos ||
		keyWordPositions[KeyWord::ARM] == std::string::npos || keyWordPositions[KeyWord::HP] == std::string::npos ||
		keyWordPositions[KeyWord::SELL] == std::string::npos)
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
