#include "Interaction.h"



void Interaction::playerWithNpc(character & player, character & npc, texts & messages, int actionKey)
{
	double distance = absoluteDistance(player->rect->getPosition(), npc->rect->getPosition());

	if (distance < 100)
	{
		if (!npc->rect->npc->isTalking())
		{
			initializeAction(player, npc, messages, actionKey);
		}
		else
		{
			action(player, npc, messages);
		}
	}
	else
	{
		npc->rect->npc->setTalking(false);
	}
}

void Interaction::initializeAction(character & player, character & npc, texts & messages, int actionKey)
{
	npc->timing.reset();
	if (!npc->rect->npc->startTalking(actionKey))
	{
		Create::createNpcMessage("Press E to talk", npc->rect->getPosition(), messages);
	}
}

void Interaction::action(character & player, character & npc, texts & messages)
{
	if (Missions::isCurrentMissionCompleted())
	{
		std::string npcMessage = "Great job, here is your award.";
		Create::createNpcMessage(npcMessage, npc->rect->getPosition(), messages, true);

		if (npc->timing.getElapsedSeconds() > (float)1.5)
		{
			npc->timing.reset();
			npc->rect->npc->setTalking(false);

			Item awardItem(Missions::getCurrentAwardItemId());
			player->rect->player->getInventory().addItem(awardItem);

			LevelManager::gainExperience(player->rect->player, Missions::getCurrentAwardExperience());

			HUD::removeMissionInfo();
			Missions::nextMission();
			npc->rect->npc->getDialogues().nextDialogueLine();
		}
	}
	else
	{
		if (!npc->rect->npc->isThereNextDialogue())
		{
			Missions::startMission();
			HUD::addMissionInfo();
		}
		if (npc->timing.getElapsedSeconds() > (float)1.5)
		{
			npc->timing.reset();
			std::string npcMessage = npc->rect->npc->talk();
			Create::createNpcMessage(npcMessage, npc->rect->getPosition(), messages, true);
		}
	}
}

double Interaction::absoluteDistance(sf::Vector2f position1, sf::Vector2f position2)
{
	int diffX = (int)((int)position2.x - (int)position1.x);
	int diffY = (int)((int)position2.y - (int)position1.y);

	return std::sqrt(diffX*diffX + diffY * diffY);
}

