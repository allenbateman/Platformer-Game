#include "QuestManager.h"

QuestManager::QuestManager(bool isActive) : Module(isActive)
{
}

QuestManager::~QuestManager()
{
}

bool QuestManager::Awake(pugi::xml_node&)
{
	return false;
}


//Activate Quest

//Cancel Quest

//Complete Quest

//Finish Quest

//Add item

void QuestManager::ActivateQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::AVAILABLE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data.progress = Quest::ACTIVE;
		}

		currentQuest = currentQuest->next;
	}
}

//Get available quest 
bool QuestManager::GetAvailableQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::AVAILABLE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}

//Get active quest
bool QuestManager::GetActiveQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::ACTIVE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}

//Get complete quest but not Done (get rewards etc)
bool QuestManager::GetCompletedQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::COMPLETE)
			return true;

		currentQuest = currentQuest->next;
	}
	return false;
}
