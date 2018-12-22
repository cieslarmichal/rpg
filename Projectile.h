#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(int enemyID);
	void setDamage(int);
	void setMovementSpeed(float);
	void setDirection(int);
	void setDestroyed(bool);
	int getDamage() const;
	float getMovementSpeed() const;
	int getDirection() const;
	int getEnemyID() const;
	bool isDestroyed() const;
private:
	float movementSpeed;
	int enemyID;
	int damage;
	int direction; 
	bool destroyed = false;
};

