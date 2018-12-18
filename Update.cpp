#include "Update.h"



Update::Update()
{
}


void Update::updatePlayer(std::unique_ptr<Wrapper> & player, StatusBar & statBar, int direction)
{
	bool flagMovement = movement.move(*player->rect, direction); //movement
	if (flagMovement) player->animation->update(direction); //update animation
	player->sprite->setPosition(player->rect->getPosition()); //synchronize sprite with rect
	statBar.update(player); // update status bar health
	player->rect->setEdges(); // calculate edges distances
}

void Update::updateEnemies(enemyPair & enemies, int nothing)
{
	int counter = 0;
	for (std::pair<std::unique_ptr<Wrapper>, StatusBar > & x : enemies)
	{
		bool flagMovement = movement.moveRandom(*enemies[counter].first->rect);
		if (flagMovement) enemies[counter].first->animation->update(enemies[counter].first->rect->character->getDirection());
		enemies[counter].first->sprite->setPosition(enemies[counter].first->rect->getPosition());
		enemies[counter].second.update(enemies[counter].first); // update status bar health
		enemies[counter].first->rect->setEdges();
		if (enemies[counter].first->rect->character->getCurrentHp() <= 0)
		{
			enemies[counter].first->rect->character->setDead(true);
		}
		counter++;
	}
}

void Update::updateObstacles(std::vector<std::unique_ptr<Wrapper>> & obstacles)
{
	int counter = 0;
	for (std::unique_ptr<Wrapper> & x : obstacles)
	{
		obstacles[counter]->sprite->setPosition(obstacles[counter]->rect->getPosition());
		counter++;
	}
}

void Update::updateText(std::vector<std::unique_ptr<Text>> & texts, sf::View view)
{
	int counter = 0;
	for (std::unique_ptr<Text> & x : texts)
	{
		movement.moveText(*texts[counter]);
		texts[counter]->update(view);
		counter++;
	}
}

void Update::updateProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles, enemyPair & enemies)
{
	int counter = 0;
	for (std::unique_ptr<Wrapper> & x : projectiles)
	{
		movement.moveProjectile(*projectiles[counter]->rect, enemies);
		projectiles[counter]->sprite->setPosition(projectiles[counter]->rect->getPosition().x-10, projectiles[counter]->rect->getPosition().y-15);
		counter++;
	}
}


