#include "Musher.h"
#include "Globals.h"
#include "App.h"
#include "Map.h"
#include "Input.h"
#include "Player.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Log.h"
#include <math.h>
Musher::Musher(bool isActive) : Module(isActive)
{
	name.Create("Musher");
}

Musher::~Musher()
{
}

bool Musher::Awake()
{
	return true;
}

bool Musher::Start()
{
	LOG("MUSER START");
	if (physBody == NULL)
	{
		texture = app->tex->Load("Assets/Spritesx16/characters.png");
		//Idle anim
		idleAnim.PushBack({ 41, 274, 14, 14 });
		idleAnim.PushBack({ 73, 276 , 14, 12 });
		idleAnim.loop = true;
		idleAnim.mustFlip = true;
		idleAnim.speed = 0.01f;
		//Walking anim
		walkingAnim.PushBack({ 9, 274, 14, 14 });
		walkingAnim.PushBack({ 41, 274, 14, 14 });
		walkingAnim.PushBack({ 73, 276 , 14, 12 });
		walkingAnim.loop = true;
		walkingAnim.mustFlip = true;
		walkingAnim.speed = 0.1f;
		//Jump anim
		jumpingAnim.PushBack({ 137, 274, 14, 14 });
		jumpingAnim.PushBack({ 168, 272, 14, 14 });
		jumpingAnim.PushBack({ 201, 272, 14, 15 });
		jumpingAnim.PushBack({ 233, 275, 14, 13 });
		jumpingAnim.loop = true;
		jumpingAnim.mustFlip = true;
		jumpingAnim.speed = 0.1f;

		currentAnim = &idleAnim;

		position = { 0, 400 };
		physBody = app->physics->CreateCircle(position.x, position.y, 8, b2_dynamicBody, { 0,400,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->color = { 255,125,0,255 };

		physBody->body->SetFixedRotation(true);
		app->physics->entities.add(physBody);

		//make the path 
		pathfinding = new PathFinding(true);

		int w, h;
		uchar* data = NULL;
		if (app->map->CreateWalkabilityMap(w, h, &data,1)) pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);

		state = PATROL;
	
	}
	
	return true;
}

bool Musher::PreUpdate()
{
	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	float distanceToPlayer = position.DistanceTo(app->player->position);

	switch (state)
	{
	case PATROL:
		if (OnPatrolPoint)
		{
			CalculateNextPatrolPoint();
		}
		if (distanceToPlayer < detectionDistance)
		{
			state = MOVE_TOWARDS;
		}

		break;
	case MOVE_TOWARDS:
		UpdatePath();
		if (distanceToPlayer > detectionDistance)
		{
			state = PATROL;
		}

		break;
	case JUMP:
		break;
	case DEATH:
		if (deathAnim.HasFinished())
		{
			CleanUp();
		}
		break;
	default:
		break;
	}

	return true;
}

bool Musher::Update(float dt)
{
	switch(state)
	{
	case PATROL:
		Move(dt);
		break;
	case MOVE_TOWARDS:
		Move(dt);
		break;
	case JUMP:
		break;
	case DEATH:
		break;
	default:
		break;
	}

	return true;
}

bool Musher::PostUpdate()
{
	if (DEBUG)
	{
		const DynArray<iPoint>* path = pathfinding->GetLastPath();
		SDL_Rect rect;
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			rect.x = (pos.x);
			rect.y = (pos.y);
			rect.w = (16);
			rect.h = (16);
			app->render->DrawRectangle(rect, 255, 125, 0, 150);
		}
	}

	//pathfinding->DrawPath();
	currentAnim->Update();

	if(texture!=nullptr && active)
	app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x-14), METERS_TO_PIXELS(physBody->body->GetPosition().y-14),
		&(currentAnim->GetCurrentFrame()), 1, spriteRotation,position.x-8, position.y-8, 1.8f, spriteDir);
	return true;
}

bool Musher::CleanUp()
{
	return true;
}

void Musher::Spawn(iPoint pos)
{
	Enable();
	SetPosition(pos);
}

bool Musher::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Musher::SaveState(pugi::xml_node& data) const
{
	return true;
}

bool Musher::CalculateNextPatrolPoint()
{
	iPoint destination;
	iPoint origin;
	// in the destination calculate a new point
	origin.x = METERS_TO_PIXELS(origin.x);
	origin.y = METERS_TO_PIXELS(origin.y);
	//convert Pixels to Tiles
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);
	destination = patrolPoint1;
	pathfinding->CreatePath(origin, destination);
	//check if it is in the destination
	if (destination == origin)
	{
		if (destination == patrolPoint1)
		{
			destination = patrolPoint2;
		}
		else if (destination == patrolPoint2)
		{
			destination = patrolPoint1;
		}
	}
	//otherwise continue
		return true;
}

void Musher::UpdatePath()
{
	iPoint destination;
	destination.x = (int)app->player->GetPosition().x;
	destination.y = (int)app->player->GetPosition().y;
	//convert meters to pixels
	destination.x = METERS_TO_PIXELS(destination.x);
	destination.y = METERS_TO_PIXELS(destination.y);
	
	iPoint origin;
	origin.x =(int) physBody->body->GetPosition().x;
	origin.y =(int) physBody->body->GetPosition().y;
	//convert meters to pixels
	origin.x = METERS_TO_PIXELS(origin.x);
	origin.y = METERS_TO_PIXELS(origin.y);

	//convert Pixels to Tiles
	destination = app->map->WorldToMap(destination.x, destination.y);
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);

	pathfinding->CreatePath(origin, destination);
}

void Musher::Move(float dt)
{
	const DynArray<iPoint>* path = pathfinding->GetLastPath();
	if (path->At(1) != nullptr)
	{
		iPoint currentTile;
		iPoint nextTile;

		currentTile.x = METERS_TO_PIXELS(position.x) - 8;
		currentTile.y = METERS_TO_PIXELS(position.y) - 8;

		b2Vec2 distance;
		b2Vec2 direction;

		nextTile = app->map->MapToWorld(path->At(1)->x, path->At(1)->y);

		if (nextTile != currentTile)
		{	
			position.x = physBody->body->GetPosition().x;
			position.y = physBody->body->GetPosition().y;
			currentTile.x = METERS_TO_PIXELS(position.x) - 8;
			currentTile.y = METERS_TO_PIXELS(position.y) - 8;

			direction.x =  nextTile.x - currentTile.x;
			direction.y =  nextTile.y - currentTile.y;
			
			if (direction.x >= 0)
				spriteDir = SDL_FLIP_NONE;
			if(direction.x < 0)
				spriteDir = SDL_FLIP_HORIZONTAL;

			if (direction.y <= 0 && spriteDir == SDL_FLIP_NONE)
			{
				spriteRotation = -90;

			}else if (direction.y <= 0 && spriteDir == SDL_FLIP_HORIZONTAL)
			{
				spriteRotation = 90;
			}
			else {
				spriteRotation = 0;
			}


			if (speedMultiplier > 1)
				speedMultiplier = 1;
			if (speedMultiplier < 0.1f)
				speedMultiplier = 0.1f;

			direction.x *= speedMultiplier;
			direction.y *= speedMultiplier;

			physBody->body->SetLinearVelocity(direction);
		}
		
	}
}

void Musher::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x,pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);

	physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}