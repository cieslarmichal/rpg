#include "Fight.h"


void Fight::attackMelee(std::unique_ptr<Wrapper> & attacker, std::unique_ptr<Wrapper> & victim,
	std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items)
{
	if (isMeleeAttackPossible(attacker, victim))
	{
		attacker->timing.reset();
		int effectiveDamage = calculateEffectiveDamage(attacker->rect->character->getAttackDamage()) - calculateEffectiveDefense(victim->rect->character->getDefense());
		effectiveDamage = (effectiveDamage > 0) ? effectiveDamage : 0;
		int damagedHp = victim->rect->character->getCurrentHp() - effectiveDamage;
		victim->rect->character->setCurrentHp(damagedHp);

		if (victim->rect->character->getCurrentHp() <= 0)
		{
			Delete::setCharacterDead(victim);

			if (victim->rect->enemy != nullptr)
			{
				LevelManager::getExperience(attacker->rect->player, victim->rect->enemy);

				int randomItemID = Item::randomizeItemID(victim->rect->enemy->getLootChance());
				if (randomItemID != (int)Item::Id::NOTHING)
				{
					Item item(randomItemID);
					Create::createItem(item, items, sf::Vector2f(victim->rect->getPosition().x + 4, victim->rect->getPosition().y + 18));
				}

				Missions::updateKilled(checkEnemyType(victim->rect->enemy));
			}
		}

		if (attacker->rect->player != nullptr)
		{
			attacker->rect->player->meleeHitsUp();
		}

		Create::createDamageMessage(effectiveDamage, victim->rect->getPosition(), notifications);
	}
}

void Fight::attackDistance(std::unique_ptr<Player> & player, std::unique_ptr<Wrapper> & projectile,
	std::unique_ptr<Wrapper> & victim, std::vector<std::unique_ptr<Text>> & notifications, std::vector<std::unique_ptr<Wrapper>> & items)
{
	int effectiveDamage = calculateEffectiveDamage(projectile->rect->projectile->getDamage()) - calculateEffectiveDefense(victim->rect->character->getDefense());
	effectiveDamage = (effectiveDamage > 0) ? effectiveDamage : 0;
	int damagedHp = victim->rect->character->getCurrentHp() - effectiveDamage;
	victim->rect->character->setCurrentHp(damagedHp);

	if (victim->rect->character->getCurrentHp() <= 0)
	{
		Delete::setCharacterDead(victim);

		if (victim->rect->enemy != nullptr)
		{
			LevelManager::getExperience(player, victim->rect->enemy);

			int randomItemID = Item::randomizeItemID(victim->rect->enemy->getLootChance());

			if (randomItemID != (int)Item::Id::NOTHING)
			{
				Item item(randomItemID);
				Create::createItem(item, items, sf::Vector2f(victim->rect->getPosition().x + 4, victim->rect->getPosition().y + 18));
			}

			Missions::updateKilled(checkEnemyType(victim->rect->enemy));
		}
	}

	Create::createDamageMessage(effectiveDamage, victim->rect->getPosition(), notifications);
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

int Fight::calculateEffectiveDamage(int attackDamage)
{
	int effectiveDamage = 0;

	int attackType = randomizeAttackType();

	switch (attackType)
	{
	case AttackType::WEAK:
		return attackDamage * Random::getRandomNumber(30, 50) / 100;
		break;
	case AttackType::NORMAL:
		return attackDamage * Random::getRandomNumber(50, 85) / 100;
		break;
	case AttackType::CRITICAL:
		return attackDamage * Random::getRandomNumber(85, 100) / 100;
		break;
	}

	return effectiveDamage;
}

int Fight::calculateEffectiveDefense(int defense)
{
	int effectiveDefense = (int)(defense*0.4);
	return effectiveDefense;
}

int Fight::randomizeAttackType()
{
	std::vector<std::vector<int>> attackTypes{ {1,2},{3,4,5,6,7,8,9},{10} };

	int randomType = Random::getRandomNumber(1, 10);

	if (containsValue(attackTypes[AttackType::WEAK], randomType))
	{
		return AttackType::WEAK;
	}
	else if (containsValue(attackTypes[AttackType::NORMAL], randomType))
	{
		return AttackType::NORMAL;
	}
	else if (containsValue(attackTypes[AttackType::CRITICAL], randomType))
	{
		return AttackType::CRITICAL;
	}

	return int(Others::RESET);
}

bool Fight::containsValue(std::vector<int>  values, int value)
{
	for (auto val : values)
	{
		if (value == val)
		{
			return true;
		}
	}
	return false;
}

int Fight::checkEnemyType(std::unique_ptr<Enemy>& enemy)
{
	Skeleton * skeleton = dynamic_cast<Skeleton*>(&(*enemy));
	SkeletonBerserker * skeletonBerserker = dynamic_cast<SkeletonBerserker*>(&(*enemy));
	Dragon * dragon = dynamic_cast<Dragon*>(&(*enemy));

	if (skeleton)
	{
		return Enemy::EnemyType::SKELETON;
	}
	else if (skeletonBerserker)
	{
		return Enemy::EnemyType::SKELETON_BERSERKER;
	}
	else if (dragon)
	{
		return Enemy::EnemyType::DRAGON;
	}

	return (int)Others::RESET;
}



