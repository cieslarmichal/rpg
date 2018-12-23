#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
public:
	Skeleton(std::string name, int hp, int attackDamage, int attackSpeed, int exp, int coins, float movementSpeed, float lootChance);
	~Skeleton() {}
};
