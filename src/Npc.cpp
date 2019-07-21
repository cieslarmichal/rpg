#include "Npc.h"


Npc::Npc(std::string name, std::string dialoguePathFile) :Character(name, 100, 1, 1, 100, 2), dialogues(dialoguePathFile)
{
	currentDialogue = "";
}

Npc::~Npc()
{
}

std::string Npc::talk()
{
	if (talking && dialogueTimer.getElapsedSeconds() > (float)1.5 && dialogues.isNextDialogue())
	{
		dialogueTimer.reset();
		dialogueCounter++;
		if (dialogueCounter % 2 == 0)
		{
			currentDialogue = dialogues.getCurrentDialogue();
		}
		else
		{
			currentDialogue = "";
		}
	}

	if(!dialogues.isNextDialogue() && dialogueTimer.getElapsedSeconds()>(float)1.5)
	{
		dialogueTimer.reset();
		talking = false;
		currentDialogue = "";
	}

	return currentDialogue;
}

bool Npc::startTalking(int actionKey)
{
	if (actionKey == (int)InputKeys::E)
	{
		talking = true;
		return true;
	}
	return false;
}

void Npc::setTalking(bool inp)
{
	if (inp == false)
	{
		dialogues.setCurrentDialogueIndex(0);
	}

	talking = inp;
}

bool Npc::isThereNextDialogue() const
{
	return dialogues.isNextDialogue();
}

bool Npc::isTalking() const
{
	return talking;
}

Dialogues & Npc::getDialogues()
{
	return dialogues;
}

