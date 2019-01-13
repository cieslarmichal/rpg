#pragma once
#include "Character.h"
#include "Random.h"

class Enemy : public Character
{
public:
	Enemy(std::string name, int hp, int attackDamage, int attackSpeed, int exp, float movementSpeed, float lootChance);
	virtual ~Enemy() = 0 {}
	void setLootChance(float);
	void setRandomMovementLength(int);
	float getLootChance() const;
	int getRandomMovementLength() const;
private:
	int randomMovementLength;
	float lootChance;
};
