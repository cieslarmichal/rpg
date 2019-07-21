#pragma once
#include "Menu.h"
#include "Game.h"

class Application
{
public:
	Application();
	~Application();
	void run();
private:
	void createMenuWindow();
	void createGameWindow();
private:
	sf::RenderWindow * app;
	Menu * menu;
	Game * game;
};

