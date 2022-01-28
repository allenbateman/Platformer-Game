#ifndef __LEVELMANAGEMENT_H__
#define __LEVELMANAGEMENT_H__
#include "Module.h"


#include "App.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Intro.h"
#include "StartMenu.h"
#include "GameOver.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Input.h"


#define MAX_SIZE 28
class LevelManagement : public Module
{
public:
	LevelManagement(bool isActive);
	~LevelManagement();
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;
	void NextLevel();
	void ReturnToMainMenu();
	void ReturnToLevelSelection();
	void RestartLevel();
	void LoadLevel();

	enum GameState {
		NONE = 0,
		INTRO = 1,
		START = 2,
		SCENE1 = 4,
		SCENE2 = 5,
		GAME_OVER = 6
	};
	GameState gameState;
	Module* currentScene = nullptr;
	Module* currentLevel = nullptr;
	int gemCount = 0;
	int frameCounter = 0;
	int delayTime = 100;
	int levelsPassed = 0;

	//to track current keys
	int KeysToTake = 0;

};
#endif // __LEVELMANAGEMENT_H__
