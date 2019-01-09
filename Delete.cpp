#include "Delete.h"

void Delete::removeEnemies(enemyPair & enemies)
{
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](std::pair<std::unique_ptr<Wrapper>, StatusBar> & e) {return e.first->rect->character->isDead(); }), enemies.end());
}

void Delete::removeText(std::vector < std::unique_ptr<Text>> & texts)
{
	texts.erase(std::remove_if(texts.begin(), texts.end(), [](std::unique_ptr<Text> & t) {return t->isDestroyed(); }), texts.end());
}

void Delete::removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](std::unique_ptr<Wrapper> & p) {return p->rect->projectile->isDestroyed(); }), projectiles.end());
}

void Delete::removeItems(std::vector<std::unique_ptr<Wrapper>> & items)
{
	items.erase(std::remove_if(items.begin(), items.end(), [](std::unique_ptr<Wrapper> & it) {return it->rect->item->isDestroyed(); }), items.end());
}

void Delete::removeAndAddItems(std::vector<Item> & inventoryItems, std::vector<std::unique_ptr<Wrapper>>& globalItems, sf::Vector2f playerPosition)
{
	for (auto & inventoryItem : inventoryItems)
	{
		if (inventoryItem.isReadyToDrop())
		{
			inventoryItem.setReadyToDrop(false);
			Create::createItem(inventoryItem, globalItems, playerPosition);
			inventoryItem.setReadyToDrop(true);
		}
	}
	inventoryItems.erase(std::remove_if(inventoryItems.begin(), inventoryItems.end(), [](auto & item) {return item.isReadyToDrop(); }), inventoryItems.end());
	inventoryItems.erase(std::remove_if(inventoryItems.begin(), inventoryItems.end(), [](auto & item) {return item.isDestroyed(); }), inventoryItems.end());
}

void Delete::removeBlocked(std::vector<Blocked> & blockedCharacters)
{
	blockedCharacters.erase(std::remove_if(blockedCharacters.begin(), blockedCharacters.end(), [](const Blocked & blocked) {return blocked.isDestroyed(); }), blockedCharacters.end());
}

void Delete::setCharacterDead(std::unique_ptr<Wrapper> & character)
{
	character->rect->character->setDead(true);
}

void Delete::setProjectileToDestroy(std::unique_ptr<Wrapper> & projectile)
{
	projectile->rect->projectile->setDestroyed(true);
}

void Delete::setItemToDestroy(std::unique_ptr<Wrapper> & item)
{
	item->rect->item->setDestroyed(true);
}

void Delete::setBlockedToDestroy(Blocked & blocked)
{
	blocked.setDestroyed(true);
}
