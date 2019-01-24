#pragma once
#include "Enemy.h"
#include "Create.h"
#include "Random.h"
#include "Tile.h"
#include "Constants.h"

using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, std::unique_ptr<StatusBar>>>;

class EnemySpawner
{
public:
	EnemySpawner();
	void spawnSkeleton(vectorOfCharacters & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnSkeletonBerserker(vectorOfCharacters & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnDragon(vectorOfCharacters & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	void spawnRandomEnemy(vectorOfCharacters & enemies, sf::Vector2f respawnPosition = { RANDOM,RANDOM });
	static void setAmountOfEnemies(int);
	static int getAmountOfEnemies();
public:
	void readEnemiesFromTxt(vectorOfCharacters & enemies);
	void initializeObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
	void updateObjectsPositions(std::vector<std::unique_ptr<Tile>> & mapPositions);
private:
	std::unique_ptr<Skeleton> characterSkeleton;
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

