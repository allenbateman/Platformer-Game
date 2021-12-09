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
	gameState = GameState::INTRO;
	currentScene = (Module*)app->intro;
	return true;
}

bool LevelManagement::PreUpdate()
{
	switch (gameState)
	{
	case INTRO:
		//cout << "Intro\n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	case START:
		//cout << "Start \n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE1;
		}
		if ((app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE1;
		}
		if ((app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		break;
	case SCENE1:
		//cout << "Scene 1 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && currentScene->active == true)
		{
			RestartLevel();
		}
		break;
	case SCENE2:
		//cout << "Scene 2 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = GAME_OVER;
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && currentScene->active == true)
		{
			RestartLevel();
		}
		break;
	case GAME_OVER:
		//cout << "GAME OVER \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	default:
		break;
	}
	return true;
}

bool LevelManagement::Update(float dt)
{


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
			if (app->fade->Fade(currentScene, (Module*)app->start, 30))
			{
				currentScene = (Module*)app->start;
				currentScene->active = true;
				LOG("START");
			}
		}
		break;
	case SCENE1:
		if (currentScene != (Module*)app->scene1) {

			if (app->fade->Fade(currentScene, (Module*)app->scene1, 30))
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

			if (app->fade->Fade(currentScene, (Module*)app->scene2, 30))
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
			if (app->fade->Fade(currentScene, (Module*)app->gameOver, 30))
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


void LevelManagement::NextLevel()
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
	if (app->player->state == PlayerState::DEAD)
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