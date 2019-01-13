#include "Mission.h"


Mission::Mission(std::string name)
{
	loadMission(name);
}

std::string Mission::getMissionName() const
{
	return name;
}

int Mission::getCurrentProgress() const
{
	return currentProgress;
}

int Mission::getGoal() const
{
	return goal;
}

int Mission::getAwardItemId() const
{
	return awardItemId;
}

bool Mission::isCompleted() const
{
	return completed;
}

void Mission::updateCollected(int itemType)
{
	if (!collecting) return;

	switch (itemType)
	{
	case Item::Type::FOOD:
		if (killCollectWhat == "food")
		{
			currentProgressUp();
		}
		break;
	}

	if (currentProgress >= goal)
	{
		completed = true;
	}
}

void Mission::updateKilled(int enemyType)
{
	if (!killing) return;

	switch (enemyType)
	{
	case Enemy::EnemyType::SKELETON:
		if (killCollectWhat == "skeleton" || killCollectWhat == "skeletons")
		{
			currentProgressUp();
		}
		break;
	case Enemy::EnemyType::SKELETON_BERSERKER:
		if (killCollectWhat == "skeletonBerserker" || killCollectWhat == "skeletonBerserkers")
		{
			currentProgressUp();
		}
		break;
	case Enemy::EnemyType::DRAGON:
		if (killCollectWhat == "dragon" || killCollectWhat == "dragons")
		{
			currentProgressUp();
		}
		break;
	}

	if (currentProgress >= goal)
	{
		completed = true;
	}
}

void Mission::loadMission(std::string description)
{
	std::stringstream ss;
	ss.str(description);
	std::string killOrCollect;
	std::string emptySapce;
	//Kill 5 dragons award: 17 
	ss >> killOrCollect >> goal >> killCollectWhat >> emptySapce >> awardItemId;

	name = killOrCollect + " " + std::to_string(goal) + " " + killCollectWhat;

	std::transform(killCollectWhat.begin(), killCollectWhat.end(), killCollectWhat.begin(), ::tolower);
	std::transform(killOrCollect.begin(), killOrCollect.end(), killOrCollect.begin(), ::tolower);

	if (killOrCollect == "kill")
	{
		killing = true;
		collecting = false;
	}
	else if (killOrCollect == "collect")
	{
		killing = false;
		collecting = true;
	}

	currentProgress = 0;
	completed = false;
}

void Mission::currentProgressUp()
{
	if (currentProgress + 1 <= goal)
	{
		currentProgress++;
	}
}


