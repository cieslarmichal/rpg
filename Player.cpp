#include "Player.h"



Player::Player(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed)
	: Character(name, hp, attackDamage, attackSpeed, 0, 0, movementSpeed)
{
	level = distanceLevel = meleeLevel = 1;
	distanceHits = meleeHits = 0;
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


void Player::distanceHitsUp()
{
	distanceHits++;
}

void Player::meleeHitsUp()
{
	meleeHits++;
}

void Player::setWeapon(bool inp)
{
	weapon = inp;
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


int Player::getDistanceHits() const
{
	return distanceHits;
}

int Player::getMeleeHits() const
{
	return meleeHits;
}

bool Player::getWeapon() const
{
	return weapon;
}