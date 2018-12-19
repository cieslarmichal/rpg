#include "Game.h"



Game::Game()
{
	//jesli bledy vectora to w collisionPlayerWithEnemy odkomentowac

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
	view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
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
	Player characterPlayer("michal", 20, 20, 20, 20, 20, 20, 2);
	std::unique_ptr<Wrapper> player = creator.createPlayer(characterPlayer,{200,250});

	std::vector < std::pair<std::unique_ptr<Wrapper>, StatusBar> > enemies;
	// adding enemy
	Skeleton characterSkeleton("skeleton", 100000, 5, 0, 70, 0, 1.5, 0);
	creator.createSkeleton(characterSkeleton, enemies, { 300,300 });
	//creator.createSkeleton(characterSkeleton, enemies, { 400,300 });

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

		// collision player with walls
		collisionHandler.playerWithObstacles(player, obstacles);

		//collision player with enemies
		bool anyCollision = collisionHandler.playerWithEnemies(player, enemies, messages);
		if (!anyCollision) // setting possibility to move with blocked direction from previous collision 
		{
			player->rect->character->setCanMoveNum(collisionHandler.playerCantMove);
			if (collisionHandler.enemyIndex > CollisionHandler::OUT)
			{
				enemies[collisionHandler.enemyIndex].first->rect->character->setCanMoveNum(collisionHandler.enemyCantMove);
				collisionHandler.enemyCantMove = CollisionHandler::RESET;
				collisionHandler.enemyIndex = CollisionHandler::OUT;
			}
			collisionHandler.playerCantMove = CollisionHandler::RESET;
		}

		//collision enemies with walls
		collisionHandler.enemiesWithObstacles(enemies, obstacles);

		//collision projectiles with walls
		collisionHandler.projectilesWithWalls(projectiles, obstacles);

		//collision projectiles with enemies
		collisionHandler.projectilesWithEnemies(projectiles, enemies, messages);

		//delete texts
		deleter.removeText(messages);

		//delete projectiles
		deleter.removeProjectiles(projectiles);

		//delete enemies
		deleter.removeEnemies(enemies);

		//input from keyboard
		int inputKey = input.read();

		//update player
		updater.updatePlayer(player, playerHealthBar, inputKey);

		//mark enemy if mouse is clicked on him
		marker.markEnemy(inputKey, enemies, window);

		//shoot target enemy, creating projectiles
		shooter.shootEnemy(player,enemies,projectiles);

		//update enemies
		updater.updateEnemies(enemies, player);

		//update texts
		updater.updateText(messages, view);

		// update obstacles
		updater.updateObstacles(obstacles);

		//update projectiles
		updater.updateProjectiles(projectiles,enemies);

		//draw obstacles
		draw.drawObstacles(obstacles);

		//draw player healthBar
		draw.drawStatusBar(playerHealthBar);

		//draw enemies
		draw.drawEnemies(enemies);

		//draw player
		draw.drawPlayer(player);

		//draw texts
		draw.drawText(messages);

		//draw projectiles
		draw.drawObstacles(projectiles);

		//player view
		window.setView(view);
		view.setCenter(player->rect->rect.getPosition());

		window.display();
	}
	return true;
}

