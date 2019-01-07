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
	bool addItem(Item &);
	void removeItem();
	void update(int actionKey);
	int getAmountOfItems() const;
	std::vector<Item> & getItems();
	bool isItemAvailable(int index) const;
	Item getMarkedItem() const;
	int getCapacity() const;
	int getMarkedItemIndex() const;
private:
	std::vector<Item> items;
	int capacity = 8;
	int markedItemIndex = 0;
	TimeHandler changingItemTime;
};

