#pragma once
#include "Character.h"
#include "Inventory.h"

class Player : public Character
{
public:
	Player(std::string name, int hp, int attackDamage, int attackSpeed, float movSpeed);
	~Player();
	void levelUp();
	void distanceSkillUp();
	void meleeSkillUp();
	void distanceHitsUp();
	void meleeHitsUp();
	void setWeapon(bool);
	int getLevel() const;
	int getDistanceLevel() const;
	int getMeleeLevel() const;
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
	bool weapon = (int)Weapons::MELEE;
	int distanceSkill, meleeSkill;
	int distanceHits, meleeHits;
private:
	Inventory inventory;
	void updateEqEffects();
	TimeHandler pickItemTimer,useItemTimer;
};
