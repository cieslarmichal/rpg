#pragma once
#include "Enemy.h"

class Dragon :public Enemy
{
public:
	Dragon(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed, int experience, float lootChance);
};

