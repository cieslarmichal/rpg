#pragma once
#include "Movement.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "LevelManager.h"
#include "Create.h"
#include "Inventory.h"
#include "HUD.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Update
{
public:
	Update() = delete;
	static void updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications);
	static void updateNpc(std::vector<std::unique_ptr<Wrapper>> & npcs);
	static void updateEnemies(enemyPair & enemies, std::unique_ptr<Wrapper> & player);
	static void updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles);
	static void updateItems(std::vector<std::unique_ptr<Wrapper>> & items);
	static void updateText(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & text);
	static void updateHUD(std::unique_ptr<Wrapper> & player, HUD & hud, sf::Vector2u windowSize);
	static void updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies);
};
