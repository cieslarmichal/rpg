#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp, int stamina, int attackDamage, int attackSpeed, int experience, int coins, float movSpeed);
	~Player() {} //virtual in future
	//setters
	void levelUp();
	void distanceLevelUp();
	void meleeLevelUp();
	void magicLevelUp();
	void distCounterUp();
	void melCounterUp();
	void magCounterUp();
	//getters
	int getLevel() const;
	int getDistanceLevel() const;
	int getMeleeLevel() const;
	int getMagicLevel() const;
	int getDistCounter() const;
	int getMelCounter() const;
	int getMagCounter() const;
	void deadHuman();
private:
	int stamina, staminaMax;
	int level;
	int distanceLevel, meleeLevel, magicLevel;
	int distCounter, melCounter, magCounter;
	//std::vector<item> inventory;
};

