#pragma once
#include "Wrapper.h"
#include "Create.h"
#include "Text.h"

class Fight
{
public:
	Fight() = delete;
	static void attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications);
	static void attackDistance(std::unique_ptr<Wrapper> & projectile, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications);
	static void setFightingMode(std::unique_ptr<Wrapper> & character, bool isFighting);
private:
	static bool isMeleeAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);
};
