#include "Inventory.h"


Inventory::Inventory()
{
}

void Inventory::addItem(Item & item)
{
	items.push_back(item);
}
