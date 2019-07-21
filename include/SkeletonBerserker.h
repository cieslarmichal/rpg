#pragma once
#include "Skeleton.h"

class SkeletonBerserker :public Skeleton
{
public:
	SkeletonBerserker(std::string name, int hp, int attackDamage, int attackSpeed, float movementSpeed, int experience, float lootChance);
};

