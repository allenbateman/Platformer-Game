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
	maxSpeedX = 0;
	minSpeedX = 0;

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
	maxSpeedX = 0.6;
	minSpeedX = -0.6;
	//Right
	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (p->player->body->GetLinearVelocity().x <= maxSpeedX))
	{
		p->player->body->SetLinearVelocity({ 0.6, p->player->body->GetLinearVelocity().y });
	}
	//Left
	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (p->player->body->GetLinearVelocity().x >= minSpeedX))
	{
		p->player->body->SetLinearVelocity({ -0.6, p->player->body->GetLinearVelocity().y });
	}
	//Jump
	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && (p->player->body->GetLinearVelocity().y == 0))
	{
		p->player->body->ApplyLinearImpulse({ 0, -1.1f }, { 0, 0 }, true);
	}
	////DoubleJump
	//if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && (p->player->body->GetLinearVelocity().y > 0))
	//{
	//	p->player->body->ApplyLinearImpulse({ 0, -1.1f }, { 0, 0 }, true);
	//}

	return ret;
}