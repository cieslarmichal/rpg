#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
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
#include "ChangeWeapon.h"

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
	void initializePathFindingMap();
	void updatePathFindingMap();
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
	CollisionHandler collisionHandler;
	PathFinding pathfinding;
	Map map;
private:
	Player * characterPlayer;
	Skeleton * characterSkeleton;
	Dragon * characterDragon;
private:
	std::unique_ptr<Wrapper> player;
	StatusBar playerHealthBar;
	std::vector <std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemies;
	std::vector<std::unique_ptr<Wrapper>> projectiles;
	std::vector<std::unique_ptr<Text>> notifications;
	std::vector<std::unique_ptr<Text>> HUDinfo;
	std::vector<std::unique_ptr<Wrapper>> walls;
	std::vector<std::unique_ptr<Wrapper>> floor;
	std::vector<std::unique_ptr<Wrapper>> items;

};
