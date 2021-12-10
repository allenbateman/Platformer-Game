#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Player.h"
#include "Map.h"
#include <SDL/include/SDL_scancode.h>

ModulePlayer::ModulePlayer(bool isActive) : Module(isActive)
{
	name.Create("player");
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Awake()
{

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	//Initializing player struct data
	if (physBody == NULL)
	{
		state = IDLE;

		playerTexture = app->tex->Load("Assets/Spritesx16/characters.png");
		//Idle anim
		idlePlayerAnim.PushBack({ 262, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 294, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 327, 43, 16, 21 });
		idlePlayerAnim.loop = false;
		idlePlayerAnim.mustFlip = true;
		idlePlayerAnim.speed = 0.04f;
		//Walking anim
		walkingPlayerAnim.PushBack({ 390, 43, 16, 21 });
		walkingPlayerAnim.PushBack({ 454, 43, 16, 21 });
		walkingPlayerAnim.loop = true;
		walkingPlayerAnim.mustFlip = true;
		walkingPlayerAnim.speed = 0.1f;
		//Jump anim
		jumpingPlayerAnim.PushBack({ 390, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 422, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 454, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 486, 47, 16, 16 });
		jumpingPlayerAnim.loop = false;
		jumpingPlayerAnim.mustFlip = true;
		jumpingPlayerAnim.speed = 0.1f;
		//Death anim
		deathPlayerAnim.PushBack({ 0, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 19, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 38, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 57, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 76, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 95, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 114, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 133, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 152, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.loop = false;
		deathPlayerAnim.mustFlip = true;
		deathPlayerAnim.speed = 0.1f;
		//Melee attack anim
		meleePlayerAnim.PushBack({ 0, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 0, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 0, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 0, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 28, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 56, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 84, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 112, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 140, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 168, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 196, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 224, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 252, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 280, 0, 28, 20 });
		meleePlayerAnim.PushBack({ 308, 0, 28, 20 });
		meleePlayerAnim.loop = false;
		meleePlayerAnim.mustFlip = true;
		meleePlayerAnim.speed = 0.5f;

		currentAnim = &idlePlayerAnim;
		state = IDLE;

		position = { 0, 300 };
		physBody = app->physics->CreateCircle(position.x, position.y, 7, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->entities.add(physBody);


		//sensors
		leftSensor = app->physics->CreateRectangleSensor(position.x-7, position.y-5,7,10, b2_kinematicBody, { 255,165,0,255 });
		rightSensor = app->physics->CreateRectangleSensor(position.x, position.y-5,7,10, b2_kinematicBody, { 255,165,0,255 });
		topSensor = app->physics->CreateRectangleSensor(position.x-7, position.y,7,5, b2_kinematicBody, { 255,165,0,255 });
		botSensor = app->physics->CreateRectangleSensor(position.x-7, position.y+5,7,5, b2_kinematicBody, { 255,165,0,255 });
		app->physics->entities.add(leftSensor);
		app->physics->entities.add(rightSensor);
		app->physics->entities.add(topSensor);
		app->physics->entities.add(botSensor);

		lives = 1;
	}
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	state = IDLE;
	delete physBody;
	currentAnim = nullptr;
	return true;
}

void ModulePlayer::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);

	physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}

void ModulePlayer::Spawn(iPoint pos)
{
	Enable();
	SetPosition(pos);
	state = IDLE;
}

void ModulePlayer::Disable()
{
	active = false;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	b2Vec2 position; 
	position.x = data.child("player").attribute("x").as_int();
	position.y = data.child("player").attribute("y").as_int();
	state = static_cast<PlayerState>(data.child("player").attribute("state").as_int());

	physBody->body->SetTransform(position, physBody->body->GetAngle());
	return ret;
}

bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node player = data.append_child("player");
	player.append_attribute("x") = physBody->body->GetPosition().x;
	player.append_attribute("y") = physBody->body->GetPosition().y;
	player.append_attribute("state") = state;
	return ret;
}

bool ModulePlayer::PreUpdate()
{
	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;
	float normal1, normal2,rayLength;
	rayLength = 25;
	physBody->RayCast(position.x, position.y, position.x + rayLength, position.y,normal1,normal2);
	//Right
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && state != ATTACK && state != DEAD)
	{
		physBody->body->SetLinearVelocity({ speed.x, physBody->body->GetLinearVelocity().y });
		state = MOVE_RIGHT;

	}else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && state != ATTACK && state != DEAD)
	{
		physBody->body->SetLinearVelocity({ -speed.x, physBody->body->GetLinearVelocity().y });
		state = MOVE_LEFT;

	}
	else if(onGround && state != ATTACK && state != DEAD){
		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });
		state = IDLE;
	}
	//Jump
	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && onGround && state != ATTACK && state != DEAD)
	{
		physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(),true);
		doubleJump = true;
		onGround = false;
		state = JUMP;


	}else//DoubleJump
	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && doubleJump && state != ATTACK && state != DEAD)
	{
		physBody->body->ApplyLinearImpulse( b2Vec2(0,-jumpForce) , physBody->body->GetWorldCenter(), true);
		doubleJump = false;
		state = DOUBLE_JUMP;
	}

	//Player melee attack
	int dir = 0;
	if (direction == 1) dir = -25;
	else dir = 20;

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && state != ATTACK && state != DEAD && onGround)
	{
		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });

		PhysBody* melee = app->physics->CreateRectangleSensor(METERS_TO_PIXELS(physBody->body->GetPosition().x) + dir,
					METERS_TO_PIXELS(physBody->body->GetPosition().y), 18, 20, b2_staticBody);
		melee->color = { 120, 50, 100, 155 };
		melee->listener = app->levelManagement->currentScene;
		melee->type = Collider_Type::PLAYER_ATTACK;
		app->physics->groundColliders.add(melee);

		state = ATTACK;
	}

	return true;
}

// Update: draw background
bool ModulePlayer::Update(float dt)
{
	bool ret = true;
	b2Vec2 vel = physBody->body->GetLinearVelocity();
	float desiredVel = 0;

	b2Vec2 pos;
	pos.x = leftSensor->body->GetPosition().x + position.x;
	pos.y = leftSensor->body->GetPosition().y + position.x;
	leftSensor->body->SetTransform(pos, physBody->body->GetAngle());

	if (lives <= 0) state = DEAD;

	switch (state)
	{
	case IDLE:
		idlePlayerAnim.Update();
		walkingPlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case JUMP:
		jumpingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		walkingPlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case MOVE_LEFT:
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		meleePlayerAnim.Reset();
		direction = SDL_FLIP_HORIZONTAL;
		break;
	case MOVE_RIGHT:
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		meleePlayerAnim.Reset();
		direction = SDL_FLIP_NONE;
		break;
	case ATTACK:
		meleePlayerAnim.Update();
		idlePlayerAnim.Reset();
		break;
	}
	currentAnim->Update();

	return ret;

}

bool ModulePlayer::PostUpdate()
{
	switch (state)
	{
	case IDLE:
		currentAnim = &idlePlayerAnim;
		break;
	case MOVE_LEFT:
		currentAnim = &walkingPlayerAnim;
		break;
	case MOVE_RIGHT:
		currentAnim = &walkingPlayerAnim;
		break;
	case JUMP:
		currentAnim = &jumpingPlayerAnim;
		break;
	case ATTACK:
		currentAnim = &meleePlayerAnim;
		break;
	case DEAD:
		currentAnim = &deathPlayerAnim;
		break;
	}

	if (playerTexture != NULL)
	{
		if (state == ATTACK && direction == 1)
		{
			app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 36), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else if (state == DEAD)
		{
			if (direction == 1)
			{
				app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x) - 19, METERS_TO_PIXELS(physBody->body->GetPosition().y) - 72,
					&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			}
			else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 17), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 72,
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	}
		

	if (state == ATTACK && frameCounter < 25)
	{
		frameCounter++;
	}
	else if (frameCounter >= 25)
	{
		state = IDLE;
		frameCounter = 0;
	}

	return true;
}
