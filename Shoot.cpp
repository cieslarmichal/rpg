#include "Shoot.h"


void Shoot::shootEnemy(std::unique_ptr<Wrapper>& player, enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	if (player->rect->character->getWeapon() != (int)Weapons::DISTANCE) return;

	int enemyIndex = findTargetEnemy(enemies);
	if (enemyIndex == (int)Others::RESET) return;

	int targetX = (int)enemies[enemyIndex].first->rect->getPosition().x;
	int targetY = (int)enemies[enemyIndex].first->rect->getPosition().y;
	int deltaX = targetX - (int)player->rect->getPosition().x;
	int deltaY = targetY - (int)player->rect->getPosition().y;

	double absDistance = std::sqrt(deltaX*deltaX + deltaY * deltaY);
	bool positiveX = (deltaX >= 0) ? true : false;
	bool positiveY = (deltaY >= 0) ? true : false;
	double angle = std::atan2(abs(deltaY), abs(deltaX));

	sf::Vector2i dimSprite = Sprite::calculateProjectileSprite(positiveX, positiveY, angle);
	if (absDistance <= 350) // shoot if absolute distance is less than 275
	{
		if (player->timing.getElapsedSeconds() >= 10 / player->rect->character->getAttackSpeed())
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
	int enemyIndex = 0;
	for (auto & enemy : enemies)
	{
		if (enemy.first->rect->character->isMarked())
		{
			return enemyIndex;
		}
		enemyIndex++;
	}
	return (int)Others::RESET;
}
