#pragma once
#include "Item.h"
#include "Constants.h"
#include "TimeHandler.h"
#include <vector>
#include <string>

class Inventory
{
public:
	Inventory();
	bool addItem(Item &);
	void equipItem(Item &);
	void changeChosenItem();
	void dropItem();
	void destroyItem();
	int getAmountOfItems() const;
	std::vector<Item> & getItems();
	std::vector<Item> & getEquipment();
	bool isItemAvailable(int index) const;
	Item & getChosenItem();
	int getCapacity() const;
	int getAmountEquipped() const;
	int getChosenItemIndex() const;
	void setSwappedItems(bool);
	bool getSwappedItems() const;
	enum EquippedType { WEAPON = 0, SHIELD = 1, HELMET = 2, ARMOR = 3, BOOTS = 4, NECKLACE = 5, RING = 6 };
private:
	std::vector<Item> equipment;
	const int maxEquipped = 7;
	std::vector<Item> items;
	int amountEquipped = 0;
	int capacity = 8;
	void swapItems(int equipIndex, Item &);
	bool swappedItems = false;
	int chosenItemIndex = 0;
	TimeHandler changingItemTime;
};

