#pragma once
#include "Movement.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include "ChangeWeapon.h"
#include "LevelManager.h"
#include "Create.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Update
{
public:
	Update() = delete;
	static void updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications, sf::View view);
	static void updateEnemies(enemyPair & enemies, std::unique_ptr<Wrapper> & player);
	static void updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles);
	static void updateText(std::vector<std::unique_ptr<Text>> & text, sf::View view);
	static void updateHUDInfo(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & texts, sf::Vector2u windowSize);
	static void updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies);
};
