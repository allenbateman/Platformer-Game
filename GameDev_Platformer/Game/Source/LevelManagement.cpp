#include "LevelManagement.h"
#include "Player.h"
#include <string>
#include <iostream>

LevelManagement::LevelManagement() : Module()
{

}

LevelManagement::~LevelManagement()
{
}

bool LevelManagement::Start()
{
	LOG("Loading LevelManager....");
	gameState = INTRO;
	currentScene = (Module*)app->intro;
	return true;
}

bool LevelManagement::Update(float dt)
{
	switch (gameState)
	{
	case INTRO:
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{

			gameState = INTRO;
		}
		break;
	case START:
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	case SCENE1:
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = SCENE1;
		}
		break;
	case SCENE2:
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		break;
	case GAME_OVER:
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = GAME_OVER;
		}
		break;
	default:
		break;
	}

	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr) {
			LOG("Loading Intro Screen");
			currentScene = (Module*)app->intro;
		}
		break;
	case START:
		if (currentScene != (Module*)app->start) {
			if (app->fade->Fade(currentScene, (Module*)app->intro, 45))
			{
				LOG("Loading Start Screen");
				currentScene = (Module*)app->start;
			}
		}
		break;
	case SCENE1:
		if (currentScene != (Module*)app->scene1) {

			if (app->fade->Fade(currentScene, (Module*)app->start, 45))
			{
				LOG("Loading Level 1");
				currentScene = (Module*)app->scene1;
			}
		}
		break;
	case SCENE2:

		if (currentScene != (Module*)app->scene2)
		{
			//Load level

			if (app->fade->Fade(currentScene, (Module*)app->scene1, 45))
			{
				LOG("Loading Level 2");
				currentScene = (Module*)app->scene2;
			}
		}
		break;
	case GAME_OVER:

		if (currentScene != (Module*)app->gameOver) {
			//Load game over
			if (app->fade->Fade(currentScene, (Module*)app->gameOver, 45))
			{
				LOG("Loading Level 2");
				currentScene = (Module*)app->gameOver;
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
	LOG("RETURN TO MAIN MENU")
		if (gameState != START)
			gameState = START;
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