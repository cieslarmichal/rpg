#include "Mark.h"


void Mark::markEnemy(int key, enemyPair & enemies, sf::RenderWindow & window)
{
	if (key == (int)InputKeys::MOUSELEFT)
	{
		sf::Vector2i windowCoordinates = sf::Mouse::getPosition(window);
		sf::Vector2f worldCoordinates = window.mapPixelToCoords(windowCoordinates);

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

			if (worldCoordinates.x >= x && worldCoordinates.x <= dx && worldCoordinates.y >= y && worldCoordinates.y <= dy)
			{
				enemy.first->rect->character->setMarked(true);
			}
		}
	}
}
