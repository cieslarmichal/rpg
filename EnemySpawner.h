#pragma once
#include "Tile.h"
#include "Skeleton.h"
#include "SkeletonBerserker.h"
#include "Dragon.h"
#include "Random.h"
#include "Create.h"
#include "Directions.h"

typedef std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();
	void spawnSkeleton(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnSkeletonBerserker(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnDragon(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnRandomEnemy(enemyPair & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
public:
	void initializeObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
	void updateObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
private:
	Skeleton * characterSkeleton;
	SkeletonBerserker * characterSkeletonBerserker;
	Dragon * characterDragon;
	enum EnemyType { SKELETON = 0, SKELETON_BERSERKER = 1, DRAGON = 2 };
	int getRandomEnemyType() const;
private:
	std::vector<std::unique_ptr<Tile>> obstacles;
	enum Position { RANDOM = -1 };
	sf::Vector2f getRandomPosition() const;
	bool isPossibleToAddPosition(sf::Vector2i position) const;
	bool isPositionFree(sf::Vector2i positionToCheck, sf::Vector2i obstaclePosition) const;
};

