#pragma once
#include"SString.h"

class Quest
{

public:
	enum QuestProgress { ACTIVE, AVAILABLE, NOT_AVAILABLE, COMPLETE, DONE }; //States a quest can have

	SString title;					//Title for the quest
	int id;							//Quest identification
	QuestProgress progress;			//State of the current quest 

	SString questDescription;		//What player has to know about the quest
	SString hint;					//Small hit for the player ( more specifically)
	SString questCongratulations;	//contgrats the player for completing the quest
	int nextQuest;					//next quest, if there is any (chain quest)


	enum QuestObjective
	{
		
	};
	int questObjective;
};

