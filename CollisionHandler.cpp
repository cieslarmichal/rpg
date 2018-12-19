#include "CollisionHandler.h"



CollisionHandler::CollisionHandler()
{
}


bool CollisionHandler::isIntersecting(Rect & r1, Rect & r2) const
{
	return r1.rect.getGlobalBounds().intersects(r2.rect.getGlobalBounds());
}

bool CollisionHandler::playerWithObstacles(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int counter = 0;
	for (auto & iter : obstacles)
	{
		bool case1 = false, case2 = false, case3 = false, case4 = false;
		if (isIntersecting(*player->rect, *obstacles[counter]->rect))
		{
			int topDistance = abs(obstacles[counter]->rect->getBottomEdge() - player->rect->getTopEdge()); //distance up
			int bottomDistance = abs(obstacles[counter]->rect->getTopEdge() - player->rect->getBottomEdge()); //distance down
			int leftDistance = abs(obstacles[counter]->rect->getRightEdge() - player->rect->getLeftEdge()); //distance left
			int rightDistance = abs(obstacles[counter]->rect->getLeftEdge() - player->rect->getRightEdge()); //distance right

			//case 1 cant move up
			if (topDistance < bottomDistance && topDistance < leftDistance && topDistance < rightDistance)
			{
				case1 = true;
			}
			//case 2 cant move down
			else if (bottomDistance < topDistance && bottomDistance < leftDistance && bottomDistance < rightDistance)
			{
				case2 = true;
			}
			//case 3 cant move left
			else if (leftDistance < bottomDistance && leftDistance < rightDistance && leftDistance < topDistance)
			{
				case3 = true;
			}
			//case 4 cant move right 
			else if (rightDistance < bottomDistance && rightDistance < leftDistance && rightDistance < topDistance)
			{
				case4 = true;
			}
		if (case1) player->rect->character->setCanMoveUp(false);
		if (case2) player->rect->character->setCanMoveDown(false);
		if (case3) player->rect->character->setCanMoveLeft(false);
		if (case4) player->rect->character->setCanMoveRight(false);
		}
		counter++;
	}
	return true;
}

//wladowac funcje playerwithobstacles tutauj z wyzej
bool CollisionHandler::enemiesWithObstacles(enemyPair & enemies, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int counter = 0;
	for (auto & iter : obstacles)
	{
		int counter2 = 0;
		for (auto & iter : enemies)
		{
			bool case1 = false, case2 = false, case3 = false, case4 = false;
			if (isIntersecting(*enemies[counter2].first->rect, *obstacles[counter]->rect))
			{
				int topDistance = abs(obstacles[counter]->rect->getBottomEdge() - enemies[counter2].first->rect->getTopEdge()); //distance up
				int bottomDistance = abs(obstacles[counter]->rect->getTopEdge() - enemies[counter2].first->rect->getBottomEdge()); //distance down
				int leftDistance = abs(obstacles[counter]->rect->getRightEdge() - enemies[counter2].first->rect->getLeftEdge()); //distance left
				int rightDistance = abs(obstacles[counter]->rect->getLeftEdge() - enemies[counter2].first->rect->getRightEdge()); //distance right

				if (topDistance < bottomDistance && topDistance < leftDistance && topDistance < rightDistance) //case 1 cant move up
				{
					case1 = true;
				}
				else if (bottomDistance < topDistance && bottomDistance < leftDistance && bottomDistance < rightDistance) //case 2 cant move down
				{
					case2 = true;
				}
				else if (leftDistance < bottomDistance && leftDistance < rightDistance && leftDistance < topDistance) //case 3 cant move left
				{
					case3 = true;
				}
				else if (rightDistance < bottomDistance && rightDistance < leftDistance && rightDistance < topDistance) //case 4 cant move right 
				{
					case4 = true;
				}
				if (case1) enemies[counter2].first->rect->character->setCanMoveUp(false);
				if (case2) enemies[counter2].first->rect->character->setCanMoveDown(false);
				if (case3) enemies[counter2].first->rect->character->setCanMoveLeft(false);
				if (case4) enemies[counter2].first->rect->character->setCanMoveRight(false);
			}
			counter2++;
		}
		counter++;
	}
	return true;
}

bool CollisionHandler::playerWithEnemies(std::unique_ptr<Wrapper> & player, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts)
{
	//time measurement
	elapsed1 = clock1.getElapsedTime();
	elapsed2 = clock2.getElapsedTime();

	int counter = 0;
	bool anyCollision = false;
	for (auto & iter : enemies)
	{
		enemies[counter].first->rect->character->setFighting(false);
		bool case1 = false, case2 = false, case3 = false, case4 = false;
		if (isIntersecting(*player->rect, *enemies[counter].first->rect))
		{
			enemies[counter].first->rect->character->setFighting(true);
			//player gets damage
			if (elapsed1.asSeconds() >= 1)
			{
				clock1.restart();
				std::cout << " " << enemies[counter].first->rect->character->isFighting() << std::endl;
				int playerDamagedHp = player->rect->character->getCurrentHp() - enemies[counter].first->rect->character->getAttackDamage();
				player->rect->character->setCurrentHp(playerDamagedHp);
				setDamageMessage(enemies[counter].first->rect->character->getAttackDamage(), player, texts);
			}
			//enemies get damage
			if (elapsed2.asSeconds() >= 0.5 && enemies[counter].first->rect->character->isMarked())
			{
				clock2.restart();
				int enemyDamagedHp = enemies[counter].first->rect->character->getCurrentHp() - player->rect->character->getAttackDamage();
				enemies[counter].first->rect->character->setCurrentHp(enemyDamagedHp);
				setDamageMessage(player->rect->character->getAttackDamage(),enemies[counter].first, texts);
			}

			int topDistance = abs(enemies[counter].first->rect->getBottomEdge() - player->rect->getTopEdge()); //distance up
			int bottomDistance = abs(enemies[counter].first->rect->getTopEdge() - player->rect->getBottomEdge()); //distance down
			int leftDistance = abs(enemies[counter].first->rect->getRightEdge() - player->rect->getLeftEdge()); //distance left
			int rightDistance = abs(enemies[counter].first->rect->getLeftEdge() - player->rect->getRightEdge()); //distance right

			if (topDistance < bottomDistance && topDistance < leftDistance && topDistance < rightDistance) // player cant go up, enemy cant go down
			{
				player->rect->character->setCanMoveUp(false);
				enemies[counter].first->rect->character->setCanMoveDown(false);
				playerCantMove = UP;
				enemyCantMove = DOWN;
				anyCollision = true;
				enemyIndex = counter;
			}
			else if (bottomDistance < topDistance && bottomDistance < leftDistance && bottomDistance < rightDistance) // player cant go down, enemy cant go up
			{
				player->rect->character->setCanMoveDown(false);
				enemies[counter].first->rect->character->setCanMoveUp(false);
				playerCantMove = DOWN;
				enemyCantMove = UP;
				anyCollision = true;
				enemyIndex = counter;
			}
			else if (leftDistance < bottomDistance && leftDistance < rightDistance && leftDistance < topDistance) // player cant go left, enemy cant go right
			{
				player->rect->character->setCanMoveLeft(false);
				enemies[counter].first->rect->character->setCanMoveRight(false);
				playerCantMove = LEFT;
				enemyCantMove = RIGHT;
				anyCollision = true;
				enemyIndex = counter;
			}
			else if (rightDistance < bottomDistance && rightDistance < leftDistance && rightDistance < topDistance) // player cant go right, enemy cant go left
			{
				player->rect->character->setCanMoveRight(false);
				enemies[counter].first->rect->character->setCanMoveLeft(false);
				playerCantMove = RIGHT;
				enemyCantMove = LEFT;
				anyCollision = true;
				enemyIndex = counter;
			}
		}
		counter++;
	}
	if (!anyCollision)
	{
		//enemyIndex = OUT;
		return false;
	}
	return true;
}


bool CollisionHandler::projectilesWithEnemies(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies, std::vector<std::unique_ptr<Text>> & texts)
{
	int counter = 0;
	for (auto & iter : projectiles)
	{
		int enemyIndex = projectiles[counter]->rect->projectile->getEnemyID();
		if (isIntersecting(*projectiles[counter]->rect, *enemies[enemyIndex].first->rect))
		{
			projectiles[counter]->rect->projectile->setDestroyed(true);
			int enemyDamagedHp = enemies[enemyIndex].first->rect->character->getCurrentHp() - projectiles[counter]->rect->projectile->getDamage();
			enemies[enemyIndex].first->rect->character->setCurrentHp(enemyDamagedHp);
			setDamageMessage(projectiles[counter]->rect->projectile->getDamage(), enemies[enemyIndex].first, texts);
		}
		counter++;
	}
	return true;
}

bool CollisionHandler::projectilesWithWalls(std::vector<std::unique_ptr<Wrapper>> & projectiles, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int counter = 0;
	for (auto & iter : projectiles)
	{
		int counter2 = 0;
		for (auto & iter : obstacles)
		{
			if (isIntersecting(*projectiles[counter]->rect, *obstacles[counter2]->rect))
			{
				projectiles[counter]->rect->projectile->setDestroyed(true);
			}
			counter2++;
		}
		counter++;
	}
	return true;
}

//change from attackDamage to random damage based on attackdamge
void CollisionHandler::setDamageMessage(int takenHp, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & texts)
{
	std::string msg = std::to_string(takenHp);
	sf::Vector2f pos = { victim->rect->rect.getPosition().x+14,	victim->rect->rect.getPosition().y -10 };
	texts.push_back(std::unique_ptr<Text>(new Text(msg, pos, sf::Color::Red)));
}



