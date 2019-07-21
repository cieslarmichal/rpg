#include "Inventory.h"


Inventory::Inventory()
{
	for (int i = 0; i < maxEquipped; i++)
	{
		equipment.push_back(Item());
	}

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
}

void Inventory::changeChosenItem()
{
	if (chosenItemIndex < (int)items.size() - 1)
	{
		chosenItemIndex++;
	}
	else
	{
		chosenItemIndex = 0;
	}
}

void Inventory::dropItem()
{
	if ((int)items.size() == 0) return;

	items[chosenItemIndex].setReadyToDrop(true);

	if (chosenItemIndex - 1 >= 0)
	{
		chosenItemIndex--;
	}
	else
	{
		chosenItemIndex = 0;
	}
}

void Inventory::destroyItem()
{
	if ((int)items.size() == 0) return;

	items[chosenItemIndex].setDestroyed(true);
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

Item & Inventory::getChosenItem()
{

	return items[chosenItemIndex];
}

int Inventory::getCapacity() const
{
	return capacity;
}

int Inventory::getAmountEquipped() const
{
	return amountEquipped;
}

int Inventory::getChosenItemIndex() const
{
	return chosenItemIndex;
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
		Item temp = items[chosenItemIndex];
		items[chosenItemIndex] = equipment[equipIndex];
		equipment[equipIndex] = temp;
		swappedItems = true;
	}
	else
	{
		equipment[equipIndex] = item;
		destroyItem();
		amountEquipped++;
	}
}

