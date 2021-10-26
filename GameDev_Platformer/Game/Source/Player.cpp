#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "Player.h"
#include <SDL/include/SDL_scancode.h>

ModulePlayer::ModulePlayer() : Module()
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	speedX = 0.8f;
	speedY = 0.8f;
	//Initializing player struct data
	p = new Player1;
	p->player = app->physics->CreateRectangle(20, 300, 20, 40, b2_dynamicBody);
	p->player->body->SetFixedRotation(true);
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
bool ModulePlayer::Update(float dt)
{
	bool ret = true;
	//Player movement
	//Right
	//if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//{
	//	p->player->body->SetLinearVelocity({ speed, 0 });
	//}
	//if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//{
	//	p->player->body->SetLinearVelocity({ -speed, 0 });
	//}
	//if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	p->player->body->ApplyLinearImpulse({ 0, -speed - 0.3f}, { 0, 0 }, true);
	//}

	return ret;
}