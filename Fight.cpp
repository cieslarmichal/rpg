#include "Fight.h"


void Fight::attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim, 
	std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items)
{
	if (isMeleeAttackPossible(attacker, victim))
	{
		attacker->timing.reset();
		int damagedHp = victim->rect->character->getCurrentHp() - attacker->rect->character->getAttackDamage();
		victim->rect->character->setCurrentHp(damagedHp);

		if (victim->rect->character->getCurrentHp() <= 0)
		{
			Delete::setCharacterDead(victim);
			if (victim->rect->enemy != nullptr)
			{
				LevelManager::getExperience(attacker->rect->player, victim->rect->enemy);
				Item item(Item::Type::COIN, 1);
				Create::createItem(item, items, sf::Vector2f(victim->rect->getPosition().x + 4, victim->rect->getPosition().y + 18));
			}
		}

		if (attacker->rect->player != nullptr)
		{
			attacker->rect->player->meleeHitsUp();
		}

		Create::createDamageMessage(attacker->rect->character->getAttackDamage(), victim->rect->getPosition(), notifications);
	}
}

void Fight::attackDistance(std::unique_ptr<Player> & player, std::unique_ptr<Wrapper> & projectile,
	std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items)
{
	int damagedHp = victim->rect->character->getCurrentHp() - projectile->rect->projectile->getDamage();
	victim->rect->character->setCurrentHp(damagedHp);

	if (victim->rect->character->getCurrentHp() <= 0)
	{
		Delete::setCharacterDead(victim);
		if (victim->rect->enemy != nullptr)
		{
			LevelManager::getExperience(player, victim->rect->enemy);
			// random process selecting which item
			////////////////////////////////////////
			///////////////////////////////////////////
			Item item(Item::Type::COIN, 1);
			Create::createItem(item, items, sf::Vector2f(victim->rect->getPosition().x + 4, victim->rect->getPosition().y + 18));
		}
	}

	Create::createDamageMessage(projectile->rect->projectile->getDamage(), victim->rect->getPosition(), notifications);
}

void Fight::setFightingMode(std::unique_ptr<Wrapper> & character, bool inp)
{
	character->rect->character->setFighting(inp);
}

bool Fight::isMeleeAttackPossible(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim)
{
	bool weaponCondition = (attacker->rect->player != nullptr) ? (attacker->rect->player->getWeapon() == (int)Weapons::MELEE) : true;
	return (attacker->timing.getElapsedSeconds() >= (float)(5 / (attacker->rect->character->getAttackSpeed()))
		&& victim->rect->character->isMarked() && weaponCondition);
}
