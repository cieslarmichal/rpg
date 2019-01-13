#pragma once
#include "Character.h"
#include "Draw.h"
#include "Rect.h"
#include "Sprite.h"
#include "Player.h"
#include "Input.h"
#include "Movement.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Obstacle.h"
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
#include "Npc.h"


class Game
{
public:
	Game();
	~Game();
	bool run();
private:
	void initialize();
	void createCharacters();
	void createWorld();
	void initializeLogicMap();
	void updateLogicMap();
	void gameLoop();
	void updatePlayerView();
	void drawWindow();
	void clearWindow();
private:
	sf::RenderWindow * window;
	sf::View * playerView;
	TimeHandler timer;
	Input input;
	Draw * draw;
	EnemySpawner enemySpawner;
	CollisionHandler collisionHandler;
	PathFinding pathfinding;
private:
	Player * characterPlayer;
	Npc * characterNpc;
private:
	HUD hud;
	std::unique_ptr<Wrapper> player;
	StatusBar playerHealthBar;
	std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemies;
	std::vector<std::unique_ptr<Wrapper>> npcs;
	std::vector<std::unique_ptr<Wrapper>> projectiles;
	std::vector<std::unique_ptr<Text>> notifications;
	std::vector<std::unique_ptr<Wrapper>> walls;
	std::vector<std::unique_ptr<Wrapper>> floor;
	std::vector<std::unique_ptr<Wrapper>> items;
};
