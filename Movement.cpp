#include "Movement.h"


bool Movement::move(Rect & rect, int dirc)
{
	if (dirc > (int)Directions::RIGHT || dirc < (int)Directions::UP) return false;
	rect.character->setDirection(dirc);

	if (dirc == (int)Directions::UP && rect.character->getCanMoveUp())
	{
		rect.rect.move(0, -rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (dirc == (int)Directions::DOWN && rect.character->getCanMoveDown())
	{
		rect.rect.move(0, rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (dirc == (int)Directions::LEFT && rect.character->getCanMoveLeft())
	{
		rect.rect.move(-rect.character->getMovementSpeed(),0);
		rect.character->canMoveEverywhere();
	}
	else if (dirc == (int)Directions::RIGHT && rect.character->getCanMoveRight())
	{
		rect.rect.move(rect.character->getMovementSpeed(),0);
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
		enemy.character->setDirection((std::rand() % 4) + 1);
		enemy.character->setRandomMovementLength((std::rand() % 30) + 40);
		enemy.character->setWalkCounter(0);
	}
	return (move(enemy, enemy.character->getDirection()));
}

bool Movement::moveEnemy(Rect & enemy, Rect & player)
{
	int deltaX = (int)(enemy.getPosition().x - player.getPosition().x);
	int deltaY = (int)(enemy.getPosition().y - player.getPosition().y);
	double absDistance = std::sqrt(deltaX*deltaX + deltaY * deltaY);
	if (absDistance > 300)
	{
		 return moveRandom(enemy);
	}
	else if (!enemy.character->isFighting())
	{
		if (std::abs(deltaX) >= std::abs(deltaY))
		{
			(deltaX >= 0) ? move(enemy, (int)Directions::LEFT) : move(enemy, (int)Directions::RIGHT);
		}
		else
		{
			(deltaY >= 0) ? move(enemy, (int)Directions::UP) : move(enemy, (int)Directions::DOWN);
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
