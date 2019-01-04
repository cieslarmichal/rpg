#pragma once
#include "Character.h"
#include "Inventory.h"

class Player : public Character
{
public:
	Player(std::string name, int hp, int attackDamage, int attackSpeed, float movSpeed);
	~Player() {}
	//setters
	void levelUp();
	void distanceSkillUp();
	void meleeSkillUp();
	void distanceHitsUp();
	void meleeHitsUp();
	void setWeapon(bool);
	//getters
	int getLevel() const;
	int getDistanceLevel() const;
	int getMeleeLevel() const;
	bool getWeapon() const;
	int getDistanceHits() const;
	int getMeleeHits() const;
	Inventory & getInventory();
private:
	int level;
	Inventory inventory;
	bool weapon = (int)Weapons::MELEE;
	int distanceSkill, meleeSkill;
	int distanceHits, meleeHits;
};
