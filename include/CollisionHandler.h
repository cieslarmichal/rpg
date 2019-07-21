#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Constants.h"
#include "Fight.h"
#include "Blocked.h"
#include "Delete.h"
#include "Item.h"
#include "HUD.h"
#include "Interaction.h"


using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, std::unique_ptr<StatusBar>>>;

class CollisionHandler
{
public:
	bool isIntersecting(Rect & rectangle1, Rect & rectangle2) const;
	void characterWithObstacles(std::unique_ptr<Wrapper> & character, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void characterWithObstacles(std::unique_ptr<Wrapper> & character, vectorOfCharacters & obstacles);
	void playerWithNpcs(std::unique_ptr<Wrapper> & player, vectorOfCharacters & npcs,
		std::vector<std::unique_ptr<Text>> & messages, int actionKey);
	void enemiesWithNpcs(vectorOfCharacters & enemies, vectorOfCharacters & npcs);
	void enemiesWithObstacles(vectorOfCharacters & enemies, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void playerWithEnemies(std::unique_ptr<Wrapper> & player, vectorOfCharacters & enemies,
		std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items);
	void enemiesWithEnemies(vectorOfCharacters & enemies);
	void projectilesWithEnemies(std::unique_ptr<Wrapper> & player, std::vector<std::unique_ptr<Wrapper>> & projectiles,
		vectorOfCharacters & enemies, std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items);
	void projectilesWithWalls(std::vector<std::unique_ptr<Wrapper>> & projectiles, std::vector<std::unique_ptr<Wrapper>> & obstacles);
	void playerWithItems(std::unique_ptr<Wrapper> & player, std::vector <std::unique_ptr<Wrapper>> & items, int actionKey);
private:
	enum { TOP = 0, BOT = 1, LEFT = 2, RIGHT = 3 };
	std::vector<Blocked> blockedCharacters;
	std::vector<Blocked> blockedEnemies;
private:
	void setEnemyCollidingWithPlayer(std::vector<bool> & enemiesCollidingWithPlayer, int enemyIndex, bool isColliding);
	bool possibleToAddBlockedCharacter(int characterIndex, int direction);
	bool possibleToAddBlockedEnemy(int enemyIndex, int direction);
	void addBlockedCharacter(int characterIndex, int direction);
	void addBlockedEnemy(int enemyIndex, int direction);
	bool canUnclockPlayerDirection(const Blocked & blocked, bool * playerCollision);
	bool canUnlockEnemyDirection(const Blocked & blocked, bool enemyCollidingWithPlayer, int enemyIndex);
	bool canUnlockEnemyDirection(const Blocked & blocked, std::vector<bool> enemyCollision, int enemyIndex);
	void unlockBlockedCharacter(std::unique_ptr<Wrapper> & character, Blocked & blocked);
	bool topDistanceShortest(int * distances);
	bool botDistanceShortest(int * distances);
	bool leftDistanceShortest(int * distances);
	bool rightDistanceShortest(int * distances);
};
