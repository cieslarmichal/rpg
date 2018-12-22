#include "Shoot.h"


void Shoot::shootEnemy(std::unique_ptr<Wrapper>& player, enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	int enemyIndex = findTargetEnemy(enemies);
	if (enemyIndex == (int)Others::RESET) return;

	int targetX = (int)enemies[enemyIndex].first->rect->getPosition().x;
	int targetY = (int)enemies[enemyIndex].first->rect->getPosition().y;
	int deltaX = targetX - (int)player->rect->getPosition().x;
	int deltaY = targetY - (int)player->rect->getPosition().y;
	double absDistance = std::sqrt(deltaX*deltaX + deltaY * deltaY);
	int flagX = (deltaX >= 0) ? 1 : -1;
	int flagY = (deltaY >= 0) ? 1 : -1;
	double angle = std::atan2(abs(deltaY), abs(deltaX));
	//sprite setting
	sf::Vector2i dimSprite;
	dimSprite.x = 0;
	dimSprite.y = calculateSpriteDimension(flagX, flagY, angle);
	if (absDistance <= 275) // shoot if absolute distance is less than 275
	{
		if (player->timing.getElapsedSeconds() >= 5/(5))
		{
			player->timing.reset();
			Projectile projectile(enemyIndex);
			projectile.setDamage(player->rect->character->getAttackDamage());
			Create::createProjectile(player, projectile, projectiles, dimSprite);
		}
	}
}

int Shoot::findTargetEnemy(enemyPair & enemies)
{
	int counter = 0;
	for (std::pair<std::unique_ptr<Wrapper>, StatusBar > & x : enemies)
	{
		if (enemies[counter].first->rect->character->isMarked())
		{
			return counter;
		}
		counter++;
	}
	return (int)Others::RESET;
}

int Shoot::calculateSpriteDimension(int flagX, int flagY, double angle)
{
	//flagX 1 down, -1 up, flagY same
	int dimY = 0;
	if (flagX == 1)
	{
		if (flagY == -1)
		{
			if (angle >= 0 && angle <= 0.45) dimY = 4 * 64;
			else if (angle > 0.45 && angle <= 1.1) dimY = 3 * 64;
			else dimY = 2 * 64;
		}
		else if (flagY == 1)
		{
			if (angle >= 0 && angle <= 0.45) dimY = 4 * 64;
			else if (angle > 0.45 && angle <= 1.1) dimY = 5 * 64;
			else dimY = 6 * 64;
		}
	}
	else if (flagX == -1)
	{
		if (flagY == -1)
		{
			if (angle >= 0 && angle <= 0.45) dimY = 0;
			else if (angle > 0.45 && angle <= 1.1) dimY = 1 * 64;
			else dimY = 2 * 64;
		}
		else if (flagY == 1)
		{
			if (angle >= 0 && angle <= 0.45) dimY = 0;
			else if (angle > 0.45 && angle <= 1.1) dimY = 7 * 64;
			else dimY = 6 * 64;
		}
	}

	return dimY;
}
