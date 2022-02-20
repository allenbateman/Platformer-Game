#include "Module.h"
#include "List.h"
#include "Quest.h"
class QuestManager : public Module {

public:
	QuestManager(bool isActive);
	~QuestManager();

	bool Awake(pugi::xml_node&);
public: 

	static QuestManager questManager;

	List<Quest>* questList = new List<Quest>();
	List<Quest>* currentQuestList = new List<Quest>();


	void ActivateQuest(int questID);


	bool GetAvailableQuest(int questID);
	bool GetActiveQuest(int questID);
	bool GetCompletedQuest(int questID);

};