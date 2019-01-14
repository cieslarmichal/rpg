#pragma once
#include "Enemy.h"
#include "Create.h"
#include "Random.h"
#include "Tile.h"
#include "Constants.h"

typedef std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class EnemySpawner
{
public:
	EnemySpawner();
	void spawnSkeleton(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnSkeletonBerserker(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnDragon(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnRandomEnemy(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
public:
	void initializeObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
	void updateObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
private:
	std::unique_ptr<Skeleton>  characterSkeleton;
	std::unique_ptr<SkeletonBerserker> characterSkeletonBerserker;
	std::unique_ptr<Dragon> characterDragon;
	int getRandomEnemyType() const;
	static int amountOfEnemies;
private:
	std::vector<std::unique_ptr<Tile>> obstacles;
	enum Position { RANDOM = -1 };
	sf::Vector2f getRandomPosition() const;
	bool isPossibleToAddPosition(sf::Vector2i position) const;
	bool isPositionFree(sf::Vector2i positionToCheck, sf::Vector2i obstaclePosition) const;

};

