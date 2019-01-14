#pragma once
#include "File.h"
#include "Mission.h"

class Missions
{
public:
	Missions() = delete;
	static void readMissions();
	static void startMission();
	static std::string getCurrentMissionName();
	static int getCurrentProgress();
	static int getCurrentGoal();
	static int getCurrentAwardItemId();
	static int getCurrentAwardExperience();
	static bool isCurrentMissionStarted();
	static bool isCurrentMissionCompleted();
	static void updateCollected(int itemType);
	static void updateKilled(int enemyType);
	static void nextMission();
private:
	static std::vector<std::unique_ptr<Mission>> missions;
	static std::vector<std::string> listOfMissions;
	static int currentMissionIndex;
};

