#include "Inventory.h"


Inventory::Inventory()
{
}

bool Inventory::addItem(Item & item)
{
	if ((int)items.size() != capacity)
	{
		items.push_back(item);
		return true;
	}
	return false;
}

void Inventory::removeItem()
{
	items[markedItemIndex].setCollected(true);

	if (markedItemIndex - 1 >= 0)
	{
		markedItemIndex--;
	}
	else
	{
		markedItemIndex = 0;
	}
}

void Inventory::update(int actionKey)
{
	if (actionKey == (int)InputKeys::TAB && changingItemTime.getElapsedSeconds() > 0.2)
	{
		changingItemTime.reset();
		if (markedItemIndex < (int)items.size() - 1)
		{
			markedItemIndex++;
		}
		else
		{
			markedItemIndex = 0;
		}
	}
	else if (actionKey == (int)InputKeys::X && changingItemTime.getElapsedSeconds() > 1 && (int)items.size() > 0)
	{
		changingItemTime.reset();
		removeItem();
	}
}

int Inventory::getAmountOfItems() const
{
	return (int)items.size();
}

std::vector<Item>& Inventory::getItems()
{
	return items;
}

bool Inventory::isItemAvailable(int index) const
{
	return (index >= 0 && index <= capacity && (int)items.size() > 0 && index < (int)items.size());
}

Item Inventory::getMarkedItem() const
{
	return items[markedItemIndex];
}

int Inventory::getCapacity() const
{
	return capacity;
}

int Inventory::getMarkedItemIndex() const
{
	return markedItemIndex;
}
