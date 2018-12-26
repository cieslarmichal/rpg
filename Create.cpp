#include "Create.h"

std::unique_ptr<Wrapper> Create::createPlayer(Player & player, sf::Vector2f position)
{
	return std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(player, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/player.png", 64, 64)), 9));
}

void Create::createSkeleton(Skeleton & skeleton, enemyPair & enemies, sf::Vector2f position)
{
	StatusBar enemyStatusBar;
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(skeleton, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/skeleton.png", 48, 48)), 3)), enemyStatusBar));
}

void Create::createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles, sf::Vector2i dimSprite)
{
	projectiles.push_back(std::unique_ptr<Wrapper>(new Wrapper
	(std::unique_ptr<Rect>(new Rect(projectile, 20, 20, { player->rect->getPosition().x + 7,player->rect->getPosition().y + 15 })),
		std::unique_ptr<Sprite>(new Sprite("stuff/projectile.png", 64, 64, dimSprite.x, dimSprite.y)))));
}

void Create::createObstacle(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	Obstacle obstacle;
	obstacles.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/wall.png", 40,40)))));
}

void Create::createFloor(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	Obstacle obstacle;
	floor.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/floor.png", 40, 40)))));
}

void Create::createRoom(int roomSize, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown,
	std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	for (int vertical = 0; vertical <= roomSize; vertical++)
	{
		for (int horizontal = 0; horizontal <= roomSize; horizontal++)
		{
			if ((!(horizontal == doorLocDown&& vertical==roomSize)) && (!(horizontal == doorLocTop && vertical==0)) &&
				(!(vertical == doorLocRight && horizontal == roomSize)) && (!(vertical == doorLocLeft && horizontal == 0)) &&
				(horizontal == 0 || horizontal == roomSize || vertical==0 ||vertical==roomSize))
			{
				createObstacle({ (float)(40 * horizontal + position.x),(float)(40 * vertical + position.y) }, walls);
			}
			createFloor({ (float)(40 * horizontal + position.x),(float)(40 * vertical + position.y) }, floor);
		}

	}
}

void Create::createBattleNotification(int message, sf::Vector2f position, std::vector<std::unique_ptr<Text>> & notifications)
{
	std::string msg = std::to_string(message);
	notifications.push_back(std::unique_ptr<Text>(new Text(msg, { position.x + 12,position.y - 2 }, sf::Color::Red)));
}

