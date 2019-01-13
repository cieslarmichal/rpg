#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int attackDamage, int attackSpeed, int exp, float movementSpeed, float chance)
	: Character(name, hp, attackDamage, attackSpeed, exp, movementSpeed), lootChance(chance)
{

	setDirection(Random::getRandomNumber(0, 3));
	randomMovementLength = 65;
}


//setters
void Enemy::setRandomMovementLength(int inp)
{
	randomMovementLength = inp;
}

void Enemy::setLootChance(float inp)
{
	lootChance = inp;
}

//getters
float Enemy::getLootChance() const
{
	return lootChance;

}

int Enemy::getRandomMovementLength() const
{
	return randomMovementLength;
}

