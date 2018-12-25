#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Skeleton.h"
#include "Projectile.h"
#include "Notifications.h"

typedef std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;

class Create
{
public:
	Create() = delete;
	static std::unique_ptr<Wrapper> createPlayer(Player & player, sf::Vector2f position);
	static void createSkeleton(Skeleton & skeleton, enemyPair & enemies, sf::Vector2f position);
	static void createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles,sf::Vector2i dimSprite);
	static void createObstacle(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	static void createRoom(int roomSize, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown,std::vector<std::unique_ptr<Wrapper>> & obstacles);
	static void createBattleNotification(std::string message, sf::Vector2f position);
	static void createBattleNotification(int message, sf::Vector2f position);
};
