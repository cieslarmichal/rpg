#include "Projectile.h"



Projectile::Projectile(int id) :enemyID(id)
{
	movementSpeed = 15.f;
	damage = 1;
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

bool Projectile::isDestroyed() const
{
	return destroyed;
}
