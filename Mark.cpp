#include "Mark.h"


void Mark::markTarget(int key, std::unique_ptr<Wrapper> & player, enemyPair & enemies, sf::RenderWindow & window)
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
			int x = (int)enemy.first->sprite->getPosition().x;
			int dx = x + enemy.first->sprite->getSpriteX();
			int y = (int)enemy.first->sprite->getPosition().y;
			int dy = y + enemy.first->sprite->getSpriteY();

			if (worldCoordinates.x >= x && worldCoordinates.x <= dx && worldCoordinates.y >= y && worldCoordinates.y <= dy)
			{
				enemy.first->rect->character->setMarked(true);
			}
		}

	}
	else if (key == (int)InputKeys::MOUSERIGHT)
	{
		sf::Vector2i windowCoordinates = sf::Mouse::getPosition(window);
		sf::Vector2f worldCoordinates = window.mapPixelToCoords(windowCoordinates);
		player->rect->character->setTargetPosition(sf::Vector2i{ ((int)worldCoordinates.x - 20) ,((int)worldCoordinates.y - 20) });
	}
}


