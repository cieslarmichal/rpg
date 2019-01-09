#include "Update.h"

void Update::updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications)
{
	bool isMoving = Movement::movePlayer(*player->rect, direction);
	if (isMoving) player->animation->update(player->rect->character->getDirection());
	player->sprite->setPosition(player->rect->getPosition());
	statBar.updateStatusBar(player);
	player->rect->setEdges();

	player->rect->player->getInventory().update(action);
	player->rect->player->useItem(action);
	ChangeWeapon::changeWeapon(action, player);
	std::string levelMessage = LevelManager::update(player->rect->player);
	Create::createLevelMessage(levelMessage, notifications);
}

void Update::updateEnemies(enemyPair & enemies, std::unique_ptr<Wrapper> & player)
{
	for (auto & enemy : enemies)
	{
		bool isMoving = Movement::moveEnemy(*enemy.first->rect, *player->rect);
		if (isMoving) enemy.first->animation->update(enemy.first->rect->character->getDirection());
		enemy.first->sprite->setPosition(enemy.first->rect->getPosition());
		enemy.second.updateStatusBar(enemy.first);
		enemy.first->rect->setEdges();
	}
}

void Update::updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & obstacle : obstacles)
	{
		obstacle->sprite->setPosition(obstacle->rect->getPosition());
	}
}

void Update::updateItems(std::vector<std::unique_ptr<Wrapper>> & items)
{
	for (auto & item : items)
	{
		item->sprite->setPosition(item->rect->getPosition());
	}
}

void Update::updateText(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & texts)
{
	for (auto & text : texts)
	{
		Movement::moveText(*text);
		sf::Vector2f position = sf::Vector2f(player->rect->getPosition().x - 150, player->rect->getPosition().y - 120);
		text->update(position);
	}
}

void Update::updateHUD(std::unique_ptr<Wrapper> & player, std::vector <std::unique_ptr<Text>> & texts,std::vector<std::unique_ptr<Wrapper>> & HUDInventory,
	std::vector<std::unique_ptr<Rect>> & HUDInventorySlots, std::vector<std::unique_ptr<Wrapper>> & HUDEquipment, sf::Vector2u windowSize)
{
	updateHUDInfo(player, texts, windowSize);
	updateHUDSlots(player, HUDInventorySlots, windowSize);
	updateHUDInventory(player, HUDInventory, windowSize);
	updateHUDEquipment(player, HUDEquipment, windowSize);
}

void Update::updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies)
{
	for (auto & projectile : projectiles)
	{
		Movement::moveProjectile(*projectile->rect, enemies);
		projectile->sprite->setPosition((int)projectile->rect->getPosition().x - 10, (int)projectile->rect->getPosition().y - 15);
	}
}

void Update::updateHUDInfo(std::unique_ptr<Wrapper> & player, std::vector <std::unique_ptr<Text>> & texts, sf::Vector2u windowSize)
{
	for (auto & text : texts)
	{
		if (text->getHUDtype() == "HP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2);
			text->updateHUD(HUDposition, player->rect->player->getCurrentHp(), player->rect->player->getMaxHp());
		}
		else if (text->getHUDtype() == "EXP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 20);
			text->updateHUD(HUDposition, player->rect->player->getExperience(), LevelManager::getRequireExperience());
		}
		else if (text->getHUDtype() == "COINS")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 40);
			text->updateHUD(HUDposition, player->rect->player->getCoins());
		}
	}
}

void Update::updateHUDSlots(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Rect>> & HUDInventorySlots, sf::Vector2u windowSize)
{
	int slotCounter = 0;
	int offX = 0, offY = 0;
	for (auto & slot : HUDInventorySlots)
	{
		sf::Vector2f HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offX * 16 + 5,
			player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offY * 16);
		slot->getRect().setPosition(HUDInventoryPosition);
		offX++;
		if (offX == 4)
		{
			offX = 0;
			offY++;
		}

		slotCounter++;
		if (slotCounter == 8) break;
	}

	//helmet
	sf::Vector2f HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 30,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 120);
	HUDInventorySlots[8]->getRect().setPosition(HUDInventoryPosition);

	//necklace
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 10,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 120);
	HUDInventorySlots[9]->getRect().setPosition(HUDInventoryPosition);

	//armor
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 30,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 140);
	HUDInventorySlots[10]->getRect().setPosition(HUDInventoryPosition);

	//shield
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 50,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 140);
	HUDInventorySlots[11]->getRect().setPosition(HUDInventoryPosition);

	//weapon
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 10,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 140);
	HUDInventorySlots[12]->getRect().setPosition(HUDInventoryPosition);

	//boots
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 30,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 160);
	HUDInventorySlots[13]->getRect().setPosition(HUDInventoryPosition);

	//ring
	HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 10,
		player->rect->getPosition().y - (float)windowSize.y / 2 + 160);
	HUDInventorySlots[14]->getRect().setPosition(HUDInventoryPosition);


}

void Update::updateHUDInventory(std::unique_ptr<Wrapper>& player, std::vector<std::unique_ptr<Wrapper>>& HUDInventory, sf::Vector2u windowSize)
{

	if (player->rect->player->getInventory().getAmountOfItems() != (int)HUDInventory.size() || player->rect->player->getInventory().getSwappedItems())
	{
		player->rect->player->getInventory().setSwappedItems(false);
		HUDInventory.clear();
		int offX = 0, offY = 0;
		for (auto & item : player->rect->player->getInventory().getItems())
		{
			sf::Vector2f HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offX * 16 + 5,
				player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offY * 16);
			Create::createItem(item, HUDInventory, HUDInventoryPosition);
			offX++;
			if (offX == 4)
			{
				offX = 0;
				offY++;
			}
		}
	}
	else
	{
		int offX = 0, offY = 0, itemIndex = 0;
		for (auto & item : HUDInventory)
		{
			if (itemIndex == player->rect->player->getInventory().getMarkedItemIndex())
			{
				item->rect->getRect().setFillColor(sf::Color::Red);
			}
			else
			{
				item->rect->getRect().setFillColor(sf::Color(181, 155, 124, 255));
			}
			sf::Vector2f HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + offX * 16 + 5,
				player->rect->getPosition().y - (float)windowSize.y / 2 + 200 + offY * 16);
			item->rect->getRect().setPosition(HUDInventoryPosition);
			item->sprite->setPosition(HUDInventoryPosition);
			offX++;
			if (offX == 4)
			{
				offX = 0;
				offY++;
			}
			itemIndex++;
		}
	}
}

void Update::updateHUDEquipment(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & HUDEquipment, sf::Vector2u windowSize)
{
	//if (player->rect->player->getInventory().getAmountEquipped() != (int)HUDEquipment.size() || player->rect->player->getInventory().getSwappedItems())
	//{
		//player->rect->player->getInventory().setSwappedItems(false);
	HUDEquipment.clear();
		
		if (player->rect->player->getInventory().getEquipment()[Inventory::EquippedType::WEAPON].getName() != "")
		{
			sf::Vector2f HUDInventoryPosition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2 + 10,
				player->rect->getPosition().y - (float)windowSize.y / 2 + 140);
			Create::createItem(player->rect->player->getInventory().getEquipment()[Inventory::EquippedType::WEAPON], HUDEquipment, HUDInventoryPosition);
			HUDEquipment[0]->rect->getRect().setPosition(HUDInventoryPosition);
			HUDEquipment[0]->sprite->setPosition(HUDInventoryPosition);

		}

	//}
}

