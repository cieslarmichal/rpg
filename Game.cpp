#include "Game.h"


Game::Game(sf::RenderWindow & win)
{
	window = &win;
}

Game::~Game()
{
	Missions::clearMissions();
	HUD::clearHUDInfo();

	window = nullptr;
	delete playerView;
}

bool Game::run()
{
	initialize();
	createWorld();
	createCharacters();
	return gameLoop();
}

bool Game::gameLoop()
{
	while (window->isOpen())
	{
		clearWindow();
		if (closeWindow()) return (int)Mode::MENU;

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
		//trees
		collisionHandler.characterWithObstacles(player, trees);
		collisionHandler.enemiesWithObstacles(enemies, trees);
		collisionHandler.projectilesWithWalls(projectiles, trees);

		Update::updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION], inputKeys[Input::ACTION], notifications);
		Update::updateEnemies(enemies, player);
		Update::updateNpc(npcs);
		Update::updateText(player, notifications);
		Update::updateHUD(player, hud, window->getSize());
		Update::updateObstacles(walls);
		Update::updateObstacles(floor);
		Update::updateObstacles(trees);
		Update::updateItems(items);
		Update::updateProjectiles(projectiles, enemies);

		updatePlayerView();

		if (logicMapTimer.getElapsedSeconds() >= (float)0.5)
		{
			logicMapTimer.reset();
			updateLogicMap();
		}

		if (respawnTimer.getElapsedSeconds() >= (float)50)
		{
			respawnTimer.reset();
			enemySpawner.spawnRandomEnemy(enemies);
		}

		Delete::removeText(notifications);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);
		Delete::removeItems(items);
		Delete::removeAndAddItems(player->rect->player->getInventory().getItems(), items, player->rect->getPosition());

		drawWindow();

	}

	return true;
}

void Game::initialize()
{
	playerView = new sf::View(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	playerView->setSize(sf::Vector2f((window->getSize())));
	playerView->setCenter(sf::Vector2f(playerView->getSize().x / 2, playerView->getSize().y / 2));
	window->setView(*playerView);

	draw = std::make_unique<Draw>(Draw(*window));
}

void Game::createCharacters()
{
	// Player:
	// name, hp, attackDamage, attackSpeed, movementSpeed
	characterPlayer = std::make_unique<Player>(Player("Michal", 250, 1000, 3, 2));
	player = Create::createPlayer(*characterPlayer, { 5 * 40,20 * 40 });

	characterNpc = std::make_unique<Npc>(Npc("Carl", "stuff/dialogues.txt"));
	Create::createNpc(*characterNpc, npcs, { 7 * 40,34 * 40 });

	enemySpawner.readEnemiesFromTxt(enemies);
}

void Game::createWorld()
{
	Create::createMapFrame(MAP_WIDTH, MAP_HEIGHT, trees);

	try
	{
		Create::createWorldFromTxt("stuff/map.txt", walls, floor, trees);
	}
	catch (const char * err)
	{
		std::cerr << err << std::endl;
	}

	//apples
	Item apple(43);
	Create::createItem(apple, items, { 30 * 40, 6 * 40 });
	Create::createItem(apple, items, { 30 * 40, 7 * 40 + 3 });
	Create::createItem(apple, items, { 30 * 40 + 10, 10 * 40 + 10 });
	Create::createItem(apple, items, { 33 * 40, 7 * 40 + 8 });
	Create::createItem(apple, items, { 31 * 40, 6 * 40 + 9 });
	Create::createItem(apple, items, { 35 * 40 + 13, 11 * 40 });

	//start items
	Item axe(2);
	Item hat(35);
	Item food(44);
	//change pos
	Create::createItem(axe, items, { 5 * 40 + 30,19 * 40 });
	Create::createItem(hat, items, { 5 * 40,19 * 40 });
	Create::createItem(food, items, { 5 * 40 - 30,19 * 40 });

	initializeLogicMap();

	Missions::readMissions();
}

void Game::initializeLogicMap()
{
	Map::readTiles(walls, trees);
	pathfinding.initializeLogicMap(Map::tiles);
	enemySpawner.initializeObjectsPositions(Map::precisePositions);
}

void Game::updateLogicMap()
{
	Map::updateTiles(player, enemies, npcs);
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
	draw->drawObstacles(trees);
	draw->drawEnemiesStatusBar(enemies);
	draw->drawStatusBar(playerHealthBar);
	draw->drawText(notifications);
	draw->drawHUD(hud);

	//player->rect->character->getPathFinding().debugDrawMap(*window);

	window->display();
}

void Game::clearWindow()
{
	window->clear();
}

bool Game::closeWindow()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			return true;
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window->close();
			return true;
		}
	}

	if (player->rect->character->getCurrentHp() <= 0)
	{
		return true;
	}

	return false;
}


