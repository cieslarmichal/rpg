#pragma once
class Item
{
public:
	Item(int type, int amount = 1);
	void setCollected(bool);
	void setReadyToPick(bool);
	void setDistanceFromPlayer(int);
	int getType() const;
	int getAmount() const;
	bool isCollected() const;
	bool isReadyToPick() const;
	int getDistanceFromPlayer() const;
	enum Type { COIN = 0, MELEE_WEAPON = 1, DISTANCE_WEAPON = 2, HEALTHPOTION = 3, KEY = 4 };
private:
	int type;
	int amount;
	bool collected, readyToPick;
	int distanceFromPlayer;
};

