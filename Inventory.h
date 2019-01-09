#pragma once
#include "Item.h"
#include <string>
#include <vector>
#include "Directions.h"
#include "TimeHandler.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
	bool addItem(Item &);
	void equipItem(Item &);
	void dropItem();
	void destroyItem();
	void update(int actionKey);
	int getAmountOfItems() const;
	std::vector<Item> & getItems();
	std::vector<Item> & getEquipment();
	bool isItemAvailable(int index) const;
	Item & getMarkedItem();
	int getCapacity() const;
	int getAmountEquipped() const;
	int getMarkedItemIndex() const;
	void setSwappedItems(bool);
	bool getSwappedItems() const;
	enum EquippedType { WEAPON = 0, SHIELD = 1, HELMET = 2, ARMOR = 3, BOOTS = 4, NECKLACE = 5, RING = 6 };
private:
	std::vector<Item> equipment;
	const int maxEquipped = 7;
	int amountEquipped = 0;
	std::vector<Item> items;
	int capacity = 8;
	void swapItems(int equipIndex, Item &);
	bool swappedItems = false;
	int markedItemIndex = 0;
	TimeHandler changingItemTime;
};

