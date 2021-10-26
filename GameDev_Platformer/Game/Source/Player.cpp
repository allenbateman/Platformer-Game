#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "Player.h"
#include "Textures.h"
#include "Render.h"
#include <SDL/include/SDL_scancode.h>

ModulePlayer::ModulePlayer() : Module()
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	//Initializing player struct data
	p = new Player1;
	p->player = app->physics->CreateRectangle(20, 300, 20, 40, b2_dynamicBody);
	//Idle anim
	p->idlePlayerAnim.PushBack({ 0, 0, 39, 38 });
	//Walking anim
	p->idlePlayerAnim.PushBack({ 0, 0, 39, 38 });
	//Death anim
	p->idlePlayerAnim.PushBack({ 0, 0, 39, 38 });

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	return true;
}

// Update: draw background
bool ModulePlayer::Update()
{
	return UPDATE_CONTINUE;

	//Player movement

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		p->player->body->ApplyLinearImpulse({ 1 , 0 }, { -1, 0 }, true);
	}

	return true;
}