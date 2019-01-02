#include "LevelManager.h"

int LevelManager::requireExperience(100);
int LevelManager::requireDistanceHits(10);
int LevelManager::requireMeleeHits(10);


std::string LevelManager::update(std::unique_ptr<Player> & player)
{
	if (player->getExperience() >= requireExperience)
	{
		int previousLevel = player->getLevel();
		while (player->getExperience() >= requireExperience)
		{
			player->levelUp();
			requireExperience += 2 * requireExperience;
		}
		std::string msg = "You advanced from Level " + std::to_string(previousLevel) + " to Level " + std::to_string(player->getLevel()) + ".";
		return msg;
	}
	if (player->getDistanceHits() >= requireDistanceHits)
	{
		player->distanceLevelUp();
		requireDistanceHits += requireDistanceHits * 1.9;
		std::string msg = "You advanced from Distance " + std::to_string(player->getDistanceLevel() - 1) + " to Distance " + std::to_string(player->getDistanceLevel()) + ".";
		return msg;
	}

	if (player->getMeleeHits() >= requireMeleeHits)
	{
		player->meleeLevelUp();
		requireMeleeHits += requireMeleeHits * 1.5;
		std::string msg = "You advanced from Melee " + std::to_string(player->getMeleeLevel() - 1) + " to Melee " + std::to_string(player->getMeleeLevel()) + ".";
		return msg;
	}

	return "";
}

int LevelManager::getRequireExperience()
{
	return requireExperience;
}

void LevelManager::getExperience(std::unique_ptr<Player> & player, std::unique_ptr<Enemy> & enemy)
{
	player->setExperience(player->getExperience() + enemy->getExperience());
}
