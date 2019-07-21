#pragma once
#include "Wrapper.h"
#include "Mission.h"
#include "HUD.h"
#include "Text.h"

using character = std::unique_ptr<Wrapper>;
using texts = std::vector<std::unique_ptr<Text>>;

class Interaction
{
public:
	Interaction() = delete;
	static void playerWithNpc(character & player, character & npc, texts & messages, int actionKey);
private:
	static void action(character & player, character & npc, texts & messages);
	static void initializeAction(character & player, character & npc, texts & messages, int actionKey);
	static double absoluteDistance(sf::Vector2f position1, sf::Vector2f position2);
};

