#pragma once
#include "Wrapper.h"
class Fight
{
public:
	Fight();
	static void attack(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);
	static void setFighting(std::unique_ptr<Wrapper> & character, bool isFighting);
private:
	static bool isAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim);

};

