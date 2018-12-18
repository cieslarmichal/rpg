#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(int enemyID);
	//setters
	void setDamage(int);
	void setMovementSpeed(float);
	void setDirection(int);
	void setCounterLifeTime(int);
	void setDestroyed(bool);
	//getters
	int getDamage() const;
	float getMovementSpeed() const;
	int getDirection() const;
	int getEnemyID() const;
	int getCounterLifeTime() const;
	int getLifetime() const;
	bool isDestroyed() const;
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UPRIGHT = 5, UPLEFT = 6, DOWNRIGHT = 7, DOWNLEFT = 8 };
private:
	float movementSpeed;
	sf::Vector2f velocity;
	int enemyID;
	int damage;
	int lifetime, counterLifetime;
	int direction; 
	bool destroyed;
};

