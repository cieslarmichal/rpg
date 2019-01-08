#include "Game.h"



Game::Game()
{
	//equipped w Item i dalej trzeba oznaczac w Player.cpp jesli Q to oznacza equipped i cos dalej
	//przy wchodzeniu w tunel wiesza gre
	//konczyc to bo trzeba tmp robic tez
}

Game::~Game()
{
	delete window;
	delete playerView;
	delete draw;
	delete characterPlayer;
	delete characterSkeleton;
	delete characterDragon;
}

bool Game::run()
{
	initialize();
	createCharacters();
	createWorld();
	gameLoop();

	return true;
}

void Game::gameLoop()
{
	while (window->isOpen())
	{
		clearWindow();

		int *inputKeys = input.read();

		Mark::markTarget(inputKeys[Input::ACTION], player, enemies, *window);
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
		Update::updateHUD(player, HUDInfo, HUDInventory,HUDInventorySlots, window->getSize());
		Update::updateObstacles(walls);
		Update::updateObstacles(floor);
		Update::updateItems(items);
		Update::updateProjectiles(projectiles, enemies);

		updatePlayerView();

		if (timer.getElapsedSeconds() >= 0.5)
		{
			timer.reset();
			updatePathFindingMap();
		}

		Delete::removeText(notifications);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);
		Delete::removeItems(items);
		Delete::removeAndAddItems(player->rect->player->getInventory().getItems(), items, player->rect->getPosition());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			player->rect->character->getPathFinding().debugDrawMap(*window);
		}

		drawWindow();
	}
}

void Game::initialize()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 800), "RPG game");
	window->setPosition(sf::Vector2i(10, 50));
	window->setFramerateLimit(60);

	playerView = new sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
	playerView->setSize(sf::Vector2f(sf::Vector2u(window->getSize())));
	playerView->setCenter(sf::Vector2f(playerView->getSize().x / 2, playerView->getSize().y / 2));
	window->setView(*playerView);

	draw = new Draw(*window);
}

void Game::createCharacters()
{
	// Player:
	// name, hp, attackDamage, attackSpeed, movementSpeed
	characterPlayer = new Player("Michal", 100, 100, 3, 4);
	// Enemies:
	// name, hp, attackDamage, attackSpeed, movementSpeed, experience, coins, lootChance
	characterSkeleton = new Skeleton("Skeleton", 200, 5, 3, 2, 70, 10, 0.2);
	characterDragon = new Dragon("Dragon", 1000, 25, 2, 2, 400, 30, 0.05);

	player = Create::createPlayer(*characterPlayer, { 24 * 40,30 * 40 });
	Create::createSkeleton(*characterSkeleton, enemies, { 18 * 40,20 * 40 });
	Create::createSkeleton(*characterSkeleton, enemies, { 19 * 40,14 * 40 });
	Create::createSkeleton(*characterSkeleton, enemies, { 5 * 40,6 * 40 });
	Create::createSkeleton(*characterSkeleton, enemies, { 8 * 40,11 * 40 });
	Create::createSkeleton(*characterSkeleton, enemies, { 2 * 40,2 * 40 });
	Create::createDragon(*characterDragon, enemies, { 20 * 40,18 * 40 });

	Create::createHUDMessage(HUDInfo);
	Create::createHUDSlots(HUDInventorySlots);
}

void Game::createWorld()
{
	Create::createRoomWithoutFloor(50, 40, { 0, 0 }, 3, -10, 2, -10, walls);

	try
	{
		Create::createWorldFromTxt("stuff/map.txt", walls, floor);
	}
	catch (const char * err)
	{
		std::cerr << err << std::endl;
	}

	initializePathFindingMap();
}

void Game::initializePathFindingMap()
{
	Map::readTiles(walls);
	pathfinding.initializeLogicMap(Map::tiles);
}

void Game::updatePathFindingMap()
{
	Map::updateTiles(enemies);
	pathfinding.updateLogicMap(Map::tiles);
}

void Game::updatePlayerView()
{
	playerView->setCenter(player->rect->getPosition());
	window->setView(*playerView);
}

void Game::drawWindow()
{
	draw->drawObstacles(floor);
	draw->drawObstacles(walls);
	draw->drawItems(items);
	draw->drawProjectiles(projectiles);
	draw->drawEnemies(enemies);
	draw->drawPlayer(player);
	draw->drawStatusBar(playerHealthBar);
	draw->drawText(notifications);
	draw->drawText(HUDInfo);
	draw->drawHUDSlots(HUDInventorySlots);
	draw->drawHUDItems(HUDInventory);
	window->display();
}

void Game::clearWindow()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window->close();
		}
	}
	window->clear();
}
