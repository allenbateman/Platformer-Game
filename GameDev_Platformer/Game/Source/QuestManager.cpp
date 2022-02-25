#include "QuestManager.h"

QuestManager::QuestManager(bool isActive) : Module(isActive)
{
}

QuestManager::~QuestManager()
{
}

bool QuestManager::Awake(pugi::xml_node&)
{
	return true;
}

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

void QuestManager::CanelQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::ACTIVE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data.progress = Quest::AVAILABLE;
		}

		currentQuest = currentQuest->next;
	}
}

void QuestManager::CompleteQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::ACTIVE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data.progress = Quest::COMPLETE;
		}

		currentQuest = currentQuest->next;
	}
}

void QuestManager::FinishQuest(int questID)
{
	ListItem<Quest>* currentQuest = questList->start;
	while (currentQuest != NULL)
	{

		if (currentQuest->data.id == questID && currentQuest->data.progress == Quest::COMPLETE)
		{
			currentQuestList->add(currentQuest->data);
			currentQuest->data.progress = Quest::DONE;
		}

		currentQuest = currentQuest->next;
	}
}

void QuestManager::AddItem()
{
}

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
