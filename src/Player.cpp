#include "Player.h"



Player::Player(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed)
	: Character(name, hp, attackDamage, attackSpeed, 0, movementSpeed)
{
	level = distanceSkill = meleeSkill = 1;
	coins = 0;
	distanceHits = meleeHits = 0;
	weapon = (int)Weapons::MELEE;
	setMarked(true);
}

void Player::levelUp()
{
	level++;
	setCurrentHp(getMaxHp());
	setBaseAttackDamage(getBaseAttackDamage() + 1);
}

void Player::setCoins(int inp)
{
	coins = inp;
}

void Player::distanceSkillUp()
{
	distanceSkill++;
}

void Player::meleeSkillUp()
{
	meleeSkill++;
}


void Player::distanceHitsUp()
{
	distanceHits++;
}

void Player::meleeHitsUp()
{
	meleeHits++;
}

void Player::setWeapon(bool inp)
{
	weapon = inp;
}

int Player::getLevel() const
{
	return level;
}

int Player::getCoins() const
{
	return coins;
}

int Player::getDistanceSkill() const
{
	return distanceSkill;
}

int Player::getMeleeSkill() const
{
	return meleeSkill;
}


int Player::getDistanceHits() const
{
	return distanceHits;
}

int Player::getMeleeHits() const
{
	return meleeHits;
}

bool Player::getWeapon() const
{
	return weapon;
}

Inventory & Player::getInventory()
{
	return inventory;
}

void Player::pickUpItem(Item & item, int actionKey)
{
	if (actionKey == (int)InputKeys::E && pickItemTimer.getElapsedSeconds() > (float)0.2)
	{
		pickItemTimer.reset();

		Missions::updateCollected(item.getType());

		if (item.getType() == Item::Type::COIN)
		{
			setCoins(getCoins() + item.getSellValue());
			item.setDestroyed(true);
		}
		else
		{
			if (inventory.addItem(item))
			{
				item.setDestroyed(true);
			}
		}
	}
}

void Player::useItem(int actionKey)
{
	if (actionKey == (int)InputKeys::Q && useItemTimer.getElapsedSeconds() > (float)0.4)
	{
		if (inventory.isItemAvailable(inventory.getChosenItemIndex()))
		{
			useItemTimer.reset();

			Item & chosenItem = inventory.getChosenItem();

			if (chosenItem.getType() == Item::Type::HEALTH_POTION || chosenItem.getType() == Item::Type::FOOD)
			{
				setCurrentHp(getCurrentHp() + chosenItem.getRestoringHp());
				inventory.destroyItem();
			}
			else
			{
				inventory.equipItem(chosenItem);
				updateEqEffects();
			}
		}
	}
}

void Player::changeChosenItem(int actionKey)
{
	if (actionKey == (int)InputKeys::TAB && useItemTimer.getElapsedSeconds() > 0.2)
	{
		useItemTimer.reset();
		inventory.changeChosenItem();
	}
}

void Player::dropItem(int actionKey)
{
	if (actionKey == (int)InputKeys::X && useItemTimer.getElapsedSeconds() > 0.5)
	{
		useItemTimer.reset();
		inventory.dropItem();
	}
}

void Player::updateEqEffects()
{
	setDefense(getBaseDefense());

	for (auto & eqItem : inventory.getEquipment())
	{
		switch (eqItem.getType())
		{
		case Item::Type::MELEE_WEAPON:
			weapon = (int)Weapons::MELEE;
			setAttackDamage(getBaseAttackDamage() + eqItem.getDamage());
			break;
		case Item::Type::DISTANCE_WEAPON:
			weapon = (int)Weapons::DISTANCE;
			setAttackDamage(getBaseAttackDamage() + eqItem.getDamage());
			break;
		case Item::Type::HELMET:
		case Item::Type::ARMOR:
		case Item::Type::BOOTS:
		case Item::Type::SHIELD:
		case Item::Type::NECKLACE:
		case Item::Type::RING:
			setDefense(getDefense() + eqItem.getArmor());
			break;
		}
	}
}

