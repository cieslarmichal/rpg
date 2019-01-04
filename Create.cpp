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
		std::unique_ptr<Sprite>(new Sprite("stuff/skeleton.png", 48, 48)), 2)), enemyStatusBar));
}

void Create::createDragon(Dragon & dragon, enemyPair & enemies, sf::Vector2f position)
{
	StatusBar enemyStatusBar;
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(dragon, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/dragon.png", 96, 96)), 3)), enemyStatusBar));
}

void Create::createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles, sf::Vector2i dimSprite)
{
	projectiles.push_back(std::unique_ptr<Wrapper>(new Wrapper
	(std::unique_ptr<Rect>(new Rect(projectile, 20, 20, { player->rect->getPosition().x + 7,player->rect->getPosition().y + 15 })),
		std::unique_ptr<Sprite>(new Sprite("stuff/projectile.png", 64, 64, dimSprite.x, dimSprite.y)))));
}

void Create::createItem(Item & item, std::vector<std::unique_ptr<Wrapper>> & items, sf::Vector2f position)
{
	items.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(item, 16, 16, position)),
		std::unique_ptr<Sprite>(new Sprite(item.getPathName(), 16, 16)))));
}

void Create::createSingleWall(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	Obstacle obstacle;
	obstacles.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/wall.png", 40, 40)))));
}

void Create::createFloor(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	Obstacle obstacle;
	floor.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("stuff/floor.png", 40, 40)))));
}

void Create::createWall(sf::Vector2f startPosition, sf::Vector2f endPosition, std::vector<std::unique_ptr<Wrapper>> & walls)
{
	if (startPosition.x != endPosition.x && startPosition.y != endPosition.y) return;

	if (startPosition.x > endPosition.x && startPosition.y)
	{
		for (int wallIndex = (int)endPosition.x; wallIndex <= (int)startPosition.x; wallIndex++)
		{
			createSingleWall({ (float)(wallIndex * 40),(float)(endPosition.y * 40) }, walls);
		}
	}
	else if (startPosition.x < endPosition.x)
	{
		for (int wallIndex = (int)startPosition.x; wallIndex <= (int)endPosition.x; wallIndex++)
		{
			createSingleWall({ (float)(wallIndex * 40),(float)(endPosition.y * 40) }, walls);
		}
	}
	else if (startPosition.y > endPosition.y)
	{
		for (int wallIndex = (int)endPosition.y; wallIndex <= (int)startPosition.y; wallIndex++)
		{
			createSingleWall({ (float)(startPosition.x * 40),(float)(wallIndex * 40) }, walls);
		}
	}
	else if (startPosition.y < endPosition.y)
	{
		for (int wallIndex = (int)startPosition.y; wallIndex <= (int)endPosition.y; wallIndex++)
		{
			createSingleWall({ (float)(startPosition.x * 40),(float)(wallIndex * 40) }, walls);
		}
	}
}

void Create::createRoom(int roomSize, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown,
	std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	for (int vertical = 0; vertical <= roomSize; vertical++)
	{
		for (int horizontal = 0; horizontal <= roomSize; horizontal++)
		{
			if ((!((horizontal == doorLocDown) && vertical == roomSize)) && (!((horizontal == doorLocTop) && vertical == 0)) &&
				(!((vertical == doorLocRight) && horizontal == roomSize)) && (!((vertical == doorLocLeft) && horizontal == 0)) &&
				(horizontal == 0 || horizontal == roomSize || vertical == 0 || vertical == roomSize))
			{
				createSingleWall({ (float)(40 * horizontal + position.x * 40),(float)(40 * vertical + position.y * 40) }, walls);
			}
			else
			{
				createFloor({ (float)(40 * horizontal + position.x * 40),(float)(40 * vertical + position.y * 40) }, floor);
			}
		}

	}
}

void Create::createMaze(std::string * mazeArray, int rows, sf::Vector2f startPosition, std::vector<std::unique_ptr<Wrapper>> & walls)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; (size_t)x < mazeArray[y].size(); x++)
		{
			if (mazeArray[y][x] == '#')
			{
				createSingleWall({ (float)(startPosition.x * 40 + x * 40),(float)(startPosition.y * 40 + y * 40) }, walls);
			}
		}
	}
}

void Create::createDamageMessage(int message, sf::Vector2f position, std::vector<std::unique_ptr<Text>> & notifications)
{
	std::string msg = std::to_string(message);
	notifications.push_back(std::unique_ptr<Text>(new Text(msg, { position.x + 15,position.y - 2 }, sf::Color::Red, true, 18)));
}

void Create::createLevelMessage(std::string message, std::vector<std::unique_ptr<Text>> & notifications)
{
	if (message == "") return;
	notifications.push_back(std::unique_ptr<Text>(new Text(message, sf::Vector2f(400, 400), sf::Color::White, false, 22)));
}

void Create::createHUDMessage(std::vector<std::unique_ptr<Text>> & HUDinfo)
{
	HUDinfo.push_back(std::unique_ptr<Text>(new Text(sf::Color::Red, "HP", 20)));
	HUDinfo.push_back(std::unique_ptr<Text>(new Text(sf::Color::Yellow, "COINS", 20)));
	HUDinfo.push_back(std::unique_ptr<Text>(new Text(sf::Color::Magenta, "EXP", 20)));
}
