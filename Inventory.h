#pragma once
#include "Item.h"
#include <string>
#include <vector>

class Inventory
{
public:
	Inventory();
	void addItem(Item &);
	//void removeItem();
private:
	std::vector<Item> items;
};

