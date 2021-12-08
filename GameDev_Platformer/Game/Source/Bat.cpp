#include "Bat.h"
#include "Globals.h"
#include "App.h"
#include "Map.h"
#include "Input.h"
#include "Player.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Log.h"

Bat::Bat(bool isActive) : Module(isActive)
{
	name.Create("Bat");
}

Bat::~Bat()
{
}

bool Bat::Awake()
{
	return true;
}

bool Bat::Start()
{
	LOG("BAT START");
	if (physBody == NULL)
	{
		texture = app->tex->Load("Assets/Spritesx16/bat.png");
		//Idle anim
		idleAnim.PushBack({ 0, 0, 32, 32 });
		idleAnim.PushBack({ 32, 0, 32, 32 });
		idleAnim.PushBack({ 64, 0, 32, 32 });
		idleAnim.PushBack({ 96, 0, 32, 32 });
		idleAnim.PushBack({ 128, 0, 32, 32 });
		idleAnim.PushBack({ 160, 0, 32, 32 });
		idleAnim.PushBack({ 192, 0, 32, 32 });
		idleAnim.PushBack({ 224, 0, 32, 32 });
		idleAnim.PushBack({ 256, 0, 32, 32 });
		idleAnim.PushBack({ 288, 0, 32, 32 });
		idleAnim.loop = true;
		idleAnim.mustFlip = true;
		idleAnim.speed = 0.1f;
		//Jump anim
		deathAnim.PushBack({ 128, 0, 32, 32 });
		deathAnim.PushBack({ 128, 32, 32, 32 });
		deathAnim.PushBack({ 128, 64, 32, 32 });
		deathAnim.PushBack({ 128, 96, 32, 32 });
		deathAnim.PushBack({ 128, 128, 32, 32 });
		deathAnim.PushBack({ 128, 160, 32, 32 });
		deathAnim.PushBack({ 128, 192, 32, 32 });
		deathAnim.PushBack({ 128, 124, 32, 32 });
		deathAnim.PushBack({ 128, 156, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 0, 0, 0, 0 });
		deathAnim.loop = false;
		deathAnim.mustFlip = true;
		deathAnim.speed = 0.15f;

		currentAnim = &idleAnim;

		position = { 0, 400 };
		physBody = app->physics->CreateCircle(position.x, position.y, 7, b2_dynamicBody, { 0,400,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->color = { 255,125,0,255 };

		physBody->body->SetFixedRotation(true);
		app->physics->entities.add(physBody);

		state = MOVE_TOWARDS;

		//make the path 
		pathfinding = new PathFinding(true);

		int w, h;
		uchar* data = NULL;
		if (app->map->CreateWalkabilityMap(w, h, &data)) pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
	}
	return true;
}

bool Bat::PreUpdate()
{
	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	origin.x = (int)position.x;
	origin.y = (int)position.y;

	//convert meters to pixels
	destination.x = METERS_TO_PIXELS(destination.x);
	destination.y = METERS_TO_PIXELS(destination.y);
	origin.x = METERS_TO_PIXELS(origin.x);
	origin.y = METERS_TO_PIXELS(origin.y);


	switch (state)
	{
	case PATROL:

		//destination

		UpdatePath(destination);
		if (origin.DistanceTo(destination) < detectionDistance)
		{
			//	state = MOVE_TOWARDS;
		}
		break;
	case MOVE_TOWARDS:
		destination.x = (int)app->player->GetPosition().x;
		destination.y = (int)app->player->GetPosition().y;
		//convert meters to pixels
		destination.x = METERS_TO_PIXELS(destination.x);
		destination.y = METERS_TO_PIXELS(destination.y);

		UpdatePath(destination);
		if (origin.DistanceTo(destination) > detectionDistance)
		{
			//	state = PATROL;
		}
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

bool Bat::Update(float dt)
{
	switch (state)
	{
	case PATROL:
		Move();
		break;
	case MOVE_TOWARDS:
		Move();
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

bool Bat::PostUpdate()
{

	const DynArray<iPoint>* path = pathfinding->GetLastPath();
	if (DEBUG)
	{
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
	currentAnim->Update();

	if (texture != nullptr && active)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 14), METERS_TO_PIXELS(physBody->body->GetPosition().y - 14),
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);

	if (state == PATROL)
	{
		idleAnim.Update();
	}
	if (state == DEATH)
	{
		deathAnim.Update();
	}

	return true;
}

bool Bat::CleanUp()
{
	return true;
}

void Bat::Spawn(iPoint pos)
{
	Enable();
	SetPosition(pos);
}

bool Bat::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Bat::SaveState(pugi::xml_node& data) const
{
	return true;
}

void Bat::UpdatePath(iPoint _destination)
{
	//convert Pixels to Tiles
	destination = app->map->WorldToMap(destination.x, destination.y);
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);

	pathfinding->CreatePath(origin, destination);
}

void Bat::Move()
{
	const DynArray<iPoint>* path = pathfinding->GetLastPath();

	iPoint currentTile;
	currentTile.x = METERS_TO_PIXELS(position.x);
	currentTile.y = METERS_TO_PIXELS(position.y);

	iPoint nextTile;

}

void Bat::SetPosition(iPoint pos)
{
	b2Vec2 newPos;
	newPos.x = PIXEL_TO_METERS(pos.x);
	newPos.y = PIXEL_TO_METERS(pos.y);

	physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}