#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Item
{
public:
	Item(int type, int whichInOrder);
	Item(int itemID);
	void setCollected(bool);
	void setReadyToPick(bool);
	void setDistanceFromPlayer(int);
	std::string getName() const;
	int getId() const;
	int getType() const;
	int getDamage() const;
	int getArmor() const;
	int getAmountRestoringHp() const;
	int getSellValue() const;
	bool getOpensDoor() const;
	std::string getPathName() const;
	bool isCollected() const;
	bool isReadyToPick() const;
	int getDistanceFromPlayer() const;
public:
	enum Type 
	{
		COIN = 0, HEALTH_POTION = 1, FOOD = 2, MELEE_WEAPON = 3, DISTANCE_WEAPON = 4, SHIELD = 5,
		NECKLACE = 6, RING = 7, HELMET = 8, BOOTS = 9, ARMOR = 10, GLOVES = 11, KEY = 12
	};
	enum WhichInOrder { FIRST = 0, SECOND = 1, THIRD = 2, FOURTH = 3 };
private:
	std::string name;
	int id, type, whichInOrder;
	int damage, armor, amountRestoringHp, sellValue;
	bool opensDoor;
	bool collected, readyToPick;
	int distanceFromPlayer;
	std::string pathName;
private:
	void setPathName(int type, int which);
	void setStats();
	void setStatsByID();
	int specifyType(std::string);
	int specifyWhichInOrder(std::string);
};

