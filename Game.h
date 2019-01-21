#pragma once
#include "Draw.h"
#include "Input.h"
#include "Movement.h"
#include "Wrapper.h"
#include "Update.h"
#include "CollisionHandler.h"
#include "Delete.h"
#include "Create.h"
#include "Mark.h"
#include "Shoot.h"
#include "PathFinding.h"
#include "Map.h"
#include "EnemySpawner.h"
#include "Missions.h"

class Game
{
public:
	Game(sf::RenderWindow &);
	~Game();
	bool run();
private:
	void initialize();
	void createCharacters();
	void createWorld();
	void initializeLogicMap();
	void updateLogicMap();
	bool gameLoop();
	void updatePlayerView();
	void drawWindow();
	void clearWindow();
	bool closeWindow();
private:
	sf::RenderWindow * window;
	sf::View * playerView;
	TimeHandler logicMapTimer, respawnTimer, deltaTimer;
	float dt;
	Input input;
	std::unique_ptr<Draw> draw;
	EnemySpawner enemySpawner;
	CollisionHandler collisionHandler;
	PathFinding pathfinding;
private:
	std::unique_ptr<Player> characterPlayer;
	std::unique_ptr<Npc> characterNpc;
private:
	HUD hud;
	std::unique_ptr<Wrapper> player;
	StatusBar playerHealthBar;
	std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemies;
	std::vector<std::pair<std::unique_ptr<Wrapper>, StatusBar>> npcs;
	std::vector<std::unique_ptr<Wrapper>> projectiles;
	std::vector<std::unique_ptr<Text>> notifications;
	std::vector<std::unique_ptr<Wrapper>> walls;
	std::vector<std::unique_ptr<Wrapper>> floor;
	std::vector<std::unique_ptr<Wrapper>> items;
};
