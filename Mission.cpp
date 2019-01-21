#include "Mission.h"


Mission::Mission(std::string name)
{
	loadMission(name);
}

Mission::~Mission()
{
	std::cout << "x" << std::endl;
}

std::string Mission::getMissionName() const
{
	return name;
}

int Mission::getProgress() const
{
	return progress;
}

int Mission::getGoal() const
{
	return goal;
}

int Mission::getAwardItemId() const
{
	return awardItemId;
}

int Mission::getAwardExperience() const
{
	return awardExp;
}

bool Mission::isStarted() const
{
	return started;
}

bool Mission::isCompleted() const
{
	return completed;
}

void Mission::updateCollected(int itemType)
{
	if (!collecting || !started) return;

	switch (itemType)
	{
	case Item::Type::FOOD:
		if (killCollectWhat == "food")
		{
			currentProgressUp();
		}
		break;
	}

	if (progress >= goal)
	{
		completed = true;
	}
}

void Mission::updateKilled(int enemyType)
{
	if (!killing || !started) return;

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
}

void Mission::setStarted(bool inp)
{
	started = inp;
}

void Mission::loadMission(std::string description)
{
	std::stringstream ss;
	ss.str(description);
	std::string killOrCollect;
	std::string emptySapce;
	//Kill 5 dragons experience: 200 award: 17 
	ss >> killOrCollect >> goal >> killCollectWhat >> emptySapce >> awardExp >> emptySapce >> awardItemId;

	name = killOrCollect + " " + std::to_string(goal) + " " + killCollectWhat + " " + std::to_string(awardExp) + " exp";

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

	progress = 0;
	started = completed = false;
}

void Mission::currentProgressUp()
{
	if (progress + 1 <= goal)
	{
		progress++;
	}

	if (progress >= goal)
	{
		completed = true;
	}
}


