#include "Dragon.h"



Dragon::Dragon(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed, int exp, float lootChance)
	: Enemy(name, hp, attackDamage, attackSpeed, exp, movementSpeed, lootChance)
{
}


Dragon::~Dragon()
{
}
