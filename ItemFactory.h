#pragma once
#include "Item.h"
#include "File.h"
class Item;

class ItemFactory
{
public:
	ItemFactory() = delete;
	static void makeItem(Item & item);
private:
	static int specifyItemType(std::string itemName);
	enum KeyWords { ID = 0, DMG = 1, ARM = 2, HP = 3, SELL = 4 };
	static void checkKeyWords(size_t * keyWordPositions);
	static int stringToInt(std::string text, size_t startPosition, size_t endPosition);
	static int stringToInt(std::string::iterator start, std::string::iterator end);
};

