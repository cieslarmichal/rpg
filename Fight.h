#pragma once
#include "Wrapper.h"
#include "Create.h"
#include "Text.h"
#include "LevelManager.h"
#include "Delete.h"

class Fight
{
public:
	Fight() = delete;
	static void attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim,
		std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items);
	static void attackDistance(std::unique_ptr<Player> & player, std::unique_ptr<Wrapper> & projectile,
		std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items);
	static void setFightingMode(std::unique_ptr<Wrapper> & character, bool isFighting);
private:
	static bool isMeleeAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);
};
