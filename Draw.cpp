#include "Draw.h"

Draw::Draw(sf::RenderWindow & win) : window(win) {}


void Draw::drawPlayer(std::unique_ptr<Wrapper> & player)
{
	window.draw(player->sprite->getSprite());
}

void Draw::drawEnemies(enemyPair & enemies)
{
	/*int counter = 0;
	for (auto & x : enemies)
	{
		window.draw(enemies[counter].first->sprite.getSprite());
		window.draw(enemies[counter].second.rect);
		window.draw(enemies[counter].second.text);
		counter++;
	}*/
	enemyPair::iterator iter = enemies.begin();
	while (iter != enemies.end())
	{
		window.draw(iter->first->sprite->getSprite());

		window.draw(iter->second.getRect());

		window.draw(iter->second.getText()); //read access violation
		++iter;
	}
}

void Draw::drawStatusBar(StatusBar & statusBar)
{
	window.draw(statusBar.getRect());
	window.draw(statusBar.getText());
}

void Draw::drawObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int counter = 0;
	for (std::unique_ptr<Wrapper> & x : obstacles)
	{
		window.draw(obstacles[counter]->sprite->getSprite());
		counter++;
	}
}

void Draw::drawText(std::vector<std::unique_ptr<Text>> & texts)
{
	int counter = 0;
	for (std::unique_ptr<Text> & x : texts)
	{
		window.draw(texts[counter]->getText());
		counter++;
	}
}

void Draw::drawRect(Rect & rect) 
{
	window.draw(rect.rect);
}


void Draw::drawRects(std::vector<std::unique_ptr<Wrapper>> & tests)
{
	int counter = 0;
	for (std::unique_ptr<Wrapper> & x : tests)
	{
		window.draw(tests[counter]->rect->rect);
		counter++;
	}
}