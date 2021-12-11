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
	img = app->tex->Load("Assets/Spritesx16/GameOver.png");
	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	return true;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;



	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene gameover");
	active = false;
	img = nullptr;
	return true;
}