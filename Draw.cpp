#include "Draw.h"

Draw::Draw(sf::RenderWindow & win) : window(win) {}


void Draw::drawPlayer(std::unique_ptr<Wrapper> & player)
{
	window.draw(player->sprite->getSprite());
}

void Draw::drawStatusBar(StatusBar & statusBar)
{
	window.draw(statusBar.getRect());
	window.draw(statusBar.getText());
}

void Draw::drawEnemies(enemyPair & enemies)
{
	for (auto & enemy : enemies)
	{
		window.draw(enemy.first->sprite->getSprite());
		window.draw(enemy.second.getRect());
		window.draw(enemy.second.getText());
	}
}

void Draw::drawObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	for (std::unique_ptr<Wrapper> & obstacle : obstacles)
	{
		window.draw(obstacle->sprite->getSprite());
	}
}

void Draw::drawProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	drawObstacles(projectiles);
}

void Draw::drawItems(std::vector<std::unique_ptr<Wrapper>> & items)
{
	drawObstacles(items);
}

void Draw::drawHUDItems(std::vector<std::unique_ptr<Wrapper>>& HUDItems)
{
	drawRects(HUDItems);
	drawObstacles(HUDItems);
}

void Draw::drawHUDSlots(std::vector<std::unique_ptr<Rect>>& HUDInventorySlots)
{
	for (auto & slot : HUDInventorySlots)
	{
		window.draw(slot->getRect());
	}
}

void Draw::drawText(std::vector<std::unique_ptr<Text>> & texts)
{
	for (std::unique_ptr<Text> & text : texts)
	{
		window.draw(text->getText());
	}
}

void Draw::drawRect(Rect & rect)
{
	window.draw(rect.getRect());
}


void Draw::drawRects(std::vector<std::unique_ptr<Wrapper>> & tests)
{
	for (std::unique_ptr<Wrapper> & test : tests)
	{
		window.draw(test->rect->getRect());
	}
}

void Draw::drawRects(enemyPair & enemies)
{
	for (auto & enemy : enemies)
	{
		window.draw(enemy.first->rect->getRect());
	}
}