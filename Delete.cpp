#include "Delete.h"



Delete::Delete()
{
}

void Delete::removeEnemies(enemyPair & enemies)
{

	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](std::pair<std::unique_ptr<Wrapper>, StatusBar> & e) {return e.first->rect->character->getDead(); }), enemies.end());

	//int counter = 0;
	//enemyPair::iterator iter = enemies.begin();
	//while (iter != enemies.end())
	//{
	//	if (iter->first->rect->character->getDead())
	//	{
	//		iter = enemies.erase(iter);
	//	}
	//	else
	//	{
	//		++iter;
	//	}
	//	counter++;
	//}

}

void Delete::removeText(std::vector < std::unique_ptr<Text>> & texts)
{
	texts.erase(std::remove_if(texts.begin(), texts.end(), [](std::unique_ptr<Text> & t) {return t->isDestroyed(); }), texts.end());

}

void Delete::removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](std::unique_ptr<Wrapper> & p) {return p->rect->projectile->isDestroyed(); }), projectiles.end());
}

////delete destroyed walls
//wallArray.erase(std::remove_if(wallArray.begin(), wallArray.end(), [](const Wall & w) {return w.isDestroyed(); }), wallArray.end());
//
////delete destroyed projectiles
//projectileArray.erase(std::remove_if(projectileArray.begin(), projectileArray.end(), [](const Projectile & p) {return p.isDestroyed(); }), projectileArray.end());
//
////delete text
//textDisplayArray.erase(std::remove_if(textDisplayArray.begin(), textDisplayArray.end(), [](std::unique_ptr<TextDisplay> & t) {return t->isDestroyed(); }), textDisplayArray.end());
//
////delete pickup items
//pickupArray.erase(std::remove_if(pickupArray.begin(), pickupArray.end(), [](const Pickup & c) {return c.isCollected(); }), pickupArray.end());
//
////delete dead enemy, wrong auto read
////enemyArray.erase(std::remove_if(enemyArray.begin(), enemyArray.end(), [](auto & e) {return e-> }), enemyArray.end());
//enemyArray.erase(std::remove_if(enemyArray.begin(), enemyArray.end(), [](std::unique_ptr<Enemy> & e) {return e->getDead(); }), enemyArray.end());
