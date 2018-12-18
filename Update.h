#pragma once
#include "Movement.h"
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Update
{
public:
	Update();
	void updatePlayer(std::unique_ptr<Wrapper> & player,StatusBar & statBar, int direction);
	void updateEnemies(enemyPair & enemies, int nothing);
	void updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void updateText(std::vector<std::unique_ptr<Text>> & text, sf::View view);
	void updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies);
private:
	Movement movement;
};

