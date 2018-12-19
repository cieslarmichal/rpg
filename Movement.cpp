#include "Movement.h"


Movement::Movement()
{
	std::srand(std::time(NULL));
}


bool Movement::move(Rect & rect, int dirc)
{
	if (dirc > 4 || dirc < 1) return false;
	rect.character->setDirection(dirc);
	if (dirc == UP && rect.character->getCanMoveUp())
	{
		rect.rect.move(0, -rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (dirc == DOWN && rect.character->getCanMoveDown())
	{
		rect.rect.move(0, rect.character->getMovementSpeed());
		rect.character->canMoveEverywhere();
	}
	else if (dirc == LEFT && rect.character->getCanMoveLeft())
	{
		rect.rect.move(-rect.character->getMovementSpeed(),0);
		rect.character->canMoveEverywhere();
	}
	else if (dirc == RIGHT && rect.character->getCanMoveRight())
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
	enemy.character->setCounter(enemy.character->getCounter() + 1);
	if (enemy.character->getCounter() >= enemy.character->getRandomMovementLength())
	{
		enemy.character->setDirection((std::rand() % 4) + 1);
		enemy.character->setRandomMovementLength((std::rand() % 30) + 40);
		enemy.character->setCounter(0);
	}
	return (move(enemy, enemy.character->getDirection()));
}

bool Movement::moveEnemy(Rect & enemy, Rect & player)
{
	int deltaX = enemy.getPosition().x - player.getPosition().x;
	int deltaY = enemy.getPosition().y - player.getPosition().y;
	double absDistance = std::sqrt(deltaX*deltaX + deltaY * deltaY);
	if (absDistance > 300)
	{
		 return moveRandom(enemy);
	}
	else
	{
		if (!enemy.character->isFighting())
		{
			if (std::abs(deltaX) >= std::abs(deltaY))
			{
				(deltaX >= 0) ? move(enemy, LEFT) : move(enemy, RIGHT);
			}
			else
			{
				(deltaY >= 0) ? move(enemy, UP) : move(enemy, DOWN);
			}
		}
		else return false;
	}
	return true;
}



bool Movement::moveText(Text & text)
{
	text.getText().move(0, -text.getMovementSpeed());
	return true;
}

void Movement::moveProjectile(Rect & rect, enemyPair & enemies)
{
	int flagX, flagY; //true shoot with +speed, false with -speed
	int enemyIndex = rect.projectile->getEnemyID();
	int targetX = enemies[enemyIndex].first->rect->getPosition().x;
	int targetY = enemies[enemyIndex].first->rect->getPosition().y;
	int deltaX = targetX - rect.getPosition().x;
	int deltaY = targetY - rect.getPosition().y;
	flagX = (deltaX >= 0) ? 1 : -1;
	flagY = (deltaY >= 0) ? 1 : -1;
	double angle = std::atan2(abs(deltaY), abs(deltaX));

	rect.rect.move(flagX * rect.projectile->getMovementSpeed()*std::cos(angle), flagY * rect.projectile->getMovementSpeed() * std::sin(angle));
}

