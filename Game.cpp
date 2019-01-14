#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
	delete window;
	delete playerView;
	delete draw;
	delete characterPlayer;
	delete characterNpc;
}

bool Game::run()
{
	initialize();
	createWorld();
	createCharacters();
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
		collisionHandler.playerWithNpcs(player, npcs, notifications, inputKeys[Input::ACTION]);
		collisionHandler.playerWithEnemies(player, enemies, notifications, items);
		collisionHandler.playerWithItems(player, items, inputKeys[Input::ACTION]);
		collisionHandler.enemiesWithObstacles(enemies, walls);
		collisionHandler.enemiesWithNpcs(enemies, npcs);
		collisionHandler.enemiesWithEnemies(enemies);
		collisionHandler.projectilesWithWalls(projectiles, walls);
		collisionHandler.projectilesWithEnemies(player, projectiles, enemies, notifications, items);

		Update::updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION], inputKeys[Input::ACTION], notifications);
		Update::updateEnemies(enemies, player);
		Update::updateNpc(npcs);
		Update::updateText(player, notifications);
		Update::updateHUD(player, hud, window->getSize());
		Update::updateObstacles(walls);
		Update::updateObstacles(floor);
		Update::updateItems(items);
		Update::updateProjectiles(projectiles, enemies);

		updatePlayerView();

		if (timer.getElapsedSeconds() >= 0.5)
		{
			timer.reset();
			updateLogicMap();
		}

		Delete::removeText(notifications);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);
		Delete::removeItems(items);
		Delete::removeAndAddItems(player->rect->player->getInventory().getItems(), items, player->rect->getPosition());

		drawWindow();
	}
}

void Game::initialize()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 800), "RPG game");
	window->setPosition(sf::Vector2i(10, 50));
	window->setFramerateLimit(60);

	playerView = new sf::View(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	playerView->setSize(sf::Vector2f((window->getSize())));
	playerView->setCenter(sf::Vector2f(playerView->getSize().x / 2, playerView->getSize().y / 2));
	window->setView(*playerView);

	draw = new Draw(*window);
}

void Game::createCharacters()
{
	// Player:
	// name, hp, attackDamage, attackSpeed, movementSpeed
	characterPlayer = new Player("Michal", 2500, 100, 3, 8);
	player = Create::createPlayer(*characterPlayer, { 24 * 40,30 * 40 });

	characterNpc = new Npc("Carl", "stuff/dialogues.txt");
	Create::createNpc(*characterNpc, npcs, { 20 * 40,30 * 40 });

	enemySpawner.spawnSkeleton(enemies);
	enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);
	//enemySpawner.spawnSkeleton(enemies);

	//enemySpawner.spawnSkeletonBerserker(enemies, { 40 * 40,5 * 40 });
	//enemySpawner.spawnDragon(enemies);

}

void Game::createWorld()
{
	Create::createRoomWithoutFloor(MAP_WIDTH, MAP_HEIGHT, { 0, 0 }, -10, -10, -10, -10, walls);

	try
	{
		Create::createWorldFromTxt("stuff/map.txt", walls, floor);
	}
	catch (const char * err)
	{
		std::cerr << err << std::endl;
	}

	initializeLogicMap();

	Missions::readMissions();
}

void Game::initializeLogicMap()
{
	Map::readTiles(walls);
	pathfinding.initializeLogicMap(Map::tiles);
	enemySpawner.initializeObjectsPositions(Map::precisePositions);
}

void Game::updateLogicMap()
{
	Map::updateTiles(player, enemies,npcs);
	pathfinding.updateLogicMap(Map::tiles);
	enemySpawner.updateObjectsPositions(Map::precisePositions);
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
	draw->drawNpcs(npcs);
	draw->drawItems(items);
	draw->drawProjectiles(projectiles);
	draw->drawEnemies(enemies);
	draw->drawPlayer(player);
	draw->drawStatusBar(playerHealthBar);
	draw->drawText(notifications);
	draw->drawHUD(hud);

	//player->rect->character->getPathFinding().debugDrawMap(*window);

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
