#pragma once
#include "PathFinding.h"
#include "Constants.h"
#include <string>

class Character
{
public:
	Character(std::string name, int healthPoints, int attackDamage, int attackSpeed, int experience, float movementSpeed);
	virtual ~Character() = 0 {}
public:
	void setName(std::string);
	void setMaxHp(int);
	void setCurrentHp(int);
	void setAttackDamage(int);
	void setBaseAttackDamage(int);
	void setAttackSpeed(int);
	void setMovementSpeed(float);
	void setDefense(int);
	void setExperience(int);
	void setDirection(int);
	void setCanMoveUp(bool);
	void setCanMoveDown(bool);
	void setCanMoveLeft(bool);
	void setCanMoveRight(bool);
	void setWalkCounter(int);
	void setCanMoveNum(int);
	void canMoveEverywhere();
	void setNextMove(sf::Vector2i);
	void setTargetPosition(sf::Vector2i);
	void setDead(bool);
	void setMarked(bool);
	void setFighting(bool);
public:
	std::string getName() const;
	int getMaxHp() const;
	int getCurrentHp() const;
	int getAttackDamage() const;
	int getBaseAttackDamage() const;
	int getAttackSpeed() const;
	int getDefense() const;
	int getBaseDefense() const;
	float getMovementSpeed() const;
	int getExperience() const;
	int getDirection() const;
	bool getCanMoveUp() const;
	bool getCanMoveDown() const;
	bool getCanMoveLeft() const;
	bool getCanMoveRight() const;
	int getWalkCounter() const;
	PathFinding & getPathFinding();
	sf::Vector2i getNextMove() const;
	sf::Vector2i getTargetPosition() const;
	bool isDead() const;
	bool isMarked() const;
	bool isFighting() const;
private:
	std::string name;
	int hpMax, hp;
	int attackDamage, baseAttackDamage;
	int attackSpeed;
	int defense, baseDefense;
	int experience;
	float movementSpeed;
	int direction;
	bool canMoveUp, canMoveDown, canMoveLeft, canMoveRight;
	int walkCounter;
	PathFinding pathfinding;
	sf::Vector2i nextMove;
	sf::Vector2i targetPosition;
	bool fighting, marked, dead;
};
