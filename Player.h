#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp, int attackDamage, int attackSpeed, float movSpeed);
	~Player() {}
	//setters
	void levelUp();
	void distanceLevelUp();
	void meleeLevelUp();
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
private:
	bool weapon = (int)Weapons::MELEE;
	int level;
	int distanceLevel, meleeLevel;
	int distanceHits, meleeHits;
	//std::vector<item> inventory;
};
