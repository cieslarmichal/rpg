#pragma once
#include "Movement.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "ChangeWeapon.h"
#include "LevelManager.h"
#include "Create.h"
#include "Inventory.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Update
{
public:
	Update() = delete;
	static void updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications);
	static void updateEnemies(enemyPair & enemies, std::unique_ptr<Wrapper> & player);
	static void updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles);
	static void updateItems(std::vector<std::unique_ptr<Wrapper>> & items);
	static void updateText(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & text);
	static void updateHUD(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & HUDInfo, std::vector<std::unique_ptr<Wrapper>> & HUDInventory,
		std::vector<std::unique_ptr<Rect>> & HUDInventorySlots, std::vector<std::unique_ptr<Wrapper>> & HUDEquipment, sf::Vector2u windowSize);
	static void updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies);
private:
	static void updateHUDInfo(std::unique_ptr<Wrapper> & player, std::vector <std::unique_ptr<Text>> & texts, sf::Vector2u windowSize);
	static void updateHUDSlots(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Rect>> & HUDInventorySlots, sf::Vector2u windowSize);
	static void updateHUDInventory(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & HUDInventory, sf::Vector2u windowSize);
	static void updateHUDEquipment(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & HUDEquipment, sf::Vector2u windowSize);
};
