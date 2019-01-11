#pragma once
#include "Wrapper.h"
#include "Text.h"
#include "Create.h"
#include "LevelManager.h"
#include "StatusBar.h"
#include "Create.h"

class HUD
{
public:
	HUD();
	void update(std::unique_ptr<Wrapper> & player,sf::Vector2u windowSize);
public:
	StatusBar hp, lvl;
	std::vector<std::unique_ptr<Text>> informations;
	std::vector<std::unique_ptr<Rect>> inventorySlots;
	std::vector<std::unique_ptr<Wrapper>> inventory;
	std::vector<std::unique_ptr<Wrapper>> equipment;
private:
	void updateInformations(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	void updateSlots(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	void updateInventorySlots(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	void updateEquipmentSlots(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	void updateInventory(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	void updateEquipment(std::unique_ptr<Wrapper> & player, sf::Vector2u windowSize);
	sf::Vector2i calculateEqPosition(int itemType);
	sf::Vector2i equipmentPositions[7];
private:
	void initializeText();
	void initializeSlots();
	void initializeEqPositions();
};

