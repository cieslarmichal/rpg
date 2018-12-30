#include "Update.h"

void Update::updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction)
{
	bool isMoving = Movement::movePlayer(*player->rect, direction);
	if (isMoving) player->animation->update(player->rect->character->getDirection());
	player->sprite->setPosition(player->rect->getPosition());
	statBar.updateStatusBar(player);
	player->rect->setEdges();
}

void Update::updateEnemies(enemyPair & enemies, std::unique_ptr<Wrapper> & player)
{
	for (auto & enemy : enemies)
	{
		bool isMoving = Movement::moveEnemy(*enemy.first->rect, *player->rect);
		if (isMoving) enemy.first->animation->update(enemy.first->rect->character->getDirection());
		enemy.first->sprite->setPosition(enemy.first->rect->getPosition());
		enemy.second.updateStatusBar(enemy.first);
		enemy.first->rect->setEdges();
		if (enemy.first->rect->character->getCurrentHp() <= 0)
		{
			enemy.first->rect->character->setDead(true);
		}
	}
}

void Update::updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & obstacle : obstacles)
	{
		obstacle->sprite->setPosition(obstacle->rect->getPosition());
	}
}

void Update::updateText(std::vector<std::unique_ptr<Text>> & texts, sf::View view)
{
	for (auto & text : texts)
	{
		Movement::moveText(*text);
		text->update(view);
	}
}

void Update::updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies)
{
	for (auto & projectile : projectiles)
	{
		Movement::moveProjectile(*projectile->rect, enemies);
		projectile->sprite->setPosition((int)projectile->rect->getPosition().x - 10, (int)projectile->rect->getPosition().y - 15);
	}
}
