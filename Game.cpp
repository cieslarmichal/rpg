#include "Game.h"



Game::Game()
{
	//kolizja enemy vs enemy
	//virtualna metoda atakujaca np w charackter
	// posprzatac komentarze
	// klasy w collisionhandler obslugujace wymiane dmg z okreslona predkoscia
	//ogarnac collisionhandler zmniejszyc liczbe metod
	// ogarnac w draw tez uniwersalne metody
	//pokoje potworzyc do testowania pathfinding dobre
	//show must go on
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
	// window
	sf::RenderWindow window(sf::VideoMode(1000, 800), "RPG game");
	window.setPosition(sf::Vector2i(10, 50));
	window.setFramerateLimit(60);

	//View
	sf::View view(sf::FloatRect(200, 200, 300, 200));
	view.setSize(sf::Vector2f(sf::Vector2u(window.getSize())));
	view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
	window.setView(view);

	Input input;
	Update updater;
	Draw draw(window);
	CollisionHandler collisionHandler;
	Delete deleter;
	Create creator;
	Mark marker;
	Shoot shooter;

	//adding player
	StatusBar playerHealthBar;
	Player characterPlayer("michal", 100,5, 20, 10,20, 20, 2);
	std::unique_ptr<Wrapper> player = creator.createPlayer(characterPlayer,{200,250});

	std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar> > enemies;
	// adding enemy
	Skeleton characterSkeleton("skeleton", 100, 5,1, 70, 0, 1.5, 0);
	creator.createSkeleton(characterSkeleton, enemies, { 200,150 });
	creator.createSkeleton(characterSkeleton, enemies, { 350,150 });
	creator.createSkeleton(characterSkeleton, enemies, { 200,200 });

	//projectiles vector
	std::vector<std::unique_ptr<Wrapper>> projectiles;

	//texts vector
	std::vector<std::unique_ptr<Text>> messages;

	//adding walls
	std::vector<std::unique_ptr<Wrapper>> obstacles;
	creator.createRoom(5, { 0, 0 }, 3, -10, 2, -10, obstacles);;
	creator.createRoom(10, { 5 * 32, 0 }, 2, 3, -10, 5, obstacles);
	creator.createRoom(7, { 5 * 32, 10 * 32 }, -10, -10, 5, -10, obstacles);


	while (window.isOpen())
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

		{
			collisionHandler.characterWithObstacles(player, obstacles);
			collisionHandler.playerWithEnemies(player, enemies, messages);
			collisionHandler.enemiesWithObstacles(enemies, obstacles);
			collisionHandler.projectilesWithWalls(projectiles, obstacles);
			collisionHandler.projectilesWithEnemies(projectiles, enemies, messages);
		}

		{
			deleter.removeText(messages);
			deleter.removeProjectiles(projectiles);
			deleter.removeEnemies(enemies);
		}

		int *inputKeys = input.read();

		//mark enemy if mouse is clicked on him
		marker.markEnemy(inputKeys[Input::ACTION], enemies, window);

		//shoot marked enemy, creating projectiles
		//shooter.shootEnemy(player, enemies, projectiles);

		{
			updater.updatePlayer(player, playerHealthBar, inputKeys[Input::DIRECTION]);
			updater.updateEnemies(enemies, player);
			updater.updateText(messages, view);
			updater.updateObstacles(obstacles);
			updater.updateProjectiles(projectiles, enemies);
		}

		{
			draw.drawObstacles(obstacles);
			draw.drawStatusBar(playerHealthBar);
			draw.drawEnemies(enemies);
			draw.drawPlayer(player);
			draw.drawText(messages);
			//draw projectiles
			draw.drawObstacles(projectiles);
		}

		window.setView(view);
		view.setCenter(player->rect->rect.getPosition());
		
		window.display();
	}
	return true;
}

