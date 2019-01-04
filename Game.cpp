#include "Game.h"



Game::Game()
{
	//pokazywanie itemow z inventory w pod HUDem
	//konczyc to bo trzeba tmp robic tez
}

bool Game::run()
{
	sf::RenderWindow window(sf::VideoMode(1280, 800), "RPG game");
	window.setPosition(sf::Vector2i(10, 50));
	window.setFramerateLimit(60);

	sf::View playerView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	playerView.setSize(sf::Vector2f(sf::Vector2u(window.getSize())));
	playerView.setCenter(sf::Vector2f(playerView.getSize().x / 2, playerView.getSize().y / 2));
	window.setView(playerView);

	Input input;
	Draw draw(window);
	CollisionHandler collisionHandler;
	PathFinding path;

	StatusBar playerHealthBar;
	Player characterPlayer("Michal", 100, 200, 3, 4);
	std::unique_ptr<Wrapper> player = Create::createPlayer(characterPlayer, { 24 * 40,30 * 40 });

	std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemies;
	Skeleton characterSkeleton("Skeleton", 100, 5, 3, 70, 0, 2, 0);
	Dragon characterDragon("Dragon", 1000, 30, 2, 40, 4, 2, 0);

	Create::createSkeleton(characterSkeleton, enemies, { 18 * 40,20 * 40 });
	Create::createSkeleton(characterSkeleton, enemies, { 19 * 40,14 * 40 });
	Create::createSkeleton(characterSkeleton, enemies, { 5 * 40,6 * 40 });
	Create::createSkeleton(characterSkeleton, enemies, { 8 * 40,11 * 40 });
	Create::createSkeleton(characterSkeleton, enemies, { 2 * 40,2 * 40 });
	Create::createDragon(characterDragon, enemies, { 20 * 40,18 * 40 });

	std::vector<std::unique_ptr<Wrapper>> projectiles;

	std::vector<std::unique_ptr<Text>> notifications;
	std::vector<std::unique_ptr<Text>> HUDinfo;
	Create::createHUDMessage(HUDinfo);

	std::vector<std::unique_ptr<Wrapper>> walls;
	std::vector<std::unique_ptr<Wrapper>> floor;

	std::vector<std::unique_ptr<Wrapper>> items;

	Create::createRoom(40, { 0, 0 }, 3, -10, 2, -10, walls, floor);

	std::string maze1[14] =
	{
		"##############",
		"#---##########",
		"#-#-##########",
		"#-#---###----#",
		"#-###-----##-#",
		"--#---###-#--#",
		"--#-###---#-##",
		"#----##-###--#",
		"####--#--###-#",
		"#####-##-#---#",
		"###----###-###",
		"###-##-#---###",
		"########-#####",
		"###----------#"
	};
	Create::createMaze(maze1, 14, { 26,26 }, walls);

	std::string maze2[20] =
	{
		"##################",
		"--#---#---#-----#",
		"#-###-#-#-#####-#",
		"#---#---#-----#-#",
		"###-###-#-###-#-#",
		"#-#-#---#-#-#---#",
		"#-#-#####-#-#####",
		"#-#-----#-----#-#",
		"#-###-#-###-#-#-#",
		"#---#-#-#---#-#-#",
		"#-#-#-#-#-###-#-#",
		"#-#-#-#-#-#---#-#",
		"###-###-#-#-###-#",
		"#---------#-#---#",
		"#-#####-###-#-###",
		"#-----#---#-----#",
		"###############-#",
	};
	Create::createMaze(maze2, 20, { 21,0 }, walls);

	Map map;
	map.readTiles(walls);
	path.initializeLogicMap(map.tiles);

	sf::Clock clock;

	while (window.isOpen())
	{
		clearWindow(window);
		sf::Time elapsed = clock.getElapsedTime();

		int *inputKeys = input.read();

		Mark::markTarget(inputKeys[Input::ACTION], player, enemies, window);
		Shoot::shootEnemy(player, enemies, projectiles);

		collisionHandler.characterWithObstacles(player, walls);
		collisionHandler.enemiesWithObstacles(enemies, walls);
		collisionHandler.enemiesWithEnemies(enemies);
		collisionHandler.playerWithEnemies(player, enemies, notifications, items);
		collisionHandler.playerWithItems(player, items, inputKeys[Input::ACTION]);
		collisionHandler.projectilesWithWalls(projectiles, walls);
		collisionHandler.projectilesWithEnemies(player, projectiles, enemies, notifications, items);

		Update::updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION], inputKeys[Input::ACTION], notifications);
		Update::updateEnemies(enemies, player);
		Update::updateText(player, notifications);
		Update::updateHUDInfo(player, HUDinfo, window.getSize());
		Update::updateObstacles(walls);
		Update::updateObstacles(floor);
		Update::updateItems(items);
		Update::updateProjectiles(projectiles, enemies);

		Delete::removeText(notifications);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);
		Delete::removeItems(items);

		playerView.setCenter(player->rect->getRect().getPosition());
		window.setView(playerView);

		draw.drawObstacles(floor);
		draw.drawObstacles(walls);
		draw.drawItems(items);
		draw.drawProjectiles(projectiles);
		draw.drawEnemies(enemies);
		draw.drawPlayer(player);
		draw.drawStatusBar(playerHealthBar);
		draw.drawText(notifications);
		draw.drawText(HUDinfo);

		if (elapsed.asSeconds() >= 0.5)
		{
			clock.restart();
			map.updateTiles(enemies);
			path.updateLogicMap(map.tiles);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			std::cout << enemies[1].first->rect->character->getNextMove().x << ", " << enemies[1].first->rect->character->getNextMove().y << std::endl;
			enemies[1].first->rect->character->getPathFinding().debugDrawMap(window);

		}
		window.display();
	}
	return true;
}


void Game::clearWindow(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
	}
	window.clear();
}
