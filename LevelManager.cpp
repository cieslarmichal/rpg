#include "LevelManager.h"

int LevelManager::requireExperience(100);
int LevelManager::requireDistanceHits(15);
int LevelManager::requireMeleeHits(15);
int LevelManager::currentExperience(0);


std::string LevelManager::update(std::unique_ptr<Player> & player)
{
	if (currentExperience >= requireExperience)
	{
		int previousLevel = player->getLevel();
		while (currentExperience >= requireExperience)
		{
			currentExperience = player->getExperience() - requireExperience;
			player->levelUp();
			requireExperience = 2 * requireExperience;
		}
		std::string msg = "You advanced from Level " + std::to_string(previousLevel) + " to Level " + std::to_string(player->getLevel()) + ".";
		return msg;
	}
	if (player->getDistanceHits() >= requireDistanceHits)
	{
		player->distanceSkillUp();
		requireDistanceHits += requireDistanceHits * 1.9;
		std::string msg = "You advanced from Distance Skill " + std::to_string(player->getDistanceLevel() - 1) + " to Distance Skill " + std::to_string(player->getDistanceLevel()) + ".";
		return msg;
	}

	if (player->getMeleeHits() >= requireMeleeHits)
	{
		player->meleeSkillUp();
		requireMeleeHits += requireMeleeHits * 1.5;
		std::string msg = "You advanced from Melee Skill " + std::to_string(player->getMeleeLevel() - 1) + " to Melee Skill " + std::to_string(player->getMeleeLevel()) + ".";
		return msg;
	}

	return "";
}

int LevelManager::getRequireExperience()
{
	return requireExperience;
}

int LevelManager::getCurrentExperience()
{
	return currentExperience;
}

void LevelManager::getExperience(std::unique_ptr<Player> & player, std::unique_ptr<Enemy> & enemy)
{
	player->setExperience(player->getExperience() + enemy->getExperience());
	currentExperience += enemy->getExperience();
}
