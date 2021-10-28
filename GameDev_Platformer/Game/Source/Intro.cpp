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
	LOG("Freeing scene");

	return true;
}