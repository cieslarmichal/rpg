#pragma once
#include "Enemy.h"
#include "Item.h"
#include <algorithm>
#include <sstream>
#include <string>

class Mission
{
public:
	Mission(std::string description);
	~Mission();
	void updateCollected(int itemType);
	void updateKilled(int enemyType);
	void setStarted(bool);
	std::string getMissionName() const;
	int getProgress() const;
	int getGoal() const;
	int getAwardItemId() const;
	int getAwardExperience() const;
	bool isStarted() const;
	bool isCompleted() const;
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
	int progress, goal;
	bool started, completed;
};
