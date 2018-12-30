#pragma once
#include "Enemy.h"

class Dragon :public Enemy
{
public:
	Dragon(std::string name, int hp, int attackDamage, int attackSpeed, int exp, int coins, float movementSpeed, float lootChance);
	~Dragon();
};

