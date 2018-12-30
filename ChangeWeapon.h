#pragma once
#include "Wrapper.h"
#include "Directions.h"

class ChangeWeapon
{
public:
	ChangeWeapon() = delete;
	static void changeWeapon(int key, std::unique_ptr < Wrapper> & player);
private:
	static TimeHandler minChangingTime;
};

