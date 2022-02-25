#pragma once
#include"SString.h"

class Quest
{

public:
	enum QuestProgress {  AVAILABLE, NOT_AVAILABLE, ACTIVE, COMPLETE, DONE }; //States a quest can have


	int id;							//Quest identification
	QuestProgress progress;			//State of the current quest 
	int nextQuest;					//next quest, if there is any (chain quest)

	SString questObjective;			//Posible quest objectives
	SString questReward;			//Posible quest rewards
	int amount;

	SString title;					//Title for the quest
	SString questDescription;		//What player has to know about the quest
	SString hint;					//Small hit for the player ( more specifically)
	SString questCongratulations;	//contgrats the player for completing the quest

};

