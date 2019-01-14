#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include "Item.h"
#include "Enemy.h"

class Mission
{
public:
	Mission(std::string description);
	std::string getMissionName() const;
	int getCurrentProgress() const;
	int getGoal() const;
	int getAwardItemId() const;
	int getAwardExperience() const;
	bool isCompleted() const;
	void updateCollected(int itemType);
	void updateKilled(int enemyType);
private:
	void loadMission(std::string description);
	void currentProgressUp();
private:
	std::string name;
	int awardItemId;
	int awardExp;
	bool killing, collecting;
	std::string killCollectWhat;
	enum KeyWords { KILL = 0, COLLECT = 1 };
	int currentProgress, goal;
	bool completed;
};
