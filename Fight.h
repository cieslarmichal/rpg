#pragma once
#include "Wrapper.h"
#include "Create.h"

class Fight
{
public:
	Fight() = delete;
	static void attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);
	static void attackDistance(std::unique_ptr<Wrapper> & projectile, std::unique_ptr<Wrapper> & victim);
	static void setFightingMode(std::unique_ptr<Wrapper> & character, bool isFighting);
private:
	static bool isAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);
};
