#pragma once
#include <string>
#include "ItemFactory.h"

class Item
{
public:
	Item(int itemID);
	void setName(std::string);
	void setPathName(std::string);
	void setId(int);
	void setType(int);
	void setDamage(int);
	void setArmor(int);
	void setRestoringHp(int);
	void setSellValue(int);
	void setCollected(bool);
	void setReadyToPick(bool);
	void setDistanceFromPlayer(int);
public:
	std::string getName() const;
	std::string getPathName() const;
	int getId() const;
	int getType() const;
	int getDamage() const;
	int getArmor() const;
	int getRestoringHp() const;
	int getSellValue() const;
	bool isCollected() const;
	bool isReadyToPick() const;
	int getDistanceFromPlayer() const;
public:
	enum Type 
	{
		COIN = 0, HEALTH_POTION = 1, FOOD = 2, MELEE_WEAPON = 3, DISTANCE_WEAPON = 4, SHIELD = 5,
		NECKLACE = 6, RING = 7, HELMET = 8, BOOTS = 9, ARMOR = 10, GLOVES = 11
	};
private:
	std::string name;
	std::string pathName;
	int id, type;
	int damage, armor, restoringHp, sellValue;
	bool collected, readyToPick, equipped;
	int distanceFromPlayer;
};

