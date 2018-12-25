#include "Create.h"

std::unique_ptr<Wrapper> Create::createPlayer(Player & player, sf::Vector2f position)
{
	return std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(player, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/player.png", 64, 64)), 9));
}

void Create::createSkeleton(Skeleton & skeleton, enemyPair & enemies, sf::Vector2f position)
{
	StatusBar enemyStatusBar;
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(skeleton, 48, 48, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/skeleton.png", 48, 48)), 3)), enemyStatusBar));
}

void Create::createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles, sf::Vector2i dimSprite)
{
	projectiles.push_back(std::unique_ptr<Wrapper>(new Wrapper
	(std::unique_ptr<Rect>(new Rect(projectile, 20, 20, { player->rect->getPosition().x + 7,player->rect->getPosition().y + 15 })),
		std::unique_ptr<Sprite>(new Sprite("stuff/projectile.png", 64, 64,dimSprite.x,dimSprite.y)))));
}

void Create::createObstacle(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	Obstacle obstacle;
	obstacles.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 32, 32, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/walls.png", 32, 32, 32, 0)))));
}

void Create::createRoom(int roomSize, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int wallHorizontalIndex = 0;
	while (wallHorizontalIndex < roomSize)
	{
		if (wallHorizontalIndex != doorLocTop && wallHorizontalIndex != doorLocTop + 1)
		{
			createObstacle({ (float)(32 * wallHorizontalIndex + position.x),(float)position.y }, obstacles);
		}
		wallHorizontalIndex++;
	}


	wallHorizontalIndex = 0;
	while (wallHorizontalIndex < roomSize)
	{
		if (wallHorizontalIndex != doorLocDown && wallHorizontalIndex != doorLocDown + 1)
		{
			createObstacle({ (float)(32 * wallHorizontalIndex + position.x),(float)(32 * roomSize + position.y) }, obstacles);
		}
		wallHorizontalIndex++;
	}

	//create vertical wall
	int wallVerticalIndex = 0;
	while (wallVerticalIndex < roomSize)
	{
		if (wallVerticalIndex != doorLocLeft && wallVerticalIndex != doorLocLeft + 1)
		{
			createObstacle({ (float)position.x,(float)(32 * wallVerticalIndex + position.y) }, obstacles);
		}
		wallVerticalIndex++;
	}

	//create vertical wall
	wallVerticalIndex = 0;
	while (wallVerticalIndex < roomSize +1 )
	{
		if (wallVerticalIndex != doorLocRight && wallVerticalIndex != doorLocRight + 1)
		{
			createObstacle({ (float)(position.x + 32 * roomSize),(float)(32 * wallVerticalIndex + position.y) }, obstacles);
		}
		wallVerticalIndex++;
	}
}

void Create::createBattleNotification(std::string message, sf::Vector2f position)
{
	notifications.push_back(std::unique_ptr<Text>(new Text(message, { position.x + 12,position.y-2 }, sf::Color::Red)));
}

void Create::createBattleNotification(int message, sf::Vector2f position)
{
	std::string msg = std::to_string(message);
	notifications.push_back(std::unique_ptr<Text>(new Text(msg, { position.x + 12,position.y-2 }, sf::Color::Red)));
}

