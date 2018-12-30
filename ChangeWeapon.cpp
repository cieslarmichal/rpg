#include "ChangeWeapon.h"

TimeHandler ChangeWeapon::minChangingTime;

void ChangeWeapon::changeWeapon(int key, std::unique_ptr < Wrapper> & player)
{
	if (key == (int)InputKeys::R && minChangingTime.getElapsedSeconds() >0.5)
	{
		minChangingTime.reset();

		if (player->rect->character->getWeapon() == (int)Weapons::MELEE)
		{
			player->rect->character->setWeapon((int)Weapons::DISTANCE);
		}
		else
		{
			player->rect->character->setWeapon((int)Weapons::MELEE);
		}
	}
}
