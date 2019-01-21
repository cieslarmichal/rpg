#pragma once
#include "Wrapper.h"
#include "StatusBar.h"
#include "Constants.h"

using vectorOfCharacters = std::vector<std::pair<std::unique_ptr<Wrapper>, StatusBar>>;

class Mark
{
public:
	Mark() = delete;
	static void markTarget(int key, std::unique_ptr<Wrapper> & player, vectorOfCharacters & enemies, sf::RenderWindow & window);
};
