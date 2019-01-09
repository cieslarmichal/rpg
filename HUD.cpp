#include "HUD.h"



HUD::HUD()
{
	equipmentPositions[Inventory::EquippedType::WEAPON] = sf::Vector2i(10, 140);
	equipmentPositions[Inventory::EquippedType::SHIELD] = sf::Vector2i(50, 140);
	equipmentPositions[Inventory::EquippedType::HELMET] = sf::Vector2i(30, 120);
	equipmentPositions[Inventory::EquippedType::ARMOR] = sf::Vector2i(30, 140);
	equipmentPositions[Inventory::EquippedType::BOOTS] = sf::Vector2i(30, 160);
	equipmentPositions[Inventory::EquippedType::NECKLACE] = sf::Vector2i(10, 120);
	equipmentPositions[Inventory::EquippedType::RING] = sf::Vector2i(10, 160);
}

void HUD::update(std::unique_ptr<Wrapper>& player, sf::Vector2u windowSize)
{
	updateInformations(player, windowSize);
	updateSlots(player, windowSize);
	updateInventory(player, windowSize);
	updateEquipment(player, windowSize);
}

void HUD::updateInformations(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize)
{
	for (auto & info : informations)
	{
		if (info->getHUDtype() == "HP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2);
			info->updateHUDInformation(HUDposition, player->rect->player->getCurrentHp(), player->rect->player->getMaxHp());
		}
		else if (info->getHUDtype() == "EXP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 20);
			info->updateHUDInformation(HUDposition, player->rect->player->getExperience(), LevelManager::getRequireExperience());
		}
		else if (info->getHUDtype() == "COINS")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 40);
			info->updateHUDInformation(HUDposition, player->rect->player->getCoins());
		}
	}
}

void HUD::updateSlots(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize)
{
	updateInventorySlots(player, windowSize);
	updateEquipmentSlots(player, windowSize);
}

void HUD::updateInventorySlots(std::unique_ptr<Wrapper>& player, sf::Vector2u windowSize)
{
	int slotCounter = 0;
	int offsetX = 0, offsetY = 0;
	for (auto & slot : inventorySlots)
	{
		sf::Vector2f slotPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offsetX * 16 + 5,
			player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offsetY * 16);
		slot->getRect().setPosition(slotPosition);

		offsetX++;
		if (offsetX == 4)
		{
			offsetX = 0;
			offsetY++;
		}

		slotCounter++;
		if (slotCounter == 8) break;
	}
}

void HUD::updateEquipmentSlots(std::unique_ptr<Wrapper>& player, sf::Vector2u windowSize)
{
	int eqPositionIndex = 0;
	for (int slotIndex = 8; slotIndex <= 14; slotIndex++, eqPositionIndex++)
	{
		sf::Vector2f slotPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + equipmentPositions[eqPositionIndex].x,
			player->rect->getPosition().y - (float)windowSize.y / 2 + equipmentPositions[eqPositionIndex].y);
		inventorySlots[slotIndex]->getRect().setPosition(slotPosition);
	}
}

void HUD::updateInventory(std::unique_ptr<Wrapper>& player, sf::Vector2u windowSize)
{
	//if something changed 
	if (player->rect->player->getInventory().getAmountOfItems() != (int)inventory.size() || player->rect->player->getInventory().getSwappedItems())
	{
		inventory.clear();

		int offsetX = 0, offsetY = 0;
		for (auto & item : player->rect->player->getInventory().getItems())
		{
			sf::Vector2f inventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offsetX * 16 + 5,
				player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offsetY * 16);
			Create::createItem(item, inventory, inventoryPosition);
			offsetX++;
			if (offsetX == 4)
			{
				offsetX = 0;
				offsetY++;
			}
		}
	}
	else //no changes, just update positions
	{
		int offsetX = 0, offsetY = 0, itemIndex = 0;
		for (auto & item : inventory)
		{
			if (itemIndex == player->rect->player->getInventory().getChosenItemIndex())
			{
				item->rect->getRect().setFillColor(sf::Color::Red);
			}
			else
			{
				item->rect->getRect().setFillColor(sf::Color(181, 155, 124, 255));
			}
			sf::Vector2f inventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offsetX * 16 + 5,
				player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offsetY * 16);
			item->rect->getRect().setPosition(inventoryPosition);
			item->sprite->setPosition(inventoryPosition);
			offsetX++;
			if (offsetX == 4)
			{
				offsetX = 0;
				offsetY++;
			}
			itemIndex++;
		}
	}
}

void HUD::updateEquipment(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize)
{
	//if something changed
	//std::cout << player->rect->player->getInventory().getSwappedItems() << std::endl;
	if (player->rect->player->getInventory().getAmountEquipped() != (int)equipment.size() || player->rect->player->getInventory().getSwappedItems())
	{
		std::cout << "in" << std::endl;
		player->rect->player->getInventory().setSwappedItems(false);
		equipment.clear();

		int hudEqIndex = 0;
		for (auto & item : player->rect->player->getInventory().getEquipment())
		{
			if (item.getName() == "")
			{
				hudEqIndex++;
				continue;
			}

			sf::Vector2f eqPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + equipmentPositions[hudEqIndex].x,
				player->rect->getPosition().y - (float)windowSize.y / 2 + equipmentPositions[hudEqIndex].y);
			Create::createItem(item, equipment, eqPosition);

			hudEqIndex++;
		}
	}
	else //not changed, just update position
	{
		for (auto & item : equipment)
		{
			sf::Vector2i eqOffset = calculateEqPosition(item->rect->item->getType());
			sf::Vector2f inventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + eqOffset.x,
				player->rect->getPosition().y - (float)windowSize.y / 2 + eqOffset.y);
			item->rect->getRect().setPosition(inventoryPosition);
			item->sprite->setPosition(inventoryPosition);
		}
	}
}

sf::Vector2i HUD::calculateEqPosition(int itemType)
{
	sf::Vector2i offset;

	switch (itemType)
	{
	case Item::Type::DISTANCE_WEAPON:
	case Item::Type::MELEE_WEAPON:
		offset = equipmentPositions[Inventory::EquippedType::WEAPON];
		break;
	case Item::Type::SHIELD:
		offset = equipmentPositions[Inventory::EquippedType::SHIELD];
		break;
	case Item::Type::HELMET:
		offset = equipmentPositions[Inventory::EquippedType::HELMET];
		break;
	case Item::Type::ARMOR:
		offset = equipmentPositions[Inventory::EquippedType::ARMOR];
		break;
	case Item::Type::BOOTS:
		offset = equipmentPositions[Inventory::EquippedType::BOOTS];
		break;
	case Item::Type::NECKLACE:
		offset = equipmentPositions[Inventory::EquippedType::NECKLACE];
		break;
	case Item::Type::RING:
		offset = equipmentPositions[Inventory::EquippedType::RING];
		break;
	}

	return offset;
}
