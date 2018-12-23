#include "Player.h"



Player::Player(std::string name, int hp, int stamina, int attackDamage, int attackSpeed, int experience, int coins, float movementSpeed)
	: Character(name, hp, attackDamage, attackSpeed, experience, coins, movementSpeed)
{
	level = distanceLevel = meleeLevel = magicLevel = 1;
	distCounter = melCounter, magCounter = 0;
	setMarked(true);
}

//setters

void Player::levelUp()
{
	level++;
}

void Player::distanceLevelUp()
{
	distanceLevel++;
}

void Player::meleeLevelUp()
{
	meleeLevel++;
}

void Player::magicLevelUp()
{
	magicLevel++;
}

void Player::distCounterUp()
{
	distCounter++;
}

void Player::melCounterUp()
{
	melCounter++;
}

void Player::magCounterUp()
{
	magCounter++;
}

//getters

int Player::getLevel() const
{
	return level;
}

int Player::getDistanceLevel() const
{
	return distanceLevel;
}

int Player::getMeleeLevel() const
{
	return meleeLevel;
}

int Player::getMagicLevel() const
{
	return magicLevel;
}

int Player::getDistCounter() const
{
	return distCounter;
}

int Player::getMelCounter() const
{
	return melCounter;
}

int Player::getMagCounter() const
{
	return magCounter;
}


//methods
void Player::deadHuman()
{

}
