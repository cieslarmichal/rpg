#include "Dialogues.h"



Dialogues::Dialogues(std::string filePath)
{
	loadDialogueLines(filePath);
	currentDialogueIndex = 0;
	currentAmountOfDialogues = (int)listOfDialogueLines[currentDialogueIndex].size();
	currentDialogueLineIndex = 0;
	amountDialogueLineIndex = (int)listOfDialogueLines.size();
}

std::string Dialogues::getCurrentDialogue()
{
	std::string nextDialogue = "";

	int dialogueIndex = 0;

	for (auto & dialogue : listOfDialogueLines[currentDialogueLineIndex])
	{
		if (dialogueIndex == currentDialogueIndex)
		{
			nextDialogue = dialogue;
			currentDialogueIndex++;
			break;
		}
		dialogueIndex++;
	}
	return nextDialogue;
}

bool Dialogues::isNextDialogue() const
{
	return (!(currentDialogueIndex >= currentAmountOfDialogues));
}

void Dialogues::setCurrentDialogueIndex(int inp)
{
	currentDialogueIndex = inp;
}

void Dialogues::nextDialogueLine()
{
	if (currentDialogueLineIndex < (int)listOfDialogueLines.size())
	{
		currentDialogueLineIndex++;
		currentDialogueIndex = 0;
		currentAmountOfDialogues = (int)listOfDialogueLines[currentDialogueLineIndex].size();
	}
}

void Dialogues::loadDialogueLines(std::string filePath)
{
	std::vector<std::string> lines = File::getLines(filePath);

	std::vector<std::string> dialogueLine;
	int lineCounter = 0;

	for (auto & line : lines)
	{
		std::string lineLowLetters = line;
		std::transform(lineLowLetters.begin(), lineLowLetters.end(), lineLowLetters.begin(), ::tolower);
		std::size_t keyWord = lineLowLetters.find("dialogue");

		if (keyWord == std::string::npos)
		{
			if (line != "")
			{
				dialogueLine.push_back(line);
			}
		}
		else if (keyWord != std::string::npos)
		{
			if ((int)dialogueLine.size() >= 1)
			{
				listOfDialogueLines.push_back(dialogueLine);
				dialogueLine.clear();
			}
		}
		lineCounter++;
	}
}

