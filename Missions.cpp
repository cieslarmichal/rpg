#include "Missions.h"

std::vector<std::unique_ptr<Mission>> Missions::missions;
std::vector<std::string> Missions::listOfMissions;
int Missions::currentMissionIndex;

void Missions::readMissions()
{
	listOfMissions = File::getLines("stuff/missions.txt");
	
	for(auto & mission: listOfMissions)
	{
		missions.push_back(std::unique_ptr<Mission>(new Mission(mission)));
	}
}

std::string Missions::getCurrentMissionName()
{
	if (currentMissionIndex < (int)listOfMissions.size())
	{
		return missions[currentMissionIndex]->getMissionName();
	}
	else
	{
		return std::string("");
	}
}

int Missions::getCurrentProgress()
{
	return  missions[currentMissionIndex]->getCurrentProgress();
}

int Missions::getCurrentGoal()
{
	return  missions[currentMissionIndex]->getGoal();
}

int Missions::getCurrentAwardItemId()
{
	return missions[currentMissionIndex]->getAwardItemId();
}

bool Missions::isCompleted()
{
	return missions[currentMissionIndex]->isCompleted();
}

void Missions::updateCollected(int itemType)
{
	missions[currentMissionIndex]->updateCollected(itemType);
}

void Missions::updateKilled(int enemyType)
{
	missions[currentMissionIndex]->updateKilled(enemyType);
}

void Missions::nextMission()
{
	if (currentMissionIndex + 1 != (int)listOfMissions.size())
	{
		currentMissionIndex++;
	}
}
