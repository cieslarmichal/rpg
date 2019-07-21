#include "Create.h"

std::unique_ptr<Wrapper> Create::createPlayer(Player & player, sf::Vector2f position)
{
	return std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(player, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/player.png", 64, 64)), 9));
}

void Create::createNpc(Npc & npc, vectorOfCharacters & npcs, sf::Vector2f position)
{
	npcs.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(npc, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/npc.png", 30, 51)))), std::unique_ptr<StatusBar>(new StatusBar())));
}

void Create::createSkeleton(Skeleton & skeleton, vectorOfCharacters & enemies, sf::Vector2f position)
{
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(skeleton, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/skeleton.png", 48, 48)), 2)), std::unique_ptr<StatusBar>(new StatusBar())));
}

void Create::createSkeletonBerserker(SkeletonBerserker & skeletonBerserker, vectorOfCharacters & enemies, sf::Vector2f position)
{
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(skeletonBerserker, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/skeletonBerserker.png", 48, 48)), 2)), std::unique_ptr<StatusBar>(new StatusBar())));
}

void Create::createDragon(Dragon & dragon, vectorOfCharacters & enemies, sf::Vector2f position)
{
	enemies.push_back(std::make_pair(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(dragon, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/dragon.png", 96, 96)), 3)), std::unique_ptr<StatusBar>(new StatusBar())));
}

void Create::createProjectile(std::unique_ptr<Wrapper>& player, Projectile & projectile, std::vector<std::unique_ptr<Wrapper>> & projectiles, sf::Vector2i dimSprite)
{
	projectiles.push_back(std::unique_ptr<Wrapper>(new Wrapper
	(std::unique_ptr<Rect>(new Rect(projectile, 20, 20, { player->rect->getPosition().x + 7,player->rect->getPosition().y + 15 })),
		std::unique_ptr<Sprite>(new Sprite("../stuff/projectile.png", 64, 64, dimSprite.x, dimSprite.y)))));
}

void Create::createItem(Item & item, std::vector<std::unique_ptr<Wrapper>> & items, sf::Vector2f position)
{
	if (item.getId() == (int)Item::Id::COIN)
	{
		sf::Vector2f offset{ 0,0 };

		int amountOFCoins = Random::getRandomNumber(1, 5);

		if (amountOFCoins == 3 || amountOFCoins == 4 || amountOFCoins == 5)
		{
			amountOFCoins = Random::getRandomNumber(1, 5);
		}

		int coinCounter = 1;
		while (coinCounter <= amountOFCoins)
		{
			switch (coinCounter)
			{
			case 1:
				offset = { 4,18 };
				break;
			case 2:
				offset = { -8,18 };
				break;
			case 3:
				offset = { -2,10 };
				break;
			case 4:
				offset = { -6,14 };
				break;
			case 5:
				offset = { 2,14 };
				break;
			}

			items.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(item, 16, 16, position + offset)),
				std::unique_ptr<Sprite>(new Sprite(item.getPathName(), 16, 16)))));

			coinCounter++;
		}
	}
	else
	{
		items.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(item, 16, 16, position)),
			std::unique_ptr<Sprite>(new Sprite(item.getPathName(), 16, 16)))));
	}
}

void Create::createStoneWall(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & walls)
{
	Obstacle obstacle;
	walls.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/wall.png", 40, 40)))));
}

void Create::createStone(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>>& walls)
{
	Obstacle obstacle;
	walls.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/stone.png", 40, 40)))));
}

void Create::createTree(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>>& trees)
{
	Obstacle obstacle(true);
	trees.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/tree.png", 68, 108)))));
}

void Create::createGrassFloor(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>> & floor)
{
	Obstacle obstacle;
	floor.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/grass.bmp", 40, 40)))));
}

void Create::createWoodenFloor(sf::Vector2f position, std::vector<std::unique_ptr<Wrapper>>& floor)
{
	Obstacle obstacle;
	floor.push_back(std::unique_ptr<Wrapper>(new Wrapper(std::unique_ptr<Rect>(new Rect(obstacle, 40, 40, position)),
		std::unique_ptr<Sprite>(new Sprite("../stuff/wood.png", 40, 40)))));
}

void Create::createMapFrame(int sizeX, int sizeY, std::vector<std::unique_ptr<Wrapper>>& trees)
{
	for (int vertical = 0; vertical <= sizeY; vertical++)
	{
		for (int horizontal = 0; horizontal <= sizeX; horizontal++)
		{
			if (horizontal == 0 || horizontal == sizeX || vertical == 0 || vertical == sizeY)
			{
				createTree({ (float)(40 * horizontal),(float)(40 * vertical) }, trees);
			}
		}
	}
}

void Create::createWorldFromTxt(std::string pathFile, std::vector<std::unique_ptr<Wrapper>> & walls,
	std::vector<std::unique_ptr<Wrapper>> & floor, std::vector<std::unique_ptr<Wrapper>> & trees)
{
	std::vector<std::string> lines(File::getLines("../stuff/map.txt"));

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
				createStoneWall({ (float)(x * 40),(float)(y * 40) }, walls);
			}
			else if (line[x] == '|')
			{
				createTree({ (float)(x * 40), (float)(y * 40) }, trees);

				createGrassFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
			else if (line[x] == '_')
			{
				createWoodenFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
			else if (line[x] == '*')
			{
				createStone({ (float)(x * 40),(float)(y * 40) }, walls);

				createGrassFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
			else
			{
				createGrassFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
		}
		y++;
	}

	for (int y = -8; y <= MAP_HEIGHT + 8; y++)
	{
		for (int x = -13; x <= MAP_WIDTH + 13; x++)
		{
			if (x<0 || y<0 || x>MAP_WIDTH || y>MAP_HEIGHT)
			{
				createGrassFloor({ (float)(x * 40),(float)(y * 40) }, floor);
			}
		}
	}
}

void Create::createNpcMessage(std::string message, sf::Vector2f position, std::vector<std::unique_ptr<Text>>& notifications, bool longMsgLifetime)
{
	int messageSize = (int)message.size();

	sf::Vector2f offset{ 0,0 };

	if (messageSize <= 7)
	{
		offset = { 10,-30 };
	}
	else if (messageSize > 7 && messageSize <= 15)
	{
		offset = { -20,-30 };
	}
	else if (messageSize > 15 && messageSize <= 21)
	{
		offset = { -30,-30 };
	}
	else if (messageSize > 21 && messageSize <= 26)
	{
		offset = { -50,-30 };
	}
	else
	{
		offset = { -80,-30 };
	}

	notifications.push_back(std::unique_ptr<Text>(new Text(message, { position.x + offset.x,position.y + offset.y }, sf::Color::White, false, 15, true, !longMsgLifetime)));
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

