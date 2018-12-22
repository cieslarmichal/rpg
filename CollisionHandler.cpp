#include "CollisionHandler.h"



CollisionHandler::CollisionHandler()
{
}


bool CollisionHandler::isIntersecting(Rect & r1, Rect & r2) const
{
	return r1.rect.getGlobalBounds().intersects(r2.rect.getGlobalBounds());
}

void CollisionHandler::characterWithObstacles(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & obstacle : obstacles)
	{
		if (isIntersecting(*player->rect, *obstacle->rect))
		{
			int distances[4];
			distances[TOP] = abs(obstacle->rect->getBottomEdge() - player->rect->getTopEdge());
			distances[BOT] = abs(obstacle->rect->getTopEdge() - player->rect->getBottomEdge());
			distances[LEFT] = abs(obstacle->rect->getRightEdge() - player->rect->getLeftEdge());
			distances[RIGHT] = abs(obstacle->rect->getLeftEdge() - player->rect->getRightEdge());

			if (topDistanceShortest(distances))
			{
				player->rect->character->setCanMoveUp(false);
			}
			else if (botDistanceShortest(distances))
			{
				player->rect->character->setCanMoveDown(false);
			}
			else if (leftDistanceShortest(distances))
			{
				player->rect->character->setCanMoveLeft(false);
			}
			else if (rightDistanceShortest(distances))
			{
				player->rect->character->setCanMoveRight(false);
			}
		}
	}
}

void CollisionHandler::enemiesWithObstacles(enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & enemy : enemies)
	{
		characterWithObstacles(enemy.first, obstacles);
	}
}

void CollisionHandler::playerWithEnemies(std::unique_ptr<Wrapper> & player, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts)
{
	std::vector<bool> enemiesCollidingWithPlayer;

	int enemyIndex = 0;
	bool playerCollision[4] = { false,false,false,false };
	for (auto & iter : enemies)
	{
		Fight::setFighting(enemies[enemyIndex].first, false);
		if (isIntersecting(*player->rect, *enemies[enemyIndex].first->rect))
		{
			setEnemyCollidingWithPlayer(enemiesCollidingWithPlayer, enemyIndex, true);

			Fight::setFighting(enemies[enemyIndex].first, true);
			//setDamageMessage(enemies[counter].first->rect->character->getAttackDamage(), player, texts);
			Fight::attack(enemies[enemyIndex].first, player);
			Fight::attack(player, enemies[enemyIndex].first);

			int distances[4];
			distances[TOP] = abs(enemies[enemyIndex].first->rect->getBottomEdge() - player->rect->getTopEdge());
			distances[BOT] = abs(enemies[enemyIndex].first->rect->getTopEdge() - player->rect->getBottomEdge());
			distances[LEFT] = abs(enemies[enemyIndex].first->rect->getRightEdge() - player->rect->getLeftEdge());
			distances[RIGHT] = abs(enemies[enemyIndex].first->rect->getLeftEdge() - player->rect->getRightEdge());

			if (topDistanceShortest(distances))
			{
				player->rect->character->setCanMoveUp(false);
				enemies[enemyIndex].first->rect->character->setCanMoveDown(false);
				blockedCharacters.push_back(Blocked(Blocked::PLAYERINDEX, (int)Directions::UP));
				blockedCharacters.push_back(Blocked(enemyIndex, (int)Directions::DOWN));
				playerCollision[TOP] = true;
			}
			else if (botDistanceShortest(distances))
			{
				player->rect->character->setCanMoveDown(false);
				enemies[enemyIndex].first->rect->character->setCanMoveUp(false);
				blockedCharacters.push_back(Blocked(Blocked::PLAYERINDEX, (int)Directions::DOWN));
				blockedCharacters.push_back(Blocked(enemyIndex, (int)Directions::UP));
				playerCollision[BOT] = true;
			}
			else if (leftDistanceShortest(distances))
			{
				player->rect->character->setCanMoveLeft(false);
				enemies[enemyIndex].first->rect->character->setCanMoveRight(false);
				blockedCharacters.push_back(Blocked(Blocked::PLAYERINDEX, (int)Directions::LEFT));
				blockedCharacters.push_back(Blocked(enemyIndex, (int)Directions::RIGHT));
				playerCollision[LEFT] = true;
			}
			else if (rightDistanceShortest(distances))
			{
				player->rect->character->setCanMoveRight(false);
				enemies[enemyIndex].first->rect->character->setCanMoveLeft(false);
				blockedCharacters.push_back(Blocked(Blocked::PLAYERINDEX, (int)Directions::RIGHT));
				blockedCharacters.push_back(Blocked(enemyIndex, (int)Directions::LEFT));
				playerCollision[RIGHT] = true;
			}
		}
		else
		{
			setEnemyCollidingWithPlayer(enemiesCollidingWithPlayer, enemyIndex, false);
		}
		enemyIndex++;
	}


	enemyIndex = 0;
	for (auto & enemy : enemies)
	{
		for (auto & blockedEnemy : blockedCharacters)
		{
			if (canUnlockEnemyDirection(blockedEnemy, enemiesCollidingWithPlayer[enemyIndex], enemyIndex))
			{
				unlockBlockedCharacter(enemy.first, blockedEnemy);
			}
		}
		enemyIndex++;
	}

	for (auto & blockedPlayer : blockedCharacters)
	{
		if (canUnclockPlayerDirection(blockedPlayer, playerCollision))
		{
			unlockBlockedCharacter(player, blockedPlayer);

		}
	}

	blockedCharacters.erase(std::remove_if(blockedCharacters.begin(), blockedCharacters.end(), [](const Blocked & blocked) {return blocked.isDestroyed(); }), blockedCharacters.end());
}

void CollisionHandler::enemiesWithEnemies(enemyPair & enemies)
{

}

void CollisionHandler::projectilesWithEnemies(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts)
{
	for (auto & projectile : projectiles)
	{
		int enemyIndex = projectile->rect->projectile->getEnemyID();
		if (isIntersecting(*projectile->rect, *enemies[enemyIndex].first->rect))
		{
			Fight::attack(projectile, enemies[enemyIndex].first);
			projectile->rect->projectile->setDestroyed(true);
			//setDamageMessage(projectile->rect->projectile->getDamage(), enemies[enemyIndex].first, texts);
		}
	}
}

void CollisionHandler::projectilesWithWalls(std::vector<std::unique_ptr<Wrapper>> & projectiles, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & projectile : projectiles)
	{
		for (auto & obstacle : obstacles)
		{
			if (isIntersecting(*projectile->rect, *obstacle->rect))
			{
				projectile->rect->projectile->setDestroyed(true);
			}
		}
	}
}


bool CollisionHandler::topDistanceShortest(int * distances)
{
	return (distances[TOP] < distances[BOT] && distances[TOP] < distances[LEFT] && distances[TOP] < distances[RIGHT]);
}

bool CollisionHandler::botDistanceShortest(int * distances)
{
	return (distances[BOT] < distances[TOP] && distances[BOT] < distances[LEFT] && distances[BOT] < distances[RIGHT]);

}

bool CollisionHandler::leftDistanceShortest(int * distances)
{
	return (distances[LEFT] < distances[BOT] && distances[LEFT] < distances[TOP] && distances[LEFT] < distances[RIGHT]);

}

bool CollisionHandler::rightDistanceShortest(int * distances)
{
	return (distances[RIGHT] < distances[BOT] && distances[RIGHT] < distances[LEFT] && distances[RIGHT] < distances[TOP]);

}

bool CollisionHandler::canUnclockPlayerDirection(const Blocked & blocked, bool * playerCollision)
{
	bool playerIndex = (blocked.characterIndex == Blocked::PLAYERINDEX);
	bool canUnlockTop = (blocked.blockedDirection == (int)Directions::UP && !playerCollision[TOP]);
	bool canUnlockBot = (blocked.blockedDirection == (int)Directions::DOWN && !playerCollision[BOT]);
	bool canUnlockLeft = (blocked.blockedDirection == (int)Directions::LEFT && !playerCollision[LEFT]);
	bool canUnlockRight = (blocked.blockedDirection == (int)Directions::RIGHT && !playerCollision[RIGHT]);

	return (playerIndex && (canUnlockTop || canUnlockBot || canUnlockLeft || canUnlockRight));
}

bool CollisionHandler::canUnlockEnemyDirection(const Blocked & blocked, bool enemyCollidingWithPlayer, int enemyIndex)
{
	return (!enemyCollidingWithPlayer && blocked.characterIndex == enemyIndex);
}

void CollisionHandler::unlockBlockedCharacter(std::unique_ptr<Wrapper> & character, Blocked & blocked)
{
	character->rect->character->setCanMoveNum(blocked.blockedDirection);
	blocked.destroyed = true;
}

void CollisionHandler::setEnemyCollidingWithPlayer(std::vector<bool> & enemiesCollidingWithPlayer, int enemyIndex, bool isColliding)
{
	if (enemyIndex >= (int)enemiesCollidingWithPlayer.size())
	{
		enemiesCollidingWithPlayer.push_back(isColliding);
	}
	else
	{
		enemiesCollidingWithPlayer[enemyIndex] = isColliding;
	}
}

//change from attackDamage to random damage based on attackdamge
void CollisionHandler::setDamageMessage(int takenHp, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & texts)
{
	std::string msg = std::to_string(takenHp);
	sf::Vector2f pos = { victim->rect->rect.getPosition().x + 14,	victim->rect->rect.getPosition().y - 10 };
	texts.push_back(std::unique_ptr<Text>(new Text(msg, pos, sf::Color::Red)));
}