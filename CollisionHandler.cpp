#include "CollisionHandler.h"



CollisionHandler::CollisionHandler()
{
}


bool CollisionHandler::isIntersecting(Rect & r1, Rect & r2) const
{
	return r1.rect.getGlobalBounds().intersects(r2.rect.getGlobalBounds());
}

void CollisionHandler::characterWithObstacles(std::unique_ptr<Wrapper> & character, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (auto & obstacle : obstacles)
	{
		if (isIntersecting(*character->rect, *obstacle->rect))
		{
			int distances[4];
			distances[TOP] = abs(obstacle->rect->getBottomEdge() - character->rect->getTopEdge());
			distances[BOT] = abs(obstacle->rect->getTopEdge() - character->rect->getBottomEdge());
			distances[LEFT] = abs(obstacle->rect->getRightEdge() - character->rect->getLeftEdge());
			distances[RIGHT] = abs(obstacle->rect->getLeftEdge() - character->rect->getRightEdge());

			if (topDistanceShortest(distances))
			{
				character->rect->character->setCanMoveUp(false);
			}
			else if (botDistanceShortest(distances))
			{
				character->rect->character->setCanMoveDown(false);
			}
			else if (leftDistanceShortest(distances))
			{
				character->rect->character->setCanMoveLeft(false);
			}
			else if (rightDistanceShortest(distances))
			{
				character->rect->character->setCanMoveRight(false);
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

void CollisionHandler::playerWithEnemies(std::unique_ptr<Wrapper> & player, enemyPair & enemies)
{
	std::vector<bool> enemiesCollidingWithPlayer;

	int enemyIndex = 0;
	bool playerCollision[4] = { false,false,false,false };
	for (auto & iter : enemies)
	{
		Fight::setFightingMode(enemies[enemyIndex].first, false);
		if (isIntersecting(*player->rect, *enemies[enemyIndex].first->rect))
		{
			setEnemyCollidingWithPlayer(enemiesCollidingWithPlayer, enemyIndex, true);

			Fight::setFightingMode(enemies[enemyIndex].first, true);
			//setDamageMessage(enemies[counter].first->rect->character->getAttackDamage(), player, texts);
			Fight::attackMelee(enemies[enemyIndex].first, player);
			Fight::attackMelee(player, enemies[enemyIndex].first);

			int distances[4];
			distances[TOP] = abs(enemies[enemyIndex].first->rect->getBottomEdge() - player->rect->getTopEdge());
			distances[BOT] = abs(enemies[enemyIndex].first->rect->getTopEdge() - player->rect->getBottomEdge());
			distances[LEFT] = abs(enemies[enemyIndex].first->rect->getRightEdge() - player->rect->getLeftEdge());
			distances[RIGHT] = abs(enemies[enemyIndex].first->rect->getLeftEdge() - player->rect->getRightEdge());

			if (topDistanceShortest(distances))
			{
				player->rect->character->setCanMoveUp(false);
				enemies[enemyIndex].first->rect->character->setCanMoveDown(false);
				addBlockedCharacter(Blocked::PLAYERINDEX, (int)Directions::UP);
				addBlockedCharacter(enemyIndex, (int)Directions::DOWN);
				playerCollision[TOP] = true;
			}
			else if (botDistanceShortest(distances))
			{
				player->rect->character->setCanMoveDown(false);
				enemies[enemyIndex].first->rect->character->setCanMoveUp(false);
				addBlockedCharacter(Blocked::PLAYERINDEX, (int)Directions::DOWN);
				addBlockedCharacter(enemyIndex, (int)Directions::UP);
				playerCollision[BOT] = true;
			}
			else if (leftDistanceShortest(distances))
			{
				player->rect->character->setCanMoveLeft(false);
				enemies[enemyIndex].first->rect->character->setCanMoveRight(false);
				addBlockedCharacter(Blocked::PLAYERINDEX, (int)Directions::LEFT);
				addBlockedCharacter(enemyIndex, (int)Directions::RIGHT);
				playerCollision[LEFT] = true;
			}
			else if (rightDistanceShortest(distances))
			{
				player->rect->character->setCanMoveRight(false);
				enemies[enemyIndex].first->rect->character->setCanMoveLeft(false);
				addBlockedCharacter(Blocked::PLAYERINDEX, (int)Directions::RIGHT);
				addBlockedCharacter(enemyIndex, (int)Directions::LEFT);
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

	Delete::removeBlocked(blockedCharacters);
}

void CollisionHandler::enemiesWithEnemies(enemyPair & enemies)
{
	std::vector<bool> enemiesCollidingWithEnemies;
	//nachodza na siebie te zjeby kurwa
	int enemyIndex = 0;
	for (auto & enemy : enemies)
	{
		int otherEnemyIndex = 0;
		for (auto & otherEnemy : enemies)
		{
			if (enemyIndex != otherEnemyIndex)
			{
				if (isIntersecting(*enemies[enemyIndex].first->rect, *enemies[otherEnemyIndex].first->rect))
				{
					setEnemyCollidingWithPlayer(enemiesCollidingWithEnemies, enemyIndex, true); //chyba problem tutaj

					int distances[4];
					distances[TOP] = abs(otherEnemy.first->rect->getBottomEdge() - enemy.first->rect->getTopEdge());
					distances[BOT] = abs(otherEnemy.first->rect->getTopEdge() - enemy.first->rect->getBottomEdge());
					distances[LEFT] = abs(otherEnemy.first->rect->getRightEdge() - enemy.first->rect->getLeftEdge());
					distances[RIGHT] = abs(otherEnemy.first->rect->getLeftEdge() - enemy.first->rect->getRightEdge());

					if (topDistanceShortest(distances))
					{
						enemy.first->rect->character->setCanMoveUp(false);
						addBlockedEnemy(enemyIndex, (int)Directions::UP);
					}
					else if (botDistanceShortest(distances))
					{
						enemy.first->rect->character->setCanMoveDown(false);
						addBlockedEnemy(enemyIndex, (int)Directions::DOWN);
					}
					else if (leftDistanceShortest(distances))
					{
						enemy.first->rect->character->setCanMoveLeft(false);
						addBlockedEnemy(enemyIndex, (int)Directions::LEFT);
					}
					else if (rightDistanceShortest(distances))
					{
						enemy.first->rect->character->setCanMoveRight(false);
						addBlockedEnemy(enemyIndex, (int)Directions::RIGHT);
					}
				}
				else
				{
					setEnemyCollidingWithPlayer(enemiesCollidingWithEnemies, enemyIndex, false);
				}
			}
			otherEnemyIndex++;
		}
		enemyIndex++;
	}

	int bIndex = 0;
	for (auto x : enemiesCollidingWithEnemies)
	{
		std::cout <<bIndex<<" = "<< x<<std::endl;
		bIndex++;
	}

	enemyIndex = 0;
	for (auto & enemy : enemies)
	{
		for (auto & blockedEnemy : blockedEnemies)
		{
			if (enemiesCollidingWithEnemies.size() > 0)
			{
				if (canUnlockEnemyDirection(blockedEnemy, enemiesCollidingWithEnemies[enemyIndex], enemyIndex)) 
				{
					unlockBlockedCharacter(enemy.first, blockedEnemy);
				}
			}
		}
		enemyIndex++;
	}

	//int blockedcounter = 0;
	//for (auto & blockedEnemy : blockedEnemies)
	//	blockedcounter++;
	//std::cout << "ILOSC W BLOCKENEMEMIES = " << blockedcounter << std::endl;

	Delete::removeBlocked(blockedEnemies);

}

void CollisionHandler::projectilesWithEnemies(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies)
{
	for (auto & projectile : projectiles)
	{
		int enemyIndex = projectile->rect->projectile->getEnemyID();
		if (isIntersecting(*projectile->rect, *enemies[enemyIndex].first->rect))
		{
			Fight::attackDistance(projectile, enemies[enemyIndex].first);
			Delete::setProjectileToDestroy(projectile);
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
				Delete::setProjectileToDestroy(projectile);
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
	Delete::setBlockedToDestroy(blocked);
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

void CollisionHandler::addBlockedCharacter(int characterIndex, int direction)
{
	if (possibleToAddBlockedCharacter(characterIndex, direction))
	{
		blockedCharacters.push_back(Blocked(characterIndex, direction));
	}
}

void CollisionHandler::addBlockedEnemy(int enemyIndex, int direction)
{
	if (possibleToAddBlockedEnemy(enemyIndex, direction))
	{
		blockedEnemies.push_back(Blocked(enemyIndex, direction));
	}

}

bool CollisionHandler::possibleToAddBlockedEnemy(int enemyIndex, int direction)
{
	for (auto & blocked : blockedEnemies)
	{
		if (blocked.characterIndex == enemyIndex && blocked.blockedDirection == direction) return false;
	}
	return true;
}


bool CollisionHandler::possibleToAddBlockedCharacter(int characterIndex, int direction)
{
	for (auto & blocked : blockedCharacters)
	{
		if (blocked.characterIndex == characterIndex && blocked.blockedDirection == direction) return false;
	}
	return true;
}

////change from attackDamage to random damage based on attackdamge
//void CollisionHandler::setDamageMessage(int takenHp, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & texts)
//{
//	std::string msg = std::to_string(takenHp);
//	sf::Vector2f pos = { victim->rect->rect.getPosition().x + 14,	victim->rect->rect.getPosition().y - 10 };
//	texts.push_back(std::unique_ptr<Text>(new Text(msg, pos, sf::Color::Red)));
//}
