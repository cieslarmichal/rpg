#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Text.h"
#include <vector>

typedef std::vector<std::pair<std::unique_ptr<Wrapper>, StatusBar>> enemyPair;
class Draw
{
public:
	Draw(sf::RenderWindow & win) : window(win) {}
	void drawPlayer(std::unique_ptr<Wrapper> & player);
	void drawEnemies(enemyPair & enemies);
	void drawStatusBar(StatusBar & rect);
	void drawObstacles(std::vector<std::unique_ptr<Wrapper>> & rects); //draw projectiles also
	void drawText(std::vector<std::unique_ptr<Text>> & texts);
	void drawRect(Rect & rect);
	void drawRects(std::vector<std::unique_ptr<Wrapper>> & tests);
private:
	sf::RenderWindow & window;
};

