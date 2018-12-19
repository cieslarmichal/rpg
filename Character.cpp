#include "Character.h"



Character::Character(std::string n, int hpp, int ad, int as, int exp, int c, float movSpeed)
	: name(n), hpMax(hpp), hp(hpp), attackDamage(ad), attackSpeed(as), experience(exp), coins(c), movementSpeed(movSpeed)
{
	direction = 1;
	walkCounter = counter = 0;
	randomMovementLength = 65;
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

//setters
void Character::setName(std::string inp)
{
	name = inp;
}

void Character::setMaxHp(int inp)
{
	hpMax = inp;
}

void Character::setCurrentHp(int inp)
{
	hp = inp;
}

void Character::setAttackDamage(int inp)
{
	attackDamage = inp;
}

void Character::setAttackSpeed(int inp)
{
	attackSpeed = inp;
}

void Character::setMovementSpeed(float inp)
{
	movementSpeed = inp;
}

void Character::setExp(int inp)
{
	experience = inp;
}

void Character::setCoins(int inp)
{
	coins = inp;
}

void Character::setDirection(int inp)
{
	direction = inp;
}

void Character::setCanMoveUp(bool inp)
{
	canMoveUp = inp;
}

void Character::setCanMoveDown(bool inp)
{
	canMoveDown = inp;
}

void Character::setCanMoveLeft(bool inp)
{
	canMoveLeft = inp;
}

void Character::setCanMoveRight(bool inp)
{
	canMoveRight = inp;
}

void Character::setWalkCounter(int inp)
{
	walkCounter = inp;
}

void Character::setCounter(int inp)
{
	counter = inp;
}

void Character::setRandomMovementLength(int inp)
{
	randomMovementLength = inp;
}

void Character::setDead(bool inp)
{
	dead = inp;
}

void Character::setCanMoveNum(int inp)
{
	switch (inp)
	{
	case 1:
		setCanMoveUp(true);
		break;
	case 2:
		setCanMoveDown(true);
		break;
	case 3:
		setCanMoveLeft(true);
		break;
	case 4:
		setCanMoveRight(true);
		break;
	}
}


void Character::setMarked(bool inp)
{
	marked = inp;
}

void Character::setFighting(bool inp)
{
	fighting = inp;
}

//getters
std::string Character::getName() const
{
	return name;
}

int Character::getMaxHp() const
{
	return hpMax;
}

int Character::getCurrentHp() const
{
	return hp;
}

int Character::getAttackDamage() const
{
	return attackDamage;
}

int Character::getAttackSpeed() const
{
	return attackSpeed;
}

float Character::getMovementSpeed() const
{
	return movementSpeed;
}

int Character::getExp() const
{
	return experience;
}

int Character::getCoins() const
{
	return coins;
}

int Character::getDirection() const
{
	return direction;
}

bool Character::getCanMoveUp() const
{
	return canMoveUp;
}

bool Character::getCanMoveDown() const
{
	return canMoveDown;
}

bool Character::getCanMoveLeft() const
{
	return canMoveLeft;
}

bool Character::getCanMoveRight() const
{
	return canMoveRight;
}

int Character::getWalkCounter() const
{
	return walkCounter;
}

int Character::getCounter() const
{
	return counter;
}

int Character::getRandomMovementLength() const
{
	return randomMovementLength;
}

bool Character::getDead() const
{
	return dead;
}


bool Character::isMarked() const
{
	return marked;
}

bool Character::isFighting() const
{
	return fighting;
}

//methods
void Character::canMoveEverywhere()
{
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}


