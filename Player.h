#pragma once
#include "Character.h"
#include "Inventory.h"
#include "Missions.h"

class Player : public Character
{
public:
	Player(std::string name, int hp, int attackDamage, int attackSpeed, float movSpeed);
	~Player();
	void levelUp();
	void setCoins(int);
	void distanceSkillUp();
	void meleeSkillUp();
	void distanceHitsUp();
	void meleeHitsUp();
	void setWeapon(bool);
public:
	int getLevel() const;
	int getCoins() const;
	int getDistanceSkill() const;
	int getMeleeSkill() const;
	bool getWeapon() const;
	int getDistanceHits() const;
	int getMeleeHits() const;
public:
	Inventory & getInventory();
	void pickUpItem(Item & item, int actionKey);
	void useItem(int actionKey);
	void changeChosenItem(int actionKey);
	void dropItem(int actionKey);
private:
	int level;
	int coins;
	bool weapon;
	int distanceSkill, meleeSkill;
	int distanceHits, meleeHits;
private:
	Inventory inventory;
	void updateEqEffects();
	TimeHandler pickItemTimer,useItemTimer;
};

