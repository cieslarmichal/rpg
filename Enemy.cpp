#include "Enemy.h"



Enemy::Enemy(std::string name, int hp, int attackDamage, int attackSpeed, int exp, int coins, float movementSpeed, float chance)
	: Character(name, hp, attackDamage, attackSpeed, exp, coins, movementSpeed), lootChance(chance)
{
	std::srand((unsigned)std::time(NULL));
	setDirection(std::rand() % 4 + 1);
}

//setters
void Enemy::setLootChance(float inp)
{
	lootChance = inp;
}

//getters
float Enemy::getLootChance() const
{
	return lootChance;

}

void Enemy::dropItem()
{

}
