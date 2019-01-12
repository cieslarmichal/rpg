#pragma once
#include "Tile.h"
#include "Skeleton.h"
#include "SkeletonBerserker.h"
#include "Dragon.h"
#include "Random.h"
#include "Create.h"

typedef std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();
public:
	void spawnSkeleton(enemyPair & enemies, sf::Vector2f respawnPosition = { -1,-1 });
	void spawnSkeletonBerserker(enemyPair & enemies, sf::Vector2f respawnPosition = { -1,-1 });
	void spawnDragon(enemyPair & enemies, sf::Vector2f respawnPosition = { -1,-1 });
	void spawnRandomEnemy(enemyPair & enemies, sf::Vector2f respawnPosition = { -1,-1 });
public:
	void initializeObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
	void updateObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
private:
	Skeleton * characterSkeleton;
	SkeletonBerserker * characterSkeletonBerserker;
	Dragon * characterDragon;
	enum EnemyType { SKELETON = 0, SKELETON_BERSERKER = 1, DRAGON = 2 };
	std::vector<std::unique_ptr<Tile>> objectsPositions;
};

