#include "Game.h"



Game::Game()
{
	//messages w collisionhandler
	//virtualna metoda atakujaca np w charackter
	// ogarnac w draw tez uniwersalne metody
	//pokoje potworzyc do testowania pathfinding dobre
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
	Player characterPlayer("michal", 100,5, 20, 3,20, 20, 2);
	std::unique_ptr<Wrapper> player = Create::createPlayer(characterPlayer,{700,250});

	std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar> > enemies;
	Skeleton characterSkeleton("skeleton", 100, 5,1, 70, 0, 1.5, 0);

	Create::createSkeleton(characterSkeleton, enemies, { 150,150 });
	Create::createSkeleton(characterSkeleton, enemies, { 200,150 });
	Create::createSkeleton(characterSkeleton, enemies, { 200,200 });

	std::vector<std::unique_ptr<Wrapper>> projectiles;

	std::vector<std::unique_ptr<Text>> messages;

	std::vector<std::unique_ptr<Wrapper>> obstacles;
	//Create::createRoom(5, { 0, 0 }, 3, -10, 2, -10, obstacles);;
	//Create::createRoom(10, { 5 * 32, 0 }, 2, 3, -10, 5, obstacles);
	//Create::createRoom(7, { 5 * 32, 10 * 32 }, -10, -10, 5, -10, obstacles);


	while (window.isOpen())
	{
		clearWindow(window);

		collisionHandler.characterWithObstacles(player, obstacles);
		collisionHandler.enemiesWithObstacles(enemies, obstacles);
		collisionHandler.enemiesWithEnemies(enemies);
		collisionHandler.playerWithEnemies(player, enemies);
		collisionHandler.projectilesWithWalls(projectiles, obstacles);
		collisionHandler.projectilesWithEnemies(projectiles, enemies);

		Delete::removeText(messages);
		Delete::removeProjectiles(projectiles);
		Delete::removeEnemies(enemies);
	
		int *inputKeys = input.read();
		Mark::markEnemy(inputKeys[Input::ACTION], enemies, window);

		Shoot::shootEnemy(player, enemies, projectiles);

		Update::updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION]);
		Update::updateEnemies(enemies, player);
		Update::updateText(messages, view);
		Update::updateObstacles(obstacles);
		Update::updateProjectiles(projectiles, enemies);


		draw.drawObstacles(obstacles);
		draw.drawProjectiles(projectiles);
		draw.drawStatusBar(playerHealthBar);
		draw.drawEnemies(enemies);
		draw.drawPlayer(player);
		draw.drawText(messages);
	

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
