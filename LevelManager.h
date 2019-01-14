#pragma once
#include "Player.h"
#include "Enemy.h"

class LevelManager
{
public:
	LevelManager() = delete;
	static std::string update(std::unique_ptr<Player> & player);
	static int getRequireExperience();
	static int getCurrentExperience();
	static void gainExperience(std::unique_ptr<Player> &, int experience);
private:
	static int currentExperience;
	static int requireExperience, requireDistanceHits, requireMeleeHits;
private:
	static std::string levelUp(std::unique_ptr<Player> & player);
	static std::string distanceSkillUp(std::unique_ptr<Player> & player);
	static std::string meleeSkillUp(std::unique_ptr<Player> & player);
};

