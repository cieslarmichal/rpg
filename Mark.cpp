#include "Mark.h"



Mark::Mark()
{
}


void Mark::markEnemy(int key, enemyPair & enemies, sf::RenderWindow & window)
{
	if (key == RIGHTMOUSE)
	{
		//conversion view to window mouse coordinates 
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		// convert it to world coordinates
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		//unmark all enemies
		for (std::pair<std::unique_ptr<Wrapper>, StatusBar > & x : enemies)
		{
			x.first->rect->character->setMarked(false);
		}

		//mark particular one enemy
		int counter = 0;
		for (std::pair<std::unique_ptr<Wrapper>, StatusBar > & x : enemies)
		{
			int x = enemies[counter].first->rect->getPosition().x;
			int dx = x + enemies[counter].first->rect->getDimX();
			int y = enemies[counter].first->rect->getPosition().y;
			int dy = y + enemies[counter].first->rect->getDimY();

			if (worldPos.x >= x && worldPos.x <= dx && worldPos.y >= y && worldPos.y <= dy)
			{
				enemies[counter].first->rect->character->setMarked(true);
			}
			counter++;
		}
	}
}
