#include "EnemySpawner.h"

int EnemySpawner::amountOfEnemies{ 0 };

EnemySpawner::EnemySpawner()
{
	// name, hp, attackDamage, attackSpeed, movementSpeed, experience, lootChance
	characterSkeleton = std::make_unique<Skeleton>(Skeleton("Skeleton", 200, 15, 3, 1, 120, 0.35f));
	characterSkeletonBerserker = std::make_unique<SkeletonBerserker>(SkeletonBerserker("Berserker", 400, 40, 5, 4, 1000, 0.5f));
	characterDragon = std::make_unique<Dragon>(Dragon("Dragon", 1000, 25, 2, 1, 400, 0.4f));
}

void EnemySpawner::spawnSkeleton(vectorOfCharacters & enemies, sf::Vector2f respawnPosition)
{
	if (!(amountOfEnemies <= MAX_ENEMIES_NUMBER)) return;

	if (respawnPosition == sf::Vector2f{ RANDOM,RANDOM })
	{
		respawnPosition = getRandomPosition();
	}

	amountOfEnemies++;
	Create::createSkeleton(*characterSkeleton, enemies, respawnPosition);
}

void EnemySpawner::spawnSkeletonBerserker(vectorOfCharacters & enemies, sf::Vector2f respawnPosition)
{
	if (!(amountOfEnemies <= MAX_ENEMIES_NUMBER)) return;

	if (respawnPosition == sf::Vector2f{ RANDOM,RANDOM })
	{
		respawnPosition = getRandomPosition();
	}

	amountOfEnemies++;
	Create::createSkeletonBerserker(*characterSkeletonBerserker, enemies, respawnPosition);
}

void EnemySpawner::spawnDragon(vectorOfCharacters & enemies, sf::Vector2f respawnPosition)
{
	if (!(amountOfEnemies <= MAX_ENEMIES_NUMBER)) return;

	if (respawnPosition == sf::Vector2f{ RANDOM,RANDOM })
	{
		respawnPosition = getRandomPosition();
	}

	amountOfEnemies++;
	Create::createDragon(*characterDragon, enemies, respawnPosition);
}

void EnemySpawner::spawnRandomEnemy(vectorOfCharacters & enemies, sf::Vector2f respawnPosition)
{
	switch (getRandomEnemyType())
	{
	case Enemy::EnemyType::SKELETON:
		spawnSkeleton(enemies, respawnPosition);
		break;
	case Enemy::EnemyType::SKELETON_BERSERKER:
		spawnSkeletonBerserker(enemies, respawnPosition);
		break;
	case Enemy::EnemyType::DRAGON:
		spawnDragon(enemies, respawnPosition);
		break;
	}
}

void EnemySpawner::setAmountOfEnemies(int inp)
{
	amountOfEnemies = inp;
}

int EnemySpawner::getAmountOfEnemies()
{
	return amountOfEnemies;
}

void EnemySpawner::initializeObjectsPositions(std::vector<std::unique_ptr<Tile>>& mapPositions)
{
	for (auto & mp : mapPositions)
	{
		obstacles.push_back(std::unique_ptr<Tile>(new Tile(mp->getPosition(), true, false)));
	}
}

void EnemySpawner::updateObjectsPositions(std::vector<std::unique_ptr<Tile>>& mapPositions)
{
	obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](std::unique_ptr<Tile> & mp) {return mp->isEnemy(); }), obstacles.end());

	for (auto & mp : mapPositions)
	{
		obstacles.push_back(std::unique_ptr<Tile>(new Tile(mp->getPosition(), true, true)));
	}
}

int EnemySpawner::getRandomEnemyType() const
{
	return Random::getRandomNumber(0, 2);
}

sf::Vector2f EnemySpawner::getRandomPosition() const
{
	sf::Vector2i randomPosition = { Random::getRandomNumber(0,MAP_WIDTH),Random::getRandomNumber(0,MAP_HEIGHT) };
	randomPosition = { randomPosition.x * 40, randomPosition.y * 40 };

	while (!isPossibleToAddPosition(randomPosition))
	{
		randomPosition = { Random::getRandomNumber(0,MAP_WIDTH),Random::getRandomNumber(0,MAP_HEIGHT) };
		randomPosition = { randomPosition.x * 40, randomPosition.y * 40 };
	}

	return sf::Vector2f(randomPosition);
}

bool EnemySpawner::isPossibleToAddPosition(sf::Vector2i position) const
{
	for (auto & obstacle : obstacles)
	{
		if (!isPositionFree(position, sf::Vector2i(obstacle->getPosition())))
		{
			return false;
		}
	}
	return true;
}

bool EnemySpawner::isPositionFree(sf::Vector2i positionToCheck, sf::Vector2i obstaclePosition) const
{
	return (!(positionToCheck.x + 40 > obstaclePosition.x &&
		obstaclePosition.x + 40 > positionToCheck.x &&
		positionToCheck.y + 40 > obstaclePosition.y &&
		obstaclePosition.y + 40 > positionToCheck.y));
}

