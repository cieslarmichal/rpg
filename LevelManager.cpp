#include "LevelManager.h"

int LevelManager::requireExperience(100);
int LevelManager::requireDistanceHits(15);
int LevelManager::requireMeleeHits(15);
int LevelManager::currentExperience(0);


std::string LevelManager::update(std::unique_ptr<Player> & player)
{
	if (currentExperience >= requireExperience)
	{
		return levelUp(player);
	}

	if (player->getDistanceHits() >= requireDistanceHits)
	{
		return distanceSkillUp(player);
	}

	if (player->getMeleeHits() >= requireMeleeHits)
	{
		return meleeSkillUp(player);
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

void LevelManager::gainExperience(std::unique_ptr<Player> & player, int experience)
{
	player->setExperience(player->getExperience() + experience);
	currentExperience += experience;
}

std::string LevelManager::levelUp(std::unique_ptr<Player>& player)
{
	int previousLevel = player->getLevel();
	while (currentExperience >= requireExperience)
	{
		currentExperience = player->getExperience() - requireExperience;
		player->levelUp();
		requireExperience = requireExperience * 2;
	}
	std::string msg = "You advanced from Level " + std::to_string(previousLevel) + " to Level " + std::to_string(player->getLevel()) + ".";
	return msg;
}

std::string LevelManager::distanceSkillUp(std::unique_ptr<Player>& player)
{
	player->distanceSkillUp();
	if (player->getDistanceSkill() % 2 == 0)
	{
		player->setBaseAttackDamage(player->getBaseAttackDamage() + 1);
	}
	requireDistanceHits += (int)(requireDistanceHits * 1.6);
	std::string msg = "You advanced from Distance Skill " + std::to_string(player->getDistanceSkill() - 1) + " to Distance Skill " + std::to_string(player->getDistanceSkill()) + ".";
	return msg;
}

std::string LevelManager::meleeSkillUp(std::unique_ptr<Player>& player)
{
	player->meleeSkillUp();
	if (player->getDistanceSkill() % 2 == 0)
	{
		player->setBaseAttackDamage(player->getBaseAttackDamage() + 1);
	}
	requireMeleeHits += (int)(requireMeleeHits * 1.7);
	std::string msg = "You advanced from Melee Skill " + std::to_string(player->getMeleeSkill() - 1) + " to Melee Skill " + std::to_string(player->getMeleeSkill()) + ".";
	return msg;
}

