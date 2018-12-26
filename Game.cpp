#include "Game.h"



Game::Game()
{
	//vector przechowujacy pozycje wszystkich obiektow 40x40 px
	//virtualna metoda atakujaca np w charackter
	//randomize with marsenne
	//pathfinding
	//dodac dragona
	//dodac inventory
	//std::pair playera z healthBar
	//loot z potworow
	//konczyc to bo trzeba tmp robic tez
}


Game::~Game()
{
}

bool Game::play()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "RPG game");
	window.setPosition(sf::Vector2i(10, 50));
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(200, 200, 300, 200));
	view.setSize(sf::Vector2f(sf::Vector2u(window.getSize())));
	view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
	window.setView(view);

	Input input;
	Draw draw(window);
	CollisionHandler collisionHandler;

	StatusBar playerHealthBar;
	Player characterPlayer("michal", 100, 5, 20, 3, 20, 20, 2);
	std::unique_ptr<Wrapper> player = Create::createPlayer(characterPlayer, { 800,220 });

	std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemies;
	Skeleton characterSkeleton("skeleton", 100, 5, 1, 70, 0, 1.5, 0);

	Create::createSkeleton(characterSkeleton, enemies, { 150,150 });
	Create::createSkeleton(characterSkeleton, enemies, { 300,150 });
	Create::createSkeleton(characterSkeleton, enemies, { 300,200 });

	std::vector<std::unique_ptr<Wrapper>> projectiles;

	std::vector<std::unique_ptr<Text>> notifications;

	std::vector<std::unique_ptr<Wrapper>> walls;
	std::vector<std::unique_ptr<Wrapper>> floor;
	Create::createRoom(5, { 0, 0 }, 3, -10, 2, -10, walls, floor);
	Create::createRoom(10, { 5 * 40, 0 }, 2, 3, 6, 5, walls, floor);
	Create::createRoom(7, { 15 * 40,0 }, 5, 2, -10, -10, walls, floor);
	Create::createRoom(6, { 20 * 40,7 * 40 }, -10, -10, 3, -10, walls, floor);
	Create::createRoom(13, { 5 * 40, -40 * 13 }, -10, -10, 4, 6, walls, floor);
	Create::createRoom(7, { 5 * 40, 10 * 40 }, -10, -10, 5, -10, walls, floor);
	Create::createRoom(4, { 22 * 40,3 * 40 }, -10, 2, -10, 1, walls, floor);


	while (window.isOpen())
	{
		clearWindow(window);

		collisionHandler.characterWithObstacles(player, walls);
		collisionHandler.enemiesWithObstacles(enemies, walls);
		collisionHandler.enemiesWithEnemies(enemies);
		collisionHandler.playerWithEnemies(player, enemies, notifications);
		collisionHandler.projectilesWithWalls(projectiles, walls);
		collisionHandler.projectilesWithEnemies(projectiles, enemies, notifications);

		Delete::removeText(notifications);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);

		int *inputKeys = input.read();
		Mark::markEnemy(inputKeys[Input::ACTION], enemies, window);

		Shoot::shootEnemy(player, enemies, projectiles);

		Update::updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION]);
		Update::updateEnemies(enemies, player);
		Update::updateText(notifications, view);
		Update::updateObstacles(walls);
		Update::updateObstacles(floor);
		Update::updateProjectiles(projectiles, enemies);


		draw.drawObstacles(floor);
		draw.drawObstacles(walls);
		draw.drawProjectiles(projectiles);
		draw.drawStatusBar(playerHealthBar);
		draw.drawEnemies(enemies);
		draw.drawPlayer(player);
		draw.drawText(notifications);
		//draw.drawRects(enemies);


		window.setView(view);
		view.setCenter(player->rect->rect.getPosition());
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
