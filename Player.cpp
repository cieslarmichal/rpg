#include "Player.h"



Player::Player(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed)
	: Character(name, hp, attackDamage, attackSpeed, 0, 0, movementSpeed)
{
	level = distanceSkill = meleeSkill = 1;
	distanceHits = meleeHits = 0;
	setMarked(true);
}

Player::~Player()
{
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
