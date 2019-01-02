#pragma once
#include "Character.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Character
{
public:
	Enemy(std::string name, int hp, int attackDamage, int attackSpeed, int exp, int coins, float movementSpeed, float lootChance);
	virtual ~Enemy() = 0 {}
	void setLootChance(float);
	void setRandomMovementLength(int);
	float getLootChance() const;
	int getRandomMovementLength() const;
private:
	int randomMovementLength;
	float lootChance, item; //item to do
};
