#include "LevelManagement.h"
#include "Log.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

LevelManagement::LevelManagement(bool isActive) : Module(isActive)
{

}

LevelManagement::~LevelManagement()
{
}

bool LevelManagement::Start()
{
	gameState = INTRO;
	currentScene = (Module*)app->intro;
	return true;
}

bool LevelManagement::Update(float dt)
{
	switch (gameState)
	{
	case INTRO:
		//cout << (currentScene->active ? "Intro: true" : "Intro: false") << endl;
		cout << "Intro\n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	case START:
		//cout << (currentScene->active ? "Start: true" : "Start: false") << endl;
		cout << "Start \n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE1;
		}
		break;
	case SCENE1:
		//cout << (currentScene->active ? "Scene1: true" : "Scene1: false") << endl;
		cout << "Scene 1 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		break;
	case SCENE2:
		//cout << (currentScene->active ? "Scene2: true" : "Scene2: false") << endl;
		cout << "Scene 2 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = GAME_OVER;
		}
		break;
	case GAME_OVER:
		//cout << (currentScene->active ? "GameOver: true" : "GameOver: false") << endl;
		cout << "GAME OVER \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	default:
		break;
	}

	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr) {
			currentScene = (Module*)app->intro;
			LOG("INTRO");
		}
		break;
	case START:
		if (currentScene != (Module*)app->start) {
			if (app->fade->Fade(currentScene, (Module*)app->intro, 45))
			{
				currentScene = (Module*)app->start;
				currentScene->active = true;
				LOG("START");
			}
		}
		break;
	case SCENE1:
		if (currentScene != (Module*)app->scene1) {

			if (app->fade->Fade(currentScene, (Module*)app->scene1, 45))
			{
				currentScene = (Module*)app->scene1;
				currentScene->Start();
				currentScene->active = true;
				LOG("SCENE 1");
			}
		}
		break;
	case SCENE2:

		if (currentScene != (Module*)app->scene2)
		{
			//Load level

			if (app->fade->Fade(currentScene, (Module*)app->scene2, 45))
			{
				currentScene = (Module*)app->scene2;
				currentScene->active = true;
				LOG("SCENE 2");
			}
		}
		break;
	case GAME_OVER:

		if (currentScene != (Module*)app->gameOver) {
			//Load game over
			if (app->fade->Fade(currentScene, (Module*)app->gameOver, 45))
			{
				currentScene = (Module*)app->gameOver;
				currentScene->active = true;
				LOG("GAME OVER");
			}
		}
		break;
	default:
		break;
	}
	frameCounter++;
	return true;
}


void LevelManagement::PassedLevel()
{
	switch (gameState) {
	case GameState::SCENE1:
		if (levelsPassed < 1) {
			levelsPassed++;
		}
		gameState = SCENE2;
		break;
	case GameState::SCENE2:
		if (levelsPassed < 2) {
			levelsPassed++;
		}
		gameState = START;
		break;
	default:
		break;
	}
}

void LevelManagement::ReturnToMainMenu()
{
	if (gameState != START)
	{
		gameState = START;
	}
}

void LevelManagement::RestartLevel()
{
	if (app->player->DEATH)
	{
		gameState = GAME_OVER;

		app->fade->Fade(currentScene, (Module*)app->gameOver, 60.0f);
	}
	else {
		app->fade->Fade(currentScene, currentScene, 60.0f);
	}
}


bool LevelManagement::CleanUp()
{
	if (currentScene != nullptr)
	{
		currentScene = nullptr;
	}
	return true;
}