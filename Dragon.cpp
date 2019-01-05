#include "Dragon.h"



Dragon::Dragon(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed, int exp, int coins, float lootChance)
	: Enemy(name, hp, attackDamage, attackSpeed, exp, coins, movementSpeed, lootChance)
{
}


Dragon::~Dragon()
{
}
