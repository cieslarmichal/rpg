#include "Update.h"

void Update::updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications)
{
	bool isMoving = Movement::movePlayer(*player->rect, direction);
	if (isMoving) player->animation->update(player->rect->character->getDirection());
	player->sprite->setPosition(player->rect->getPosition());
	statBar.updateStatusBar(player->rect->character->getCurrentHp(), player->rect->character->getMaxHp(),
		player->rect->character->getName(), player->rect->getPosition());
	player->rect->setEdges();

	player->rect->player->useItem(action);
	player->rect->player->changeChosenItem(action);
	player->rect->player->dropItem(action);
	std::string levelMessage = LevelManager::update(player->rect->player);
	Create::createLevelMessage(levelMessage, notifications);
}

void Update::updateNpc(vectorOfCharacters & npcs)
{
	for (auto & npc : npcs)
	{
		npc.first->sprite->setPosition(npc.first->rect->getPosition());
	}
}

void Update::updateEnemies(vectorOfCharacters & enemies, std::unique_ptr<Wrapper> & player)
{
	for (auto & enemy : enemies)
	{
		bool isMoving = Movement::moveEnemy(*enemy.first->rect, *player->rect);
		if (isMoving) enemy.first->animation->update(enemy.first->rect->character->getDirection());
		enemy.first->sprite->setPosition(enemy.first->rect->getPosition());
		enemy.second.updateStatusBar(enemy.first->rect->character->getCurrentHp(), enemy.first->rect->character->getMaxHp(),
			enemy.first->rect->character->getName(), enemy.first->rect->getPosition());
		enemy.first->rect->setEdges();
	}
}

void Update::updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & obstacle : obstacles)
	{
		obstacle->sprite->setPosition(obstacle->rect->getPosition());
	}
}

void Update::updateItems(std::vector<std::unique_ptr<Wrapper>> & items)
{
	for (auto & item : items)
	{
		item->sprite->setPosition(item->rect->getPosition());
	}
}

void Update::updateText(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Text>> & texts)
{
	for (auto & text : texts)
	{
		Movement::moveText(*text);
		sf::Vector2f position = sf::Vector2f(player->rect->getPosition().x - 150, player->rect->getPosition().y - 120);
		text->update(position);
	}
}

void Update::updateHUD(std::unique_ptr<Wrapper> & player, HUD & hud, sf::Vector2u windowSize)
{
	hud.update(player, windowSize);
}

void Update::updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, vectorOfCharacters & enemies)
{
	for (auto & projectile : projectiles)
	{
		Movement::moveProjectile(*projectile->rect, enemies);
		projectile->sprite->setPosition((int)projectile->rect->getPosition().x - 10, (int)projectile->rect->getPosition().y - 15);
	}
}


