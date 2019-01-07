#include "Player.h"



Player::Player(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed)
	: Character(name, hp, attackDamage, attackSpeed, 0, 0, movementSpeed)
{
	level = distanceSkill = meleeSkill = 1;
	distanceHits = meleeHits = 0;
	setMarked(true);
}

//setters

void Player::levelUp()
{
	level++;
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

//getters

int Player::getLevel() const
{
	return level;
}

int Player::getDistanceLevel() const
{
	return distanceSkill;
}

int Player::getMeleeLevel() const
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

void Player::useItem(int actionKey)
{
	if (actionKey == (int)InputKeys::Q && useItemTimer.getElapsedSeconds() > (float)1)
	{
		if (inventory.isItemAvailable(inventory.getMarkedItemIndex()))
		{
			useItemTimer.reset();
			Item tempItem = inventory.getMarkedItem();
			//item effects handling
			if (tempItem.getType() == Item::Type::HEALTH_POTION)
			{
				setCurrentHp(getCurrentHp() + tempItem.getAmountRestoringHp());
			}
		}
	}
}
