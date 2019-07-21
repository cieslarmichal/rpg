#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Create.h"
#include <cmath>
#include "Constants.h"

using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, std::unique_ptr<StatusBar>>>;

class Shoot
{
public:
	Shoot() = delete;
	static void shootEnemy(std::unique_ptr<Wrapper>& player, vectorOfCharacters & enemies, std::vector<std::unique_ptr<Wrapper>> & projectiles);
	static int findTargetEnemy(vectorOfCharacters & enemies);
};
