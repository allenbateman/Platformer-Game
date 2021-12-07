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
	texture = app->tex->Load("Assets/Spritesx16/characters.png");
	//Idle anim
	idleAnim.PushBack({ 41, 274, 14, 14 });
	idleAnim.PushBack({ 73, 276 , 14, 12 });
	idleAnim.loop = true;
	idleAnim.mustFlip = true;
	idleAnim.speed = 0.01f;
	//Walking anim
	walkingAnim.PushBack({ 9, 274, 14, 14 });
	walkingAnim.PushBack({ 41, 274, 14, 14});
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

	position = { 370, 300 };
	physBody = app->physics->CreateCircle(position.x, position.y, 7, b2_dynamicBody, { 0,250,125,255 });
	physBody->listener = app->levelManagement->currentScene;
	physBody->color = {255,125,0,255};

	physBody->body->SetFixedRotation(true);
	app->physics->entities.add(physBody);

	state = MOVE_TOWARDS;

	//make the path 
	pathfinding = new PathFinding(true);

	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data)) pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	LOG("MUSER START");
	return true;
}

bool Musher::PreUpdate()
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

bool Musher::PostUpdate()
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
		app->render->DrawRectangle(rect,255,125,0,150);
	}

	currentAnim->Update();
	if(texture!=nullptr)
	app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x-14), METERS_TO_PIXELS(physBody->body->GetPosition().y-14),
		&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	return true;
}

bool Musher::CleanUp()
{
	return true;
}

void Musher::Spawn(fPoint pos)
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

void Musher::UpdatePath(iPoint _destination)
{
	//convert Pixels to Tiles
	destination = app->map->WorldToMap(destination.x, destination.y);
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);

	pathfinding->CreatePath(origin, destination);
}

void Musher::Move()
{
	const DynArray<iPoint>* path = pathfinding->GetLastPath();

	iPoint currentTile;
	currentTile.x = METERS_TO_PIXELS(position.x);
	currentTile.y = METERS_TO_PIXELS(position.y);
	
	iPoint nextTile;

}
