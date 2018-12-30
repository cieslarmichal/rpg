#include "Movement.h"

TimeHandler Movement::enemyTimer;

bool Movement::move(Rect & rect, int direction)
{
	rect.character->setDirection(direction);

	if (direction == (int)Directions::UP && rect.character->getCanMoveUp())
	{
		rect.rect.move(0, -rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (direction == (int)Directions::DOWN && rect.character->getCanMoveDown())
	{
		rect.rect.move(0, rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (direction == (int)Directions::LEFT && rect.character->getCanMoveLeft())
	{
		rect.rect.move(-rect.character->getMovementSpeed(), 0);
		rect.character->canMoveEverywhere();
	}
	else if (direction == (int)Directions::RIGHT && rect.character->getCanMoveRight())
	{
		rect.rect.move(rect.character->getMovementSpeed(), 0);
		rect.character->canMoveEverywhere();
	}

	if (!rect.character->getCanMoveRight() || !rect.character->getCanMoveLeft() ||
		!rect.character->getCanMoveUp() || !rect.character->getCanMoveDown()) return false;

	return true;
}

bool Movement::movePlayer(Rect & player, int direction)
{
	if (direction != (int)Others::RESET || player.character->target == sf::Vector2i{ -1,-1 })
	{
		player.character->target = sf::Vector2i{ -1,-1 };
		return move(player, direction);
	}
	else if (player.character->target != sf::Vector2i{ -1,-1 })
	{
		if (enemyTimer.getElapsedSeconds() >= 0.5 || player.character->nextMove == sf::Vector2i(player.getPosition()))
		{
			enemyTimer.reset();
			player.character->pathfinding.initializeStartEnd(player.getPosition(), sf::Vector2f(player.character->target));
			player.character->nextMove = player.character->pathfinding.solveAStar();
		}

		if (player.character->nextMove == sf::Vector2i(-1, -1))
		{
			return move(player, direction);
		}
		else
		{
			int xdiff = (int)(player.character->nextMove.x - (int)player.getPosition().x);
			int ydiff = (int)(player.character->nextMove.y - (int)player.getPosition().y);

			if ((int)player.getPosition().x != player.character->nextMove.x && player.character->getCanMoveRight() && xdiff > 0) return move(player, (int)Directions::RIGHT);
			else if ((int)player.getPosition().x != player.character->nextMove.x && player.character->getCanMoveLeft() && xdiff < 0) return move(player, (int)Directions::LEFT);
			else if ((int)player.getPosition().y != player.character->nextMove.y && player.character->getCanMoveUp() && ydiff < 0) return move(player, (int)Directions::UP);
			else if ((int)player.getPosition().y != player.character->nextMove.y && player.character->getCanMoveDown() && ydiff > 0) return move(player, (int)Directions::DOWN);
		}
	}
	return false;
}


bool Movement::moveRandom(Rect & enemy)
{
	enemy.character->setWalkCounter(enemy.character->getWalkCounter() + 1);
	if (enemy.character->getWalkCounter() >= enemy.character->getRandomMovementLength())
	{
		int random = std::rand() % 4;
		enemy.character->setDirection(random);
		enemy.character->setRandomMovementLength((std::rand() % 30) + 40);
		enemy.character->setWalkCounter(0);
	}
	return (move(enemy, enemy.character->getDirection()));
}

bool Movement::moveEnemy(Rect & enemy, Rect & player)
{
	int positiveX = (int)((int)enemy.getPosition().x - (int)player.getPosition().x);
	int positiveY = (int)((int)enemy.getPosition().y - (int)player.getPosition().y);
	double absoluteDistance = std::sqrt(positiveX*positiveX + positiveY * positiveY);
	if (absoluteDistance > 400)
	{
		return moveRandom(enemy);
	}
	else if (!enemy.character->isFighting())
	{
		if (enemyTimer.getElapsedSeconds() >= 1.5 || enemy.character->nextMove == sf::Vector2i(enemy.getPosition()))
		{
			enemyTimer.reset();
			enemy.character->pathfinding.initializeStartEnd(enemy.getPosition(), player.getPosition());
			enemy.character->nextMove = enemy.character->pathfinding.solveAStar();
		}

		if (enemy.character->nextMove == sf::Vector2i(-1, -1))
		{
			if (std::abs(positiveX) >= std::abs(positiveY))
			{
				if (positiveX >= 0) return move(enemy, (int)Directions::LEFT);
				else return move(enemy, (int)Directions::RIGHT);
			}
			else
			{
				if (positiveY >= 0) return move(enemy, (int)Directions::UP);
				else return move(enemy, (int)Directions::DOWN);
			}
		}
		else
		{
			int xdiff = (int)(enemy.character->nextMove.x - enemy.getPosition().x);
			int ydiff = (int)(enemy.character->nextMove.y - enemy.getPosition().y);

			if ((int)enemy.getPosition().x != enemy.character->nextMove.x && enemy.character->getCanMoveRight() && xdiff > 0) return move(enemy, (int)Directions::RIGHT);
			else if ((int)enemy.getPosition().x != enemy.character->nextMove.x && enemy.character->getCanMoveLeft() && xdiff < 0) return move(enemy, (int)Directions::LEFT);
			else if ((int)enemy.getPosition().y != enemy.character->nextMove.y && enemy.character->getCanMoveUp() && ydiff < 0) return move(enemy, (int)Directions::UP);
			else if ((int)enemy.getPosition().y != enemy.character->nextMove.y && enemy.character->getCanMoveDown() && ydiff > 0) return move(enemy, (int)Directions::DOWN);
		}
	}
	return false;
}

void Movement::moveText(Text & text)
{
	text.getText().move(0, -text.getMovementSpeed());
}

void Movement::moveProjectile(Rect & rect, enemyPair & enemies)
{
	int flagX, flagY; //true shoot with +speed, false with -speed
	int enemyIndex = rect.projectile->getEnemyID();
	int targetX = (int)(enemies[enemyIndex].first->rect->getPosition().x);
	int targetY = (int)(enemies[enemyIndex].first->rect->getPosition().y);
	int deltaX = (int)(targetX - rect.getPosition().x);
	int deltaY = (int)(targetY - rect.getPosition().y);
	flagX = (deltaX >= 0) ? 1 : -1;
	flagY = (deltaY >= 0) ? 1 : -1;
	float angle = (float)std::atan2(abs(deltaY), abs(deltaX));

	rect.rect.move(flagX * rect.projectile->getMovementSpeed()*std::cos(angle), flagY * rect.projectile->getMovementSpeed() * std::sin(angle));
}
