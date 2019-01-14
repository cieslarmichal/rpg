#include "Character.h"

Character::Character(std::string n, int hpp, int ad, int as, int exp, float movSpeed)
	: name(n), hpMax(hpp), hp(hpp), attackDamage(ad), attackSpeed(as), experience(exp), movementSpeed(movSpeed)
{
	baseAttackDamage = attackDamage;
	baseDefense = defense = 0;
	direction = 1;
	walkCounter = 0;
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
	fighting = marked = dead = false;
	nextMove = { (int)Others::RESET, (int)Others::RESET };
	targetPosition = { (int)Others::RESET, (int)Others::RESET };
}

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

void Character::setBaseAttackDamage(int inp)
{
	baseAttackDamage = inp;
}

void Character::setAttackSpeed(int inp)
{
	attackSpeed = inp;
}

void Character::setDefense(int inp)
{
	defense = inp;
}

void Character::setMovementSpeed(float inp)
{
	movementSpeed = inp;
}

void Character::setExperience(int inp)
{
	experience = inp;
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

void Character::setCanMoveNum(int inp)
{
	switch (inp)
	{
	case (int)Directions::UP:
		setCanMoveUp(true);
		break;
	case (int)Directions::DOWN:
		setCanMoveDown(true);
		break;
	case (int)Directions::LEFT:
		setCanMoveLeft(true);
		break;
	case (int)Directions::RIGHT:
		setCanMoveRight(true);
		break;
	}
}

void Character::canMoveEverywhere()
{
	canMoveUp = canMoveDown = canMoveLeft = canMoveRight = true;
}

void Character::setNextMove(sf::Vector2i inp)
{
	nextMove = inp;
}

void Character::setTargetPosition(sf::Vector2i inp)
{
	targetPosition = inp;
}

void Character::setDead(bool inp)
{
	dead = inp;
}

void Character::setMarked(bool inp)
{
	marked = inp;
}

void Character::setFighting(bool inp)
{
	fighting = inp;
}

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

int Character::getBaseAttackDamage() const
{
	return baseAttackDamage;
}

int Character::getAttackSpeed() const
{
	return attackSpeed;
}

int Character::getDefense() const
{
	return defense;
}

int Character::getBaseDefense() const
{
	return baseDefense;
}

float Character::getMovementSpeed() const
{
	return movementSpeed;
}

int Character::getExperience() const
{
	return experience;
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

PathFinding & Character::getPathFinding()
{
	return pathfinding;
}

sf::Vector2i Character::getNextMove() const
{
	return nextMove;
}

sf::Vector2i Character::getTargetPosition() const
{
	return targetPosition;
}

bool Character::isDead() const
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

