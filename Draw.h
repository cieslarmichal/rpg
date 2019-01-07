#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"

typedef std::vector<std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;
class Draw
{
public:
	Draw(sf::RenderWindow & win);
	void drawPlayer(std::unique_ptr<Wrapper> & player);
	void drawEnemies(enemyPair & enemies);
	void drawStatusBar(StatusBar & statusBar);
	void drawObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void drawProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles);
	void drawItems(std::vector<std::unique_ptr<Wrapper>> & items);
	void drawHUDItems(std::vector<std::unique_ptr<Wrapper>> & HUDItems);
	void drawHUDSlots(std::vector<std::unique_ptr<Rect>> & HUDInventorySlots);
	void drawText(std::vector<std::unique_ptr<Text>> & texts);
	void drawRect(Rect & rect);
	void drawRects(std::vector<std::unique_ptr<Wrapper>> & tests);
	void drawRects(enemyPair & enemies);
private:
	sf::RenderWindow & window;
};
