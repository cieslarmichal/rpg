#include "Fight.h"


void Fight::attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications)
{
	if (isMeleeAttackPossible(attacker, victim))
	{
		attacker->timing.reset();
		int damagedHp = victim->rect->character->getCurrentHp() - attacker->rect->character->getAttackDamage();
		victim->rect->character->setCurrentHp(damagedHp);

		Create::createBattleNotification(attacker->rect->character->getAttackDamage(), victim->rect->getPosition(), notifications);
	}
}

void Fight::attackDistance(std::unique_ptr<Wrapper> & projectile, std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications)
{
	int damagedHp = victim->rect->character->getCurrentHp() - projectile->rect->projectile->getDamage();
	victim->rect->character->setCurrentHp(damagedHp);

	Create::createBattleNotification(projectile->rect->projectile->getDamage(), victim->rect->getPosition(), notifications);
}

void Fight::setFightingMode(std::unique_ptr<Wrapper> & character, bool inp)
{
	character->rect->character->setFighting(inp);
}

bool Fight::isMeleeAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim)
{
	return (attacker->timing.getElapsedSeconds() >= (float)(5 / (attacker->rect->character->getAttackSpeed()))
		&& victim->rect->character->isMarked() && attacker->rect->character->getWeapon() == (int)Weapons::MELEE);
}
