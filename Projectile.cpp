#include "Projectile.h"



Projectile::Projectile(int id)
{
	enemyID = id;
	movementSpeed = 15;
	damage = 1;
	counterLifetime = 0;
	lifetime = 200;
	destroyed = false;
	velocity = { 0,0 };
}

//setters
void Projectile::setDamage(int inp)
{
	damage = inp;
}

void Projectile::setMovementSpeed(float inp)
{
	movementSpeed = inp;
}

void Projectile::setDirection(int inp)
{
	direction = inp;
}

void Projectile::setCounterLifeTime(int inp)
{
	counterLifetime = inp;
}


void Projectile::setDestroyed(bool inp)
{
	destroyed = inp;
}

//getters
int Projectile::getDamage() const
{
	return damage;
}

float Projectile::getMovementSpeed() const
{
	return movementSpeed;
}

int Projectile::getDirection() const
{
	return direction;
}

int Projectile::getEnemyID() const
{
	return enemyID;
}

int Projectile::getCounterLifeTime() const
{
	return counterLifetime;
}

int Projectile::getLifetime() const
{
	return lifetime;
}

bool Projectile::isDestroyed() const
{
	return destroyed;
}