#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Player.h"
#include "Map.h"
#include "Log.h"
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
		meleePlayerAnim.PushBack({ 0, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 0, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 37, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 74, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 111, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 148, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 185, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 222, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 259, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 296, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 333, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 333, 0, 37, 28 });
		meleePlayerAnim.loop = false;
		meleePlayerAnim.mustFlip = true;
		meleePlayerAnim.speed = 0.3f;

		currentAnim = &idlePlayerAnim;
		state = IDLE;

		position = { 20, 300 };
		physBody = app->physics->CreateCircle(position.x, position.y, colliderRadius, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->entities.add(physBody);

		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;
		lastPosition = position;

		//sensors
		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;
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
	else if (physBody->body == NULL) {

		physBody = app->physics->CreateCircle(position.x, position.y, colliderRadius, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->entities.add(physBody);

		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;
		lastPosition = position;
	}
	return true;
}



bool ModulePlayer::PreUpdate()
{
	if (LoadRequest)
	{
		iPoint p;
		p.x = position.x;
		p.y = position.y;
		SetPosition(p);
		LoadRequest = false;
	}


	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;


	float normal1, normal2,rayLength;
	rayLength = 25;
	physBody->RayCast(position.x, position.y, position.x + rayLength, position.y,normal1,normal2);

	if (isGodmodeOn == false)
	{
		//Right
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && state != ATTACK && state != DEAD)
		{
			physBody->body->SetLinearVelocity({ speed.x, physBody->body->GetLinearVelocity().y });
			state = MOVE_RIGHT;

		}
		else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && state != ATTACK && state != DEAD)
		{
			physBody->body->SetLinearVelocity({ -speed.x, physBody->body->GetLinearVelocity().y });
			state = MOVE_LEFT;

		}
		else if (onGround && state != ATTACK && state != DEAD) {
			physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });
			state = IDLE;
		}
		//Jump
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && onGround && state != ATTACK && state != DEAD)
		{
			physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
			doubleJump = true;
			onGround = false;
			state = JUMP;

			if (physBody->body->GetLinearVelocity().y > speed.y)
			{
				physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
			}
		}
		else//DoubleJump
			if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && doubleJump && state != ATTACK && state != DEAD)
			{
				physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
				doubleJump = false;
				state = DOUBLE_JUMP;

				if (physBody->body->GetLinearVelocity().y > speed.y)
				{
					physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
				}
			}
	}
	else
	{
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && state != ATTACK && state != DEAD)
		{
		physBody->body->SetLinearVelocity({ speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = MOVE_RIGHT;
		}
		else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && state != ATTACK && state != DEAD)
		{
		physBody->body->SetLinearVelocity({ -speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = MOVE_LEFT;
		}
		else physBody->body->SetLinearVelocity({ 0, physBody->body->GetLinearVelocity().y });

		if ((app->input->GetKey(SDL_SCANCODE_UP) || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && state != ATTACK && state != DEAD)
		{
			physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, -speed.y * 1.5f });
			state = JUMP;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) && state != ATTACK && state != DEAD)
		{
			physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y * 1.5f });
			state = JUMP;
		}
		else physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, 0 });
	}
	

	//Player melee attack
	int dir = 0;
	if (direction == 1) dir = -25;
	else dir = 20;

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && state != ATTACK && state != DEAD && onGround && isGodmodeOn == false)
	{
		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });

		PhysBody* melee = app->physics->CreateRectangleSensor(METERS_TO_PIXELS(physBody->body->GetPosition().x) + dir,
					METERS_TO_PIXELS(physBody->body->GetPosition().y), 18, 20, b2_staticBody);
		melee->color = { 120, 50, 100, 155 };
		melee->listener = app->levelManagement->currentScene;
		melee->type = Collider_Type::PLAYER_ATTACK;
		app->physics->playerAttackSensors.add(melee);

		state = ATTACK;
	}
	else if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && state != ATTACK && state != DEAD && onGround && isGodmodeOn)
	{
		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });

		PhysBody* melee = app->physics->CreateRectangleSensor(METERS_TO_PIXELS(physBody->body->GetPosition().x) + dir,
			METERS_TO_PIXELS(physBody->body->GetPosition().y), 18, 20, b2_staticBody);
		melee->color = { 120, 50, 100, 155 };
		melee->listener = app->levelManagement->currentScene;
		melee->type = Collider_Type::PLAYER_ATTACK;
		app->physics->playerAttackSensors.add(melee);

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
	pos.x = 20 + position.x;
	pos.y = 20 + position.y;
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
		direction = SDL_FLIP_HORIZONTAL;
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case MOVE_RIGHT:
		direction = SDL_FLIP_NONE;
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case ATTACK:
		meleePlayerAnim.Update();
		idlePlayerAnim.Reset();
		break;
	case DEAD:
		physBody->body->SetType(b2_staticBody);
		break;
	}
	currentAnim->Update();
	
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (isGodmodeOn) 
		{
			isGodmodeOn = false;
		}
		else
		{
			isGodmodeOn = true;
		}
	}

	return ret;

}

bool ModulePlayer::PostUpdate()
{
	//check if player in map boundaries; Screen size is in pixels
	fPoint pixelPosition;
	pixelPosition.x = METERS_TO_PIXELS(position.x);
	pixelPosition.y = METERS_TO_PIXELS(position.y);

	b2Vec2 newPos;
	newPos.x = lastPosition.x;
	newPos.y = lastPosition.y;

	//Left Right boundaries
	if ((pixelPosition.x + colliderRadius) > SCREEN_WIDTH || (pixelPosition.x - colliderRadius) < 0)
	{
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
		physBody->body->SetLinearVelocity({ 0, physBody->body->GetLinearVelocity().y });
	}

	//Top Bot boundaries
	if ((pixelPosition.y + colliderRadius) > SCREEN_HEIGHT || (pixelPosition.y - colliderRadius) < 0)
	{
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
		physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, 0 });
	}

	//store Lats position after all the update
	lastPosition = position;


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
		if (currentAnim->HasFinished())
		{
			app->levelManagement->gameState = LevelManagement::GameState::GAME_OVER;
		}
		break;
	}

	if (playerTexture != NULL)
	{
		SDL_Rect* rect;
		rect = &currentAnim->GetCurrentFrame();

		if (state == ATTACK && direction == 1)
		{
			app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 52), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else if (state == DEAD)
		{
			if (direction == 1)
			{
				app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
					&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			}
			else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y - 26),
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	}
		

	if (state == ATTACK && frameCounter < 20)
	{
		frameCounter++;
	}
	else if (frameCounter >= 20)
	{
		state = IDLE;
		frameCounter = 0;
		app->physics->playerAttackSensors.getFirst()->data->pendingToDelete = true;
		app->physics->playerAttackSensors.clear();
	}

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	state = IDLE;
	delete physBody;
	physBody = nullptr;
	currentAnim = nullptr;
	return true;
}

void ModulePlayer::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);
	if(physBody->body != nullptr)
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}

void ModulePlayer::Spawn(iPoint pos)
{
	Enable();
	SetPosition(pos);
	state = IDLE;
	lives = 1;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	position.x = data.child("player").attribute("x").as_int();
	position.y = data.child("player").attribute("y").as_int();
	state = static_cast<PlayerState>(data.child("player").attribute("state").as_int());

	LoadRequest = true;

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