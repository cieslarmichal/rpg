#pragma once
#include <vector>
#include <string>
#include "File.h"
#include <algorithm>

class Dialogues
{
public:
	Dialogues(std::string filePath);
	std::string getCurrentDialogue();
	bool isNextDialogue() const;
	void setCurrentDialogueIndex(int);
	void nextDialogueLine();
private:
	void loadDialogueLines(std::string filePath);
	std::vector<std::vector<std::string>> listOfDialogueLines;
	int currentDialogueLineIndex, amountDialogueLineIndex;
	int currentDialogueIndex, currentAmountOfDialogues;
};

