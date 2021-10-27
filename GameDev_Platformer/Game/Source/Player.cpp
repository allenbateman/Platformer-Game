#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "Render.h"
#include "Player.h"
#include <SDL/include/SDL_scancode.h>

ModulePlayer::ModulePlayer() : Module()
{
	name.Create("player");
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
	pState = IDLE;
	//p->player = app->physics->CreateRectangle(20, 300, 20, 40, b2_dynamicBody);
	p->player = app->physics->CreateCircle(20, 300, 20,b2_dynamicBody);
	p->player->body->SetFixedRotation(true);
	//Idle anim
	p->idlePlayerAnim.PushBack({ 262, 11, 16, 21 });
	p->idlePlayerAnim.PushBack({ 294, 11, 16, 21 });
	p->idlePlayerAnim.PushBack({ 327, 11, 16, 21 });
	p->idlePlayerAnim.loop = false;
	p->idlePlayerAnim.mustFlip = false;
	p->idlePlayerAnim.speed = 0.02f;
	//Walking anim
	p->walkingPlayerAnim.PushBack({ 390, 11, 16, 21 });
	p->walkingPlayerAnim.PushBack({ 454, 11, 16, 21 });
	p->walkingPlayerAnim.loop = true;
	p->walkingPlayerAnim.mustFlip = false;
	p->walkingPlayerAnim.speed = 0.06f;
	//Death anim
	p->jumpingPlayerAnim.PushBack({ 390, 11, 16, 21 });
	p->jumpingPlayerAnim.PushBack({ 422, 11, 16, 21 });
	p->jumpingPlayerAnim.PushBack({ 454, 11, 16, 21 });
	p->jumpingPlayerAnim.PushBack({ 486, 11, 16, 21 });
	p->jumpingPlayerAnim.loop = true;
	p->jumpingPlayerAnim.speed = 0.06f;

	playerTexture= app->tex->Load("Assets/Spritesx16/characters.png");


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	return true;
}

bool ModulePlayer::LoadState(pugi::xml_node&)
{
	bool ret = true;
	return ret;
}

bool ModulePlayer::SaveState(pugi::xml_node&) const
{
	bool ret = true;
	return ret;
}

// Update: draw background
bool ModulePlayer::Update(float dt)
{
	switch (pState)
	{
	case IDLE:
		currentAnim = &p->idlePlayerAnim;
		break;

	case WALK:
		currentAnim = &p->walkingPlayerAnim;
		break;

	case JUMP:
		currentAnim = &p->jumpingPlayerAnim;
		break;
	}

	app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(p->player->body->GetPosition().x - 9), 
				 METERS_TO_PIXELS(p->player->body->GetPosition().y), &(currentAnim->GetCurrentFrame()), 1.0f);

	bool ret = true;
	//Player movement
	maxSpeedX = 0.6;
	minSpeedX = -0.6;
	//Right
	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (p->player->body->GetLinearVelocity().x <= maxSpeedX))
	{
		p->player->body->SetLinearVelocity({ 0.6, p->player->body->GetLinearVelocity().y });
		pState = WALK;
		p->walkingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
		p->IsDirectionRight = true;
	}
	//Left
	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (p->player->body->GetLinearVelocity().x >= minSpeedX))
	{
		p->player->body->SetLinearVelocity({ -0.6, p->player->body->GetLinearVelocity().y });
		pState = WALK;
		p->walkingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
		p->IsDirectionRight = false;
	}
	//Jump
	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && (p->player->body->GetLinearVelocity().y == 0))
	{
		p->player->body->ApplyLinearImpulse({ 0, -1.6f }, { 0, 0 }, true);
		pState = JUMP;
		p->jumpingPlayerAnim.Update();
		p->idlePlayerAnim.Reset();
		p->walkingPlayerAnim.Reset();
	}	
	////DoubleJump
	//if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) && (p->player->body->GetLinearVelocity().y < 0))
	//{
	//	p->player->body->ApplyLinearImpulse({ 0, -1.1f }, { 0, 0 }, true);
	//}
	if (p->player->body->GetLinearVelocity().x == 0 && p->player->body->GetLinearVelocity().y == 0)
	{
		pState = IDLE;
		p->idlePlayerAnim.Update();
		p->walkingPlayerAnim.Reset();
	}



	return ret;
}