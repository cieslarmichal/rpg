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

void Create::createWall(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & obstacles)
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


void Create::createRoomWithFloor(int roomSizeX, int roomSizeY, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown,
	std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	for (int vertical = 0; vertical <= roomSizeY; vertical++)
	{
		for (int horizontal = 0; horizontal <= roomSizeX; horizontal++)
		{
			if ((!((horizontal == doorLocDown) && vertical == roomSizeY)) && (!((horizontal == doorLocTop) && vertical == 0)) &&
				(!((vertical == doorLocRight) && horizontal == roomSizeX)) && (!((vertical == doorLocLeft) && horizontal == 0)) &&
				(horizontal == 0 || horizontal == roomSizeX || vertical == 0 || vertical == roomSizeY))
			{
				createWall({ (float)(40 * horizontal + position.x * 40),(float)(40 * vertical + position.y * 40) }, walls);
			}
			else
			{
				createFloor({ (float)(40 * horizontal + position.x * 40),(float)(40 * vertical + position.y * 40) }, floor);
			}
		}
	}
}

void Create::createRoomWithoutFloor(int roomSizeX, int roomSizeY, sf::Vector2f position, int doorLocRight, int doorLocLeft, int doorLocTop, int doorLocDown, std::vector<std::unique_ptr<Wrapper>>& walls)
{
	for (int vertical = 0; vertical <= roomSizeY; vertical++)
	{
		for (int horizontal = 0; horizontal <= roomSizeX; horizontal++)
		{
			if ((!((horizontal == doorLocDown) && vertical == roomSizeY)) && (!((horizontal == doorLocTop) && vertical == 0)) &&
				(!((vertical == doorLocRight) && horizontal == roomSizeX)) && (!((vertical == doorLocLeft) && horizontal == 0)) &&
				(horizontal == 0 || horizontal == roomSizeX || vertical == 0 || vertical == roomSizeY))
			{
				createWall({ (float)(40 * horizontal + position.x * 40),(float)(40 * vertical + position.y * 40) }, walls);
			}
		}
	}
}

void Create::createWorldFromTxt(std::string pathFile, std::vector<std::unique_ptr<Wrapper>> & walls, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	std::vector<std::string > lines(File::getLines("stuff/map.txt"));

	int y = -1;
	for (auto line : lines)
	{
		if (y == -1)
		{
			y++;
			continue;
		}

		for (int x = 0; x < (int)line.size(); x++)
		{
			if (line[x] == '#')
			{
				createWall({ (float)(x * 40),(float)(y * 40) }, walls);
			}
			else if (line[x] == '-')
			{
				createFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
		}
		y++;
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

void Create::createHUDSlots(std::vector<std::unique_ptr<Rect>>& HUDInventorySlots)
{
	//helmet armor etc ...

	for (int i = 0; i < 15; i++)
	{
		HUDInventorySlots.push_back(std::unique_ptr<Rect>(new Rect(16, 16, { -1,-1 })));
	}
}
