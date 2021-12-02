#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Player.h"
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
	state = IDLE;

	//Initializing player struct data
	if (physBody == NULL)
	{
		

		playerTexture = app->tex->Load("Assets/Spritesx16/characters.png");
		//Idle anim
		idlePlayerAnim.PushBack({ 262, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 294, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 327, 43, 16, 21 });
		idlePlayerAnim.loop = false;
		idlePlayerAnim.mustFlip = true;
		idlePlayerAnim.speed = 0.2f;
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
		walkingPlayerAnim.mustFlip = true;
		jumpingPlayerAnim.speed = 0.1f;
		//Death anim
		deathPlayerAnim.PushBack({ 262, 43, 16, 21 });
		deathPlayerAnim.loop = false;
		deathPlayerAnim.mustFlip = true;
		deathPlayerAnim.speed = 1.0f;

		currentAnim = &idlePlayerAnim;
		state = IDLE;

		if (physBody == NULL)
		{
			position = { 20, 300 };
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

		}
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

void ModulePlayer::Spawn(fPoint pos)
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
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		physBody->body->SetLinearVelocity({ speed.x, physBody->body->GetLinearVelocity().y });
		state = MOVE_RIGHT;

	}else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		physBody->body->SetLinearVelocity({ -speed.x, physBody->body->GetLinearVelocity().y });
		state = MOVE_LEFT;

	}
	else if(onGround){
		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });
		state = IDLE;
	}
	//Jump
	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)) && onGround)
	{
		physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(),true);
		doubleJump = true;
		onGround = false;
		state = JUMP;


	}else////DoubleJump
	if ((app->input->GetKey(SDL_SCANCODE_UP || (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)) == KEY_DOWN) && doubleJump)
	{
		physBody->body->ApplyLinearImpulse( b2Vec2(0,-jumpForce) , physBody->body->GetWorldCenter(), true);
		doubleJump = false;
		state = DOUBLE_JUMP;
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


	switch (state)
	{
	case IDLE:

		idlePlayerAnim.Update();
		walkingPlayerAnim.Reset();
		break;
	case JUMP:

		jumpingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		walkingPlayerAnim.Reset();
		break;
	case MOVE_LEFT:
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		direction = SDL_FLIP_HORIZONTAL;
		break;
	case MOVE_RIGHT:
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		direction = SDL_FLIP_NONE;
		break;
	case ATTACK:
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
	case DEAD:
		currentAnim = &deathPlayerAnim;
		direction = SDL_FLIP_HORIZONTAL;
		break;
	}

	if (playerTexture != NULL)
		app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	
	return true;
}
