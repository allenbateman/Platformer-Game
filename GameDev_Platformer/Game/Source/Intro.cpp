#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Intro.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

Intro::Intro(bool isActive) : Module(isActive)
{
	name.Create("scene");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{
	img = app->tex->Load("Assets/Spritesx16/intro.png");
	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;

	app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Intro::CleanUp()
{
	LOG("Freeing scene intro");

	return true;
}