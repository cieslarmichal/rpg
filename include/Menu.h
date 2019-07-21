#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow & win);
	~Menu();
	int chooseMode();
private:
	void initialize();
	void currentItemUp();
	void currentItemDown();
	void update();
	void draw();
	void clear();
	int events();
private:
	sf::RenderWindow * window;
	sf::Event event;
	sf::Font font;
	sf::Text menu[3];
	int currentItemIndex = 0;
	const int itemAmount = 3;
	enum class Item { PLAY = 0, OPTIONS = 1, EXIT = 2 };
	enum class Action { NO_ACTION = -1, CANCEL = 0, CONFIRM = 1 };
};

