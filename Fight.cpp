#include "Fight.h"

Fight::Fight()
{

}


void Fight::attack(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim)
{
	if (isAttackPossible(attacker,victim))
	{
		attacker->timing.reset();
		int damagedHp = victim->rect->character->getCurrentHp() - attacker->rect->character->getAttackDamage();
		victim->rect->character->setCurrentHp(damagedHp);
	}
}

void Fight::setFighting(std::unique_ptr<Wrapper> & character, bool inp)
{
	character->rect->character->setFighting(inp);
}

bool Fight::isAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim)
{
	return (attacker->timing.getElapsedSeconds() >= (float)(5 / (attacker->rect->character->getAttackSpeed()))
		&& victim->rect->character->isMarked());
}
