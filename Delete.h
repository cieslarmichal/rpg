#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "Blocked.h"
#include "Create.h"
#include "EnemySpawner.h"

using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, StatusBar>>;


class Delete
{
public:
	Delete() = delete;
	static void removeEnemies(vectorOfCharacters & characters);
	static void removeText(std::vector < std::unique_ptr<Text>> & texts);
	static void removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles);
	static void removeItems(std::vector<std::unique_ptr<Wrapper>> & items);
	static void removeAndAddItems(std::vector<Item> & inventoryItems, std::vector<std::unique_ptr<Wrapper>> & globalItems, sf::Vector2f playerPosition);
	static void removeBlocked(std::vector<Blocked> & blockedCharacters);
	static void setCharacterDead(std::unique_ptr<Wrapper> & character);
	static void setProjectileToDestroy(std::unique_ptr<Wrapper> & projectile);
	static void setItemToDestroy(std::unique_ptr<Wrapper> & item);
	static void setBlockedToDestroy(Blocked & blocked);
};
