#include "Update.h"

void Update::updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction, int action, std::vector<std::unique_ptr<Text>> & notifications, sf::View view)
{
	bool isMoving = Movement::movePlayer(*player->rect, direction);
	if (isMoving) player->animation->update(player->rect->character->getDirection());
	player->sprite->setPosition(player->rect->getPosition());
	statBar.updateStatusBar(player);
	player->rect->setEdges();

	ChangeWeapon::changeWeapon(action, player);
	std::string levelMessage = LevelManager::update(player->rect->player);
	Create::createLevelMessage(levelMessage, notifications, view);
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

void Update::updateHUDInfo(std::unique_ptr<Wrapper> & player, std::vector <std::unique_ptr<Text>> & texts, sf::Vector2u windowSize)
{
	for (auto & text : texts)
	{
		if (text->getHUDtype() == "HP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2);
			text->updateHUD(HUDposition, player->rect->player->getCurrentHp(), player->rect->player->getMaxHp());
		}
		else if (text->getHUDtype() == "EXP")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 20);
			text->updateHUD(HUDposition, player->rect->player->getExperience(), LevelManager::getRequireExperience());
		}
		else if (text->getHUDtype() == "COINS")
		{
			sf::Vector2f HUDposition = sf::Vector2f(player->rect->getPosition().x - (float)windowSize.x / 2, player->rect->getPosition().y - (float)windowSize.y / 2 + 40);
			text->updateHUD(HUDposition, player->rect->player->getCoins());
		}
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
