#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Directions.h"

class Character
{
public:
	Character(std::string name, int healthPoints, int attackDamage, int attackSpeed, int experience, int coins, float movementSpeed);
	virtual ~Character() = 0 {}
	//setters
	void setName(std::string);
	void setMaxHp(int);
	void setCurrentHp(int);
	void setAttackDamage(int);
	void setAttackSpeed(int);
	void setMovementSpeed(float);
	void setExp(int);
	void setCoins(int);
	void setDirection(int);
	void setCanMoveUp(bool);
	void setCanMoveDown(bool);
	void setCanMoveLeft(bool);
	void setCanMoveRight(bool);
	void setWalkCounter(int);
	void setRandomMovementLength(int);
	void setDead(bool);
	void setCanMoveNum(int);
	void canMoveEverywhere();
	void setMarked(bool);
	void setFighting(bool);
	//getters
	std::string getName() const;
	int getMaxHp() const;
	int getCurrentHp() const;
	int getAttackDamage() const;
	int getAttackSpeed() const;
	float getMovementSpeed() const;
	int getExp() const;
	int getCoins() const;
	int getDirection() const;
	bool getCanMoveUp() const;
	bool getCanMoveDown() const;
	bool getCanMoveLeft() const;
	bool getCanMoveRight() const;
	int getWalkCounter() const;
	int getRandomMovementLength() const;
	bool getDead() const;
	bool isMarked() const;
	bool isFighting() const;
private:
	std::string name;
	int hpMax, hp;
	int attackDamage, attackSpeed;
	int experience;
	int coins;
	//std::vector<item> inventory;
	float movementSpeed;
	int direction;
	bool canMoveUp, canMoveDown, canMoveLeft, canMoveRight;
	int walkCounter;
	int randomMovementLength;
	bool dead = false;
	bool marked = false;
	bool fighting = false;
};
