#pragma once
class Obstacle
{
public:
	Obstacle(bool destructable = false, int hp = 10);
	//setters
	void setCurrentHp(int);
	void setDestructable(bool);
	void setDestroyed(bool);
	//getters
	int getCurrentHp() const;
	bool isDestructable() const;
	int isDestroyed() const;
private:
	int hp;
	bool destructable, destroyed;
};



