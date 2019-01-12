#include "EnemySpawner.h"

EnemySpawner::EnemySpawner()
{
// name, hp, attackDamage, attackSpeed, movementSpeed, experience, coins, lootChance
	characterSkeleton = new Skeleton("Skeleton", 200, 5, 3, 2, 70, 10, 0.2f);
	characterSkeletonBerserker = new SkeletonBerserker("Berserker", 400, 40, 5, 4, 1000, 100, 0.13f);
	characterDragon = new Dragon("Dragon", 1000, 25, 2, 2, 400, 30, 0.05f);
}

EnemySpawner::~EnemySpawner()
{
	delete characterSkeleton;
	delete characterSkeletonBerserker;
	delete characterDragon;
}

void EnemySpawner::spawnSkeleton(enemyPair & enemies, sf::Vector2f respawnPosition)
{
	Create::createSkeleton(*characterSkeleton, enemies, respawnPosition);

}

void EnemySpawner::spawnSkeletonBerserker(enemyPair & enemies, sf::Vector2f respawnPosition)
{
	Create::createSkeletonBerserker(*characterSkeletonBerserker, enemies, respawnPosition);

}

void EnemySpawner::spawnDragon(enemyPair & enemies, sf::Vector2f respawnPosition)
{
	Create::createDragon(*characterDragon, enemies, respawnPosition);
}

void EnemySpawner::spawnRandomEnemy(enemyPair & enemies, sf::Vector2f respawnPosition)
{

}

void EnemySpawner::initializeObjectsPositions(std::vector<std::unique_ptr<Tile>>& mapPositions)
{
	for (auto & mp : mapPositions)
	{
		objectsPositions.push_back(std::unique_ptr<Tile>(new Tile(mp->getPosition(), true, false)));
	}
}

void EnemySpawner::updateObjectsPositions(std::vector<std::unique_ptr<Tile>>& mapPositions)
{
	objectsPositions.erase(std::remove_if(objectsPositions.begin(), objectsPositions.end(), [](std::unique_ptr<Tile> & mp) {return mp->isEnemy(); }), objectsPositions.end());

	for (auto & mp : mapPositions)
	{
		objectsPositions.push_back(std::unique_ptr<Tile>(new Tile(mp->getPosition(), true, true)));
	}
}
