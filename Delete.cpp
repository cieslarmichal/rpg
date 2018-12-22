#include "Delete.h"

void Delete::removeEnemies(enemyPair & enemies)
{
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](std::pair<std::unique_ptr<Wrapper>, StatusBar> & e) {return e.first->rect->character->getDead(); }), enemies.end());
}

void Delete::removeText(std::vector < std::unique_ptr<Text>> & texts)
{
	texts.erase(std::remove_if(texts.begin(), texts.end(), [](std::unique_ptr<Text> & t) {return t->isDestroyed(); }), texts.end());
}

void Delete::removeProjectiles(std::vector<std::unique_ptr<Wrapper>> & projectiles)
{
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](std::unique_ptr<Wrapper> & p) {return p->rect->projectile->isDestroyed(); }), projectiles.end());
}

void Delete::removeBlocked(std::vector<Blocked> & blockedCharacters)
{
	blockedCharacters.erase(std::remove_if(blockedCharacters.begin(), blockedCharacters.end(), [](const Blocked & blocked) {return blocked.isDestroyed(); }), blockedCharacters.end());
}


void Delete::setProjectileToDestroy(std::unique_ptr<Wrapper> & object)
{
	object->rect->projectile->setDestroyed(true);
}

void Delete::setBlockedToDestroy(Blocked & blocked)
{
	blocked.setDestroyed(true);
}
