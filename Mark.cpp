#include "Mark.h"


void Mark::markEnemy(int key, enemyPair & enemies, sf::RenderWindow & window)
{
	if (key == (int)InputKeys::MOUSELEFT)
	{
		//conversion view to window mouse coordinates 
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		// convert it to world coordinates
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		for (auto & enemy : enemies)
		{
			enemy.first->rect->character->setMarked(false);
		}

		for (auto & enemy : enemies)
		{
			int x = (int)enemy.first->rect->getPosition().x;
			int dx = x + enemy.first->rect->getDimX();
			int y = (int)enemy.first->rect->getPosition().y;
			int dy = y + enemy.first->rect->getDimY();

			if (worldPos.x >= x && worldPos.x <= dx && worldPos.y >= y && worldPos.y <= dy)
			{
				enemy.first->rect->character->setMarked(true);
			}
		}
	}
}
