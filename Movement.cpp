#include "Movement.h"


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

bool Movement::moveRandom(Rect & enemy)
{
	enemy.character->setWalkCounter(enemy.character->getWalkCounter() + 1);
	if (enemy.character->getWalkCounter() >= enemy.character->getRandomMovementLength())
	{
		int random = std::rand() % 4;
		std::cout << random << std::endl;
		enemy.character->setDirection(random);
		enemy.character->setRandomMovementLength((std::rand() % 30) + 40);
		enemy.character->setWalkCounter(0);
	}
	return (move(enemy, enemy.character->getDirection()));
}

bool Movement::moveEnemy(Rect & enemy, Rect & player)
{
	int positiveX = (int)(enemy.getPosition().x - player.getPosition().x);
	int positiveY = (int)(enemy.getPosition().y - player.getPosition().y);
	double absoluteDistance = std::sqrt(positiveX*positiveX + positiveY * positiveY);
	if (absoluteDistance > 300)
	{
		return moveRandom(enemy);
	}
	else if (!enemy.character->isFighting())
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
		return false;
	}
	return true;
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
