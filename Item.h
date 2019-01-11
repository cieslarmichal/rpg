#pragma once
#include <string>
#include "ItemFactory.h"
#include "Directions.h"

class Item
{
public:
	Item(int itemID);
	Item();
	void setName(std::string);
	void setPathName(std::string);
	void setId(int);
	void setType(int);
	void setDamage(int);
	void setArmor(int);
	void setRestoringHp(int);
	void setSellValue(int);
	void setDestroyed(bool);
	void setReadyToPick(bool);
	void setReadyToDrop(bool);
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
	bool isDestroyed() const;
	bool isReadyToPick() const;
	bool isReadyToDrop() const;
	int getDistanceFromPlayer() const;
public:
	enum Type 
	{
		COIN = 0, HEALTH_POTION = 1, FOOD = 2, MELEE_WEAPON = 3, DISTANCE_WEAPON = 4, SHIELD = 5,
		NECKLACE = 6, RING = 7, HELMET = 8, BOOTS = 9, ARMOR = 10
	};
private:
	std::string name;
	std::string pathName;
	int id, type;
	int damage, armor, restoringHp, sellValue;
	bool destroyed, readyToDrop, readyToPick;
	int distanceFromPlayer;
};

