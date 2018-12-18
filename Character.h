#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

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
	void setCounter(int);
	void setMovementLength(int);
	void setDead(bool);
	void setCanMoveNum(int);
	void canMoveEverywhere();
	void setMarked(bool);
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
	int getCounter() const;
	int getMovementLength() const;
	bool getDead() const;
	bool isMarked() const;
	//methods
	virtual void update() = 0 {}
private:
	std::string name;
	int hpMax, hp;
	int attackDamage, attackSpeed;
	int experience;
	int coins;
	//std::vector<item> inventory;
	float movementSpeed;
	int direction; //1 up 2 down 3 left 4 right
	bool canMoveUp, canMoveDown, canMoveLeft, canMoveRight;
	int counter, walkCounter;
	int movementLength; //length of AFK random movements
	bool dead = false;
	bool marked = false;
};


