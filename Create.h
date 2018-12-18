#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Skeleton.h"
#include "Projectile.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Create
{
public:
	Create();
	std::unique_ptr<Wrapper> createPlayer(Player & player, sf::Vector2f position);
	void createSkeleton(Skeleton & skeleton, enemyPair & enemies, sf::Vector2f position);
	void createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles,sf::Vector2i dimSprite);
	void createObstacle(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void createRoom(int roomSize, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown,std::vector<std::unique_ptr<Wrapper>> & obstacles);
};

