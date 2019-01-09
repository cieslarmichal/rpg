#include "Inventory.h"


Inventory::Inventory()
{
	for (int i = 0; i < 7; i++)
	{
		equipment.push_back(Item());
	}
}

Inventory::~Inventory()
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

void Inventory::equipItem(Item & item)
{
	switch (item.getType())
	{
	case Item::Type::DISTANCE_WEAPON:
	case Item::Type::MELEE_WEAPON:
		swapItems(EquippedType::WEAPON, item);
		break;
	case Item::Type::SHIELD:
		swapItems(EquippedType::SHIELD, item);
		break;
	case Item::Type::HELMET:
		swapItems(EquippedType::HELMET, item);
		break;
	case Item::Type::ARMOR:
		swapItems(EquippedType::ARMOR, item);
		break;
	case Item::Type::BOOTS:
		swapItems(EquippedType::BOOTS, item);
		break;
	case Item::Type::NECKLACE:
		swapItems(EquippedType::NECKLACE, item);
		break;
	case Item::Type::RING:
		swapItems(EquippedType::RING, item);
		break;
	}

	for (auto& item : equipment)
	{
		std::cout <<"name = "<<item.getName()<<" id = "<< item.getId()<<std::endl;
	}
}

void Inventory::dropItem()
{
	items[markedItemIndex].setReadyToDrop(true);

	if (markedItemIndex - 1 >= 0)
	{
		markedItemIndex--;
	}
	else
	{
		markedItemIndex = 0;
	}
}

void Inventory::destroyItem()
{
	items[markedItemIndex].setDestroyed(true);
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
		dropItem();
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

std::vector<Item> & Inventory::getEquipment()
{
	return equipment;
}

bool Inventory::isItemAvailable(int index) const
{
	return (index >= 0 && index <= capacity && (int)items.size() > 0 && index < (int)items.size());
}

Item & Inventory::getMarkedItem()
{
	
	return items[markedItemIndex];
}

int Inventory::getCapacity() const
{
	return capacity;
}

int Inventory::getAmountEquipped() const
{
	return amountEquipped;
}

int Inventory::getMarkedItemIndex() const
{
	return markedItemIndex;
}

void Inventory::setSwappedItems(bool inp)
{
	swappedItems = inp;
}

bool Inventory::getSwappedItems() const
{
	return swappedItems;
}

void Inventory::swapItems(int equipIndex, Item & item)
{
	if (equipment[equipIndex].getName() != "")
	{
		std::cout << "SWAPPED" << std::endl;
		Item temp = items[markedItemIndex];
		items[markedItemIndex] = equipment[EquippedType::WEAPON];
		swappedItems = true;
		equipment[equipIndex] = temp;
	}
	else
	{
		equipment[equipIndex] = item;
		destroyItem();
		swappedItems = false;
		amountEquipped++;
	}
}
