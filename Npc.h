#pragma once
#include "Character.h"
#include "TimeHandler.h"
#include "Dialogues.h"

class Npc :public Character
{
public:
	Npc(std::string name, std::string dialoguePathFile);
	~Npc();
	std::string talk();
	bool startTalking(int actionKey);
	void setTalking(bool);
	bool isThereNextDialogue() const;
	bool isTalking() const;
	Dialogues & getDialogues();
private:
	std::string currentDialogue;
	int dialogueCounter = 0;
	Dialogues dialogues;
	TimeHandler dialogueTimer;
	bool talking = false;
};

