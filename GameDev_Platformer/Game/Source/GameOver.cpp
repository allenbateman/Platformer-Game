#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameOver.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

GameOver::GameOver(bool isActive) : Module(isActive)
{
	name.Create("game_over");
}

// Destructor
GameOver::~GameOver()
{}

// Called before render is available
bool GameOver::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameOver::Start()
{

	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene");

	return true;
}